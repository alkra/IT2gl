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
#include "../_api/src/CGraphe.h"

GLvoid dessiner_graphe(const CGraphe &graphe);
GLvoid dessiner_trains(CGraphe &graphe);
GLvoid deplacer_train(int v);

#endif // DESSIN_H
