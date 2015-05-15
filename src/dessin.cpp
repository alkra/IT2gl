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
#include "train.h"

GLvoid dessiner_graphe(const CGraphe &graphe) {
    std::vector<CArc> arcs = graphe.list_arc;
    std::vector<CSommet> sommets = graphe.list_sommet;
    std::vector<CPointAnnexe> pts_annexes = graphe.list_point_annexe;
    std::vector<int> arc_pa;

    CSommet *sommet_ini = NULL, *sommet_fin = NULL;

    glColor3ub(255, 255, 255);
    glLineWidth(6);
    for(int i = 0 ; i < graphe.nb_arc ; i++) {
        sommet_ini = &sommets[arcs[i].id_sommet_ini];
        sommet_fin = &sommets[arcs[i].id_sommet_fin];
        arc_pa = arcs[i].list_point_annexe;

        glBegin(GL_LINE_STRIP);

        // point de départ
        glVertex3f(sommet_ini->X, sommet_ini->Y, sommet_ini->Z);

        // points annexes
        for(std::vector<int>::iterator j = arc_pa.begin(); j != arc_pa.end(); ++j) {
            glVertex3f(pts_annexes[*j].X, pts_annexes[*j].Y, pts_annexes[*j].Z);
        }

        // point d'arrivée
        glVertex3f(sommet_fin->X, sommet_fin->Y, sommet_fin->Z);

        glEnd();
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

GLvoid deplacer_train(int v) {
    for(unsigned int i=0; i < trains.size() ; i++) {
        trains[i].avancer();
    }
}
