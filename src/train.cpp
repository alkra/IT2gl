#include "train.h"

Train::Train(CGraphe &gr) : graphe(gr), wagons(), vitesse(0)
{
}

Train::Train(CGraphe &gr, std::vector<Wagon> w, double v)
    : graphe(gr), wagons(w), vitesse(v) {
}

Train::Train(const Train &autre) : graphe(autre.graphe), wagons(autre.wagons),
vitesse(autre.vitesse) {

}

void Train::dessiner() const {
    for(unsigned int i= 0 ; i < wagons.size() ; i++) {
        wagons[i].dessiner();
    }
}

void Train::avancer() const {

}

std::vector<Train> construire_trains(CGraphe graphe) {
    std::vector<Train> trains;

    CArc courant = graphe.list_arc[1];
    CPoint3f ini = graphe.list_sommet[courant.id_sommet_ini],
            fin = graphe.list_point_annexe[courant.list_point_annexe[0]];
    Wagon wagon11(0, ini, fin, 64, 0, 0, 1.5),
            wagon12(2.5, ini, fin, 128, 0, 0, 3);
    std::vector<Wagon> w;
    w.push_back(wagon11);
    w.push_back(wagon12);
    Train train1(graphe, w, 0);

    trains.push_back(train1);
    return trains;
}
