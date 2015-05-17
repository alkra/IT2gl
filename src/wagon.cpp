#include "wagon.h"
#include "tests.h"

#include <GL/glut.h>
#include <cmath>
#include <iostream>

Wagon::Wagon() : position(0), dimensions(1.5, 1.2, 1.2), arc(-1), si_courant(), sf_courant(), norme(0), rouge(255), vert(255), bleu(255) {
}

Wagon::Wagon(double pos, int _arc, const CPoint3f &si, const CPoint3f &sf, GLubyte r, GLubyte v, GLubyte b, double longueur, double largeur, double hauteur)
    : position(pos), dimensions(longueur, largeur, hauteur), arc(_arc), si_courant(si), sf_courant(sf), norme(), rouge(r), vert(v), bleu(b) {
    norme = calculer_norme(si, sf);
}

Wagon::Wagon(const Wagon &autre)
    : position(autre.position), dimensions(autre.dimensions), arc(autre.arc), si_courant(autre.si_courant),
      sf_courant(autre.sf_courant), norme(autre.norme), rouge(autre.rouge), vert(autre.vert), bleu(autre.bleu) {
}

void Wagon::calculer_norme() {
    norme = calculer_norme(si_courant, sf_courant);
}

double Wagon::calculer_norme(const CPoint3f &un, const CPoint3f &deux) {
    return std::sqrt(
                std::pow(un.X - deux.X, 2) +
                std::pow(un.Y - deux.Y, 2) +
                std::pow(un.Z - deux.Z, 2));
}

void Wagon::dessiner() const {
    glPushMatrix();

    // on place le wagon au bon endroit
    glTranslatef(si_courant.X, si_courant.Y, si_courant.Z);

    // on oriente le wagon : nouveau X dans le sens du tronçon
    CPoint3f troncon(sf_courant.X - si_courant.X,
                     sf_courant.Y - si_courant.Y,
                     sf_courant.Z - si_courant.Z);
    if(troncon.Y || troncon.Z) { // pas colinéaire à X
        CPoint3f axe(0, -troncon.Z, troncon.Y); // X vectoriel troncon
        GLfloat angle = std::acos(troncon.X / norme); // angle (X, troncon) comme notre produit vectoriel
        glRotatef(angle*180/M_PI, axe.X, axe.Y, axe.Z);
    } else if(troncon.X < 0) {
        glRotatef(180, 0, 0, 1);
    }

    // on le déplace sur l'arc
    glTranslatef(position, 0, 0);

    // couleur
    glColor3ub(rouge, vert, bleu);

    // taille
    glScalef(dimensions.X, dimensions.Y, dimensions.Z);

    // dessin
    glutSolidCube(1);

    glPopMatrix();
}

bool operator==(const CPoint3f &u, const CPoint3f &d) {
    return (u.X == d.X) && (u.Y == d.Y) && (u.Z == d.Z);
}

bool operator!=(const CPoint3f &u, const CPoint3f &d) {
    return (u.X != d.X) || (u.Y != d.Y) || (u.Z != d.Z);
}
