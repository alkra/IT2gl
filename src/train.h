#ifndef TRAIN_H
#define TRAIN_H

#include "_api/src/CPoint3f.h"
#include "_api/src/CGraphe.h"

#include "wagon.h"

class Train
{
public:
    Train(CGraphe &gr);
    Train(CGraphe &gr, std::vector<Wagon> w = std::vector<Wagon>(), double v = 0);
    Train(const Train &autre);

    void dessiner() const;

    CGraphe graphe;
    std::vector<Wagon> wagons;
    double vitesse;
};


std::vector<Train> construire_trains(CGraphe graphe);

#endif // TRAIN_H
