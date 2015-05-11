#ifndef WAGON_H
#define WAGON_H

#include "../_api/src/CPoint3f.h"

class Wagon
{
public:
    Wagon();
    Wagon(double pos, const CPoint3f &si, const CPoint3f &sf);
    Wagon(const Wagon &autre);

    void dessiner() const;

    double position;
    CPoint3f si_courant;
    CPoint3f sf_courant;
};

#endif // WAGON_H
