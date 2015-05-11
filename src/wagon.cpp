#include "wagon.h"
#include "tests.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>

Wagon::Wagon() : position(0), si_courant(), sf_courant() {
}

Wagon::Wagon(double pos, const CPoint3f &si, const CPoint3f &sf)
    : position(pos), si_courant(si), sf_courant(sf) {
}

Wagon::Wagon(const Wagon &autre)
    : position(autre.position), si_courant(autre.si_courant),
      sf_courant(autre.sf_courant) {
}

void Wagon::dessiner() const {
    std::cout << "Dessin du wagon";

    double norme = std::sqrt(
                std::pow(sf_courant.X - si_courant.X, 2) +
                std::pow(sf_courant.Y - si_courant.Y, 2) +
                std::pow(sf_courant.Z - si_courant.Z, 2));
    glPushMatrix();

    // on place le wagon au bon endroit
    glTranslatef(si_courant.X, si_courant.Y, si_courant.Z);
    //glRotatef(std::asin((sf_courant.X - si_courant.X)/norme),
    //    0, 0, 0);

    glColor3ub(255, 0, 0);

    // on le dessine à la bonne taille
    glScalef(60, 1, 1);
    //glutSolidCube(1);
    TEST_DESSIN_REPERE;

    glPopMatrix();
}
