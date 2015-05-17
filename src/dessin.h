/* © ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes – Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 *
 * Projet OpenGL
 * Proposé par I. GIROUX
 * Réalisé par KRAUS Alban, PENSIER Philémon, SCHITTEK Gabin
 * 15 mai 2015
 */

#ifndef DESSIN_H
#define DESSIN_H

#include <GL/gl.h>
#include "_api/CGraphe.h"
#include "train.h"

GLvoid dessiner_graphe(CGraphe &graphe);
GLvoid dessiner_trains(CGraphe &graphe);
GLvoid deplacer_train();


double collision_verifier_vitesse(const Train *train);
int collision_calcul_priorite(const CSommet &mathieu_sommet);
void collision_liberer_vitesse(const std::vector<CArc> &entrants);

#endif // DESSIN_H
