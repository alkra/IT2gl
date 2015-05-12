#include "wagon.h"
#include "tests.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>

Wagon::Wagon() : position(0), si_courant(), sf_courant(), rouge(255), vert(255), bleu(255), dimensions(1.5, 1.2, 1.2) {
}

Wagon::Wagon(double pos, const CPoint3f &si, const CPoint3f &sf, GLubyte r, GLubyte v, GLubyte b, double longueur, double largeur, double hauteur)
    : position(pos), si_courant(si), sf_courant(sf), rouge(r), vert(v), bleu(b), dimensions(longueur, largeur, hauteur) {
}

Wagon::Wagon(const Wagon &autre)
    : position(autre.position), si_courant(autre.si_courant),
      sf_courant(autre.sf_courant), rouge(autre.rouge), vert(autre.vert), bleu(autre.bleu),
      dimensions(autre.dimensions) {
}

void Wagon::dessiner() const {
    double norme = std::sqrt(
                std::pow(sf_courant.X - si_courant.X, 2) +
                std::pow(sf_courant.Y - si_courant.Y, 2) +
                std::pow(sf_courant.Z - si_courant.Z, 2));
    TEST_DESSIN_REPERE;
    glPushMatrix();

    // on place le wagon au bon endroit
    glTranslatef(si_courant.X, si_courant.Y, si_courant.Z);
    // on oriente le wagon
    double angle = std::acos((sf_courant.X - si_courant.X)/norme);
    glRotatef(180 - angle*180/M_PI, 0, 0, 1);
    // on le déplace sur l'arc
    glTranslatef(position, 0, 0);

    glColor3ub(rouge, vert, bleu);

    // on le dessine à la bonne taille
    glScalef(dimensions.X, dimensions.Y, dimensions.Z);
    glutSolidCube(1);

    glPopMatrix();
}
