/* © ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes – Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 *
 * Projet OpenGL
 * Proposé par I. GIROUX
 * Réalisé par KRAUS Alban, PENSIER Philémon, SCHITTEK Gabin
 * 15 mai 2015
 */

#include "dessin.h"
#include <GL/glut.h>
#include <algorithm>

GLvoid dessiner_graphe(CGraphe &graphe) {
    std::vector<CArc> arcs = graphe.list_arc;
    std::vector<CSommet> sommets = graphe.list_sommet;
    std::vector<CPointAnnexe> pts_annexes;

    CSommet *sommet_ini = NULL, *sommet_fin = NULL;

    for(int i = 0 ; i < graphe.nb_arc ; i++) {
        const CArc &arc_courant = arcs[i];
        sommet_ini = &sommets[arcs[i].id_sommet_ini];
        sommet_fin = &sommets[arcs[i].id_sommet_fin];
        pts_annexes = graphe.getListPointAnnexeArc(arc_courant);


        glColor3ub(255, 255, 255);
        glLineWidth(6);
        glBegin(GL_LINE_STRIP);

        // point de départ
        glVertex3f(sommet_ini->X, sommet_ini->Y, sommet_ini->Z);

        // points annexes
        for(unsigned int j = 0 ; j < pts_annexes.size() ; j++) {
            glVertex3f(pts_annexes[j].X, pts_annexes[j].Y, pts_annexes[j].Z);
        }

        // point d'arrivée
        glVertex3f(sommet_fin->X, sommet_fin->Y, sommet_fin->Z);

        glEnd();

        // dessin du sommet
        glPushMatrix();
        glTranslatef(sommet_fin->X, sommet_fin->Y, sommet_fin->Z);
        glLineWidth(1);
        glColor3ub(255, 0, 0);
        glutSolidSphere(0.4, 5, 5);
        glPopMatrix();
    }
}


static std::vector<Train> trains;
GLvoid dessiner_trains(CGraphe &graphe) {
    if(trains.empty()) {
        trains = construire_trains(graphe);
    }

    for(unsigned int i =0; i < trains.size() ; i++)
    {
        trains[i].dessiner();
    }
}

GLvoid deplacer_train() {
    for(unsigned int i=0; i < trains.size() ; i++) {
        trains[i].avancer();
    }
}



struct Priorite {
    Train *train;
    unsigned int nb_wagons;
    short priorite;
};

bool inferieur(Priorite un, Priorite deux) {
    if(un.priorite < 0) {
        return false;
    } else if(deux.priorite < 0) {
        return true;
    } else {
        if(un.priorite < deux.priorite) {
            return true;
        } else if(deux.priorite < un.priorite) {
            return false;
        } else { // priorités égales
            return un.nb_wagons <= deux.nb_wagons;
        }
    }
}

int collision_calcul_priorite(const CSommet &mathieu_sommet) {
    // Recherche d'un train engagé dans le carrefour
    bool train_engage = false;
    std::vector<Train>::iterator engage = trains.begin();
    for(; engage != trains.end() && !train_engage ; ++engage) {
        for(std::vector<Wagon>::iterator w = engage->wagons.begin() ;
            w != engage->wagons.end() ; ++w) {
            if(w->sf_courant == mathieu_sommet && engage->vitesse > 0) {
                train_engage = true;
            }
        }
    }
    short priorite_min = 0;
    if(train_engage) {
        // un train est engage
        --engage; // car incrémenté une fois de trop
        priorite_min++;
    }

    // liste des trains en attente en attente à ce carrefour
    std::list<Priorite> trains_en_attente;
    Priorite constructeur;
    for(std::vector<Train>::iterator train = trains.begin();
        train != trains.end(); ++train) {
        if(train == engage) {
            continue;
        }

        if(train->carrefour_contient(mathieu_sommet)) {
            constructeur.train = &(*train);
            constructeur.priorite = train->attente;
            constructeur.nb_wagons = train->wagons.size();
            trains_en_attente.push_front(constructeur);
        }
    }

    // Tri des trains par ordre de priorité
    trains_en_attente.sort(inferieur);

    // Attribution des priorités et des vitesses
    short priorite_actuelle = priorite_min;
    Priorite train_actuel;
    while(!trains_en_attente.empty()) {
        train_actuel = trains_en_attente.front();
        trains_en_attente.pop_front();

        if(priorite_actuelle > 0) {
            // on arrête le train
            train_actuel.train->vitesse = 0;
        } else {
            // on redémarre ...
            train_actuel.train->vitesse = train_actuel.train->vitesse_max;
        }

        // priorité du train
        train_actuel.train->attente = priorite_actuelle;
        priorite_actuelle++;
    }

    return 0;
}


double collision_verifier_vitesse(const Train *train) {
    if(train->vitesse == 0) {
        // le train est arrêté à un feu
        return 0;
    }

    std::list<double> devant;
    for(std::vector<Train>::const_iterator t = trains.begin() ;
        t != trains.end() ; ++t) {
        if(&(*t) == train) {
            continue;
        }
        if((t->wagons.end() -1)->arc == train->wagons.begin()->arc) {
            devant.push_front(t->vitesse);
        }
    }

    if(devant.empty()) {
        return train->vitesse_max;
    } else {
        devant.sort();
        return std::min<double>(train->vitesse_max, devant.front());
    }
}
