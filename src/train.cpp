#include "train.h"
#include "dessin.h"

#include <iostream>
#include <cstdlib> // rand

Train::Train(CGraphe &gr) : graphe(gr), wagons(), etendue(), etendue_arc(), vitesse_max(0), vitesse(0), attente(0), carrefours()
{
}

Train::Train(CGraphe &gr, std::vector<Wagon> w, double v)
    : graphe(gr), wagons(w), etendue(), etendue_arc(), vitesse_max(v), vitesse(v), attente(0), carrefours() {
    if(!w.empty()) {
        std::list<CPoint3f>::iterator dernier_point = etendue.begin(); // point ayant été dépassé par le dernier wagon du train

        for(std::vector<Wagon>::reverse_iterator w_courant = w.rbegin() ;
            w_courant != w.rend() ;
            ++w_courant) {
            // pour chaque wagon (en commençant par le dernier)
            if(w_courant == w.rbegin()
                    || w_courant->si_courant != *dernier_point) { // ce wagon est avant le dernier point du train
                etendue.push_front(w_courant->si_courant);
                etendue_arc.push_front((w_courant->arc));
                dernier_point = etendue.begin();
            }
        }

        etendue.push_front(w[0].sf_courant); // direction du train
        etendue_arc.push_front(w[0].arc);
    }
}

Train::Train(const Train &autre) : graphe(autre.graphe), wagons(autre.wagons),
    etendue(autre.etendue), etendue_arc(autre.etendue_arc), vitesse_max(autre.vitesse_max), vitesse(autre.vitesse),
    attente(autre.attente), carrefours(autre.carrefours) {
}

bool Train::carrefour_contient(const CPoint3f &recherche) const {
    for(std::vector<CSommet>::const_iterator courant = carrefours.begin() ;
        courant != carrefours.end() ; ++courant) {
        if(courant->X == recherche.X && courant->Y == recherche.Y && courant->Z == recherche.Z) {
            return true;
        }
    }

    return false;
}

CSommet Train::carrefour_pop(const CPoint3f &recherche) {
    for(std::vector<CSommet>::iterator courant = carrefours.begin() ;
        courant != carrefours.end() ; ++courant) {
        if(courant->X == recherche.X && courant->Y == recherche.Y && courant->Z == recherche.Z) {
            CSommet sommet = *courant;
            carrefours.erase(courant);
            return sommet;
        }
    }

    throw 0;
}

void Train::dessiner() const {
    for(std::vector<Wagon>::const_iterator wagon_courant = wagons.begin() ; wagon_courant != wagons.end() ; ++wagon_courant) {
        wagon_courant->dessiner();
    }
}

void Train::avancer() {
    for(std::vector<Wagon>::iterator wagon_courant = wagons.begin() ; wagon_courant != wagons.end() ; ++wagon_courant) {
        // on avance le wagon i
        wagon_courant->position += vitesse;

        if(wagon_courant->position > wagon_courant->norme) {
            // ON CHANGE DE TRONÇON

            // nouvelle position
            wagon_courant->position -= wagon_courant->norme;

            // premier point du tronçon suivant
            wagon_courant->si_courant = wagon_courant->sf_courant;

            // dernier point du tronçon suivant (à calculer), et son arc support
            changer_troncon(*wagon_courant);
            wagon_courant->calculer_norme();

            if(wagon_courant +1 == wagons.end()) {
                // on libère ce tronçon
                etendue.pop_back();
                etendue_arc.pop_back();

                // on libère le carrefour
                if(carrefour_contient(etendue.back())) {
                    CSommet libre = carrefour_pop(etendue.back());
                    collision_calcul_priorite(libre);
                }
            }
        }
    }
}


void trouver_point_et_arc(std::list<CPoint3f>::const_iterator &points, const std::list<CPoint3f>::const_iterator &fin, std::list<int>::const_iterator &arcs, const CPoint3f &recherche) {
    for(; points != fin && *points != recherche; ++points, ++arcs);
}

void Train::changer_troncon(Wagon &wagon) {
    // Ce wagon est-il la locomotive ?
    if(wagon.sf_courant == etendue.front()) {
        choisir_troncon(wagon);
    } else {
        std::list<CPoint3f>::const_iterator pf = etendue.begin();
        std::list<int>::const_iterator af = etendue_arc.begin();
        trouver_point_et_arc(pf, etendue.end(), af, wagon.sf_courant);
        wagon.sf_courant = *(--pf);
        wagon.arc = *(--af);
    }
}

int choisir_arc_suivant(CGraphe &gr, const int arc_actuel) {
    int isommet = gr.list_arc[arc_actuel].id_sommet_fin;
    CSommet sommet = gr.list_sommet[isommet];
    std::vector<CArc> arcs_suivants_possibles = gr.getListArcSortantDuSommet(sommet);
    return arcs_suivants_possibles[rand() % arcs_suivants_possibles.size()].id_arc;
}

void Train::choisir_troncon(Wagon &loco) {
    // on trouve le point annexe courant
    const CArc arc_courant = graphe.list_arc[loco.arc];
    const std::vector<CPointAnnexe> points_annexes = graphe.getListPointAnnexeArc(arc_courant);
    std::vector<CPointAnnexe>::const_iterator pa = points_annexes.begin();
    for(; pa != points_annexes.end() && *pa != loco.sf_courant ; ++pa);

    // Calcul du point suivant
    CPoint3f point_suivant;


    if(pa == points_annexes.end()) {
        // la loco est sur le sommet final
        loco.arc = choisir_arc_suivant(graphe, loco.arc);
        const CArc arc = graphe.list_arc[loco.arc];
        point_suivant = graphe.getListPointAnnexeArc(arc)[0];
    }

    else {
        // la loco est sur un point annexe

        if(pa +1 == points_annexes.end()) {
            // la loco est sur le dernier point annexe
            CSommet point_suivant_sommet = graphe.list_sommet[arc_courant.id_sommet_fin];
            point_suivant = point_suivant_sommet;

            // elle doit adapter sa vitesse au carrefour
            attente = -1;
            carrefours.push_back(point_suivant_sommet);
            collision_calcul_priorite(point_suivant_sommet);
        }

        else {
            point_suivant = *(pa +1);
        }
    }

    // mise à jour du point suivant
    loco.sf_courant = point_suivant;

    // on ajoute ce nouveau tronçon
    etendue.push_front(point_suivant);
    etendue_arc.push_front(loco.arc);

    // par acquis de conscience, on vérifie la vitesse
    vitesse = collision_verifier_vitesse(this);
}


std::vector<Train> construire_trains(CGraphe &graphe) {
    std::vector<Train> trains;

    /* On construit un train sur l'arc 1 */
    CArc courant = graphe.list_arc[1];
    CPoint3f ini = graphe.list_sommet[courant.id_sommet_ini],
            fin = graphe.list_point_annexe[courant.list_point_annexe[0]];
    Wagon wagon11(2.5, 1, ini, fin, 64, 0, 0, 1.5),
            wagon12(0, 1, ini, fin, 128, 0, 0, 3);
    std::vector<Wagon> w;
    w.push_back(wagon11);
    w.push_back(wagon12);
    Train train1(graphe, w, 0.1);
    trains.push_back(train1);

    /* Sur l'arc 0 */
    courant = graphe.list_arc[0];
    ini = graphe.list_sommet[courant.id_sommet_ini];
    fin = graphe.list_point_annexe[courant.list_point_annexe[0]];
    CPoint3f ffi = graphe.list_point_annexe[courant.list_point_annexe[1]];
    Wagon wagon21(  3.09, 0, fin, ffi, 8, 192, 32, 3),
            wagon22(0.84, 0, fin, ffi, 0,  64,  0, 1, 1.1),
            wagon23(2.25, 0, ini, fin, 0, 128,  0, 2, 1.4),
            wagon24(0   , 0, ini, fin, 0, 128,  0, 2, 1.4);
    w.clear();
    w.push_back(wagon21);
    w.push_back(wagon22);
    w.push_back(wagon23);
    w.push_back(wagon24);
    Train train2(graphe, w, 0.2);
    trains.push_back(train2);

    /* Sur l'arc 6 */
    courant = graphe.list_arc[6];
    ini = graphe.list_sommet[courant.id_sommet_ini];
    fin = graphe.list_point_annexe[courant.list_point_annexe[0]];
    ffi = graphe.list_point_annexe[courant.list_point_annexe[1]];
    Wagon wagon31(  8.5 , 6, ini, fin, 128, 128, 64, 3),
            wagon32(6.25, 6, ini, fin, 128, 128,  0, 1, 1.1),
            wagon33(4.5 , 6, ini, fin, 192, 192,  0, 2, 1.3),
            wagon34(2.25, 6, ini, fin, 128, 128, 32, 2, 1.4),
            wagon35(0   , 6, ini, fin, 192, 128, 32, 3);
    w.clear();
    w.push_back(wagon31);
    w.push_back(wagon32);
    w.push_back(wagon33);
    w.push_back(wagon34);
    w.push_back(wagon35);
    Train train3(graphe, w, 0.15);
    trains.push_back(train3);

    /* Sur l'arc 3 */
    courant = graphe.list_arc[3];
    ini = graphe.list_sommet[courant.id_sommet_ini];
    fin = graphe.list_point_annexe[courant.list_point_annexe[0]];
    Wagon wagon41(0, 3, ini, fin, 0, 0, 255, 2);
    w.clear();
    w.push_back(wagon41);
    Train train4(graphe, w, 0.3);
    //trains.push_back(train4); // bug
    return trains;
}
