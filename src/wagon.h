#ifndef WAGON_H
#define WAGON_H

#include "_api/CPoint3f.h"
#include <GL/gl.h>
#include <vector>

class Wagon
{
public:
    Wagon();
    Wagon(double pos, int _arc, const CPoint3f &si, const CPoint3f &sf, GLubyte r = 255, GLubyte v = 255, GLubyte b = 255, double longueur = 1.5, double largeur = 1.2, double hauteur = 1.2);
    Wagon(const Wagon &autre);

    void calculer_norme();
    static double calculer_norme(const CPoint3f &un, const CPoint3f &deux);
    void dessiner() const;

    /* géométrie du wagon */
    double position;
    CPoint3f dimensions;

    /* tronçon sur lequel se trouve le wagon */
    int arc; // indice de l'arc
    CPoint3f si_courant;
    CPoint3f sf_courant;
    GLfloat norme;

    /* couleur du wagon */
    GLubyte rouge;
    GLubyte vert;
    GLubyte bleu;
};



bool operator==(const CPoint3f &u, const CPoint3f &d);
bool operator!=(const CPoint3f &u, const CPoint3f &d);

#endif // WAGON_H
