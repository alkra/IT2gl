#ifndef TRAIN_H
#define TRAIN_H

#include "_api/CPoint3f.h"
#include "_api/CGraphe.h"

#include "wagon.h"
#include <list>

class Train
{
public:
    Train(CGraphe &gr);
    Train(CGraphe &gr, std::vector<Wagon> w = std::vector<Wagon>(), double v = 0);
    Train(const Train &autre);

    void dessiner() const;
    void avancer();

    bool carrefour_contient(const CPoint3f &recherche) const;
    CSommet carrefour_pop(const CPoint3f &recherche);

    CGraphe graphe;
    std::vector<Wagon> wagons;
    std::list<CPoint3f> etendue; // La liste des points par lesquels passe le train
    std::list<int> etendue_arc; // l'indice de l'arc sur lequel se trouve le point de la liste etendue correspondant
    double vitesse_max;
    double vitesse;
    short attente;
    std::vector<CSommet> carrefours;

private:
    void changer_troncon(Wagon &wagon);
    void choisir_troncon(Wagon &loco);
};


std::vector<Train> construire_trains(CGraphe &graphe);

#endif // TRAIN_H
