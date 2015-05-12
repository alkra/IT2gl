#ifndef WAGON_H
#define WAGON_H

#include "../_api/src/CPoint3f.h"
#include <GL/gl.h>

class Wagon
{
public:
    Wagon();
    Wagon(double pos, const CPoint3f &si, const CPoint3f &sf, GLubyte r = 255, GLubyte v = 255, GLubyte b = 255, double longueur = 1.5, double largeur = 1.2, double hauteur = 1.2);
    Wagon(const Wagon &autre);

    void dessiner() const;

    double position;
    CPoint3f dimensions;
    CPoint3f si_courant;
    CPoint3f sf_courant;
    GLubyte rouge;
    GLubyte vert;
    GLubyte bleu;
};

#endif // WAGON_H
