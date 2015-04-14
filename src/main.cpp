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

#include "config.h"
#include "dessin.h"

#include "../_api/src/CGraphe.h"
#include "../_api/src/CSommet.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

CGraphe *graphe = NULL;

CGraphe initialiser_graphe(ostream &out) {
    // construction des tables du graphe
    CDonneesGraphe gdata(CHEMIN_DATA + "SXYZ.TXT", CHEMIN_DATA + "SIF.TXT",
                         CHEMIN_DATA + "PAXYZ.TXT", CHEMIN_DATA + "AXYZ.TXT");
    // affichage des donnees
    gdata.afficheDonnees();

    // Constrcuction de la base de donnees objet du graphe
    CGraphe graphe(gdata);

    // Preparation du generateur de nombre aleatoire
    srand((unsigned)time(NULL));
    // Tirage d'un nombre aleatoire entre 0 et NS (nombre de sommet)
    int iSommet = rand() % gdata.NS;
    out<<iSommet<<endl;

    // Recuperation du sommet
    CSommet sommet = graphe.list_sommet.at(iSommet);
    out<<sommet.toString()<<endl;

    // Recuperation arcs entrants
    vector<CArc> list_arc_entrant = graphe.getListArcEntrantDansSommet(sommet);
    int nb_arc_entrant = list_arc_entrant.size();
    for (int i = 0; i < nb_arc_entrant; ++i) {
        CArc arc = list_arc_entrant.at(i);
        out<<arc.toString()<<endl;
    }
    graphe.afficheSommets();
    graphe.afficheArcs();
    graphe.buildExtent();
    out<<graphe.getExtentLowerLeft().toString()<<endl;
    out<<graphe.getExtentUpperRight().toString()<<endl;

    return graphe;
}

GLvoid initialiser_gl() {
    // taille de l'écran
    GLint larg_ecran = glutGet(GLUT_SCREEN_WIDTH),
            haut_ecran = glutGet(GLUT_SCREEN_HEIGHT);

    // fenêtre
    glutInitWindowSize(larg_ecran, haut_ecran);
    glutCreateWindow(NOM_APPLICATION);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // couleur d'effacement de la fenêtre
    glClearColor(1, 1, 1, 1);
}

//#define TEAPOT

GLvoid dessiner_scene() {
    // zone d'activité (volume de vue)
    glLoadIdentity();
#ifdef TEAPOT
    glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
#else
    CPoint3f bas_gauche = graphe->getExtentLowerLeft(),
            haut_droit = graphe->getExtentUpperRight();
    glOrtho(bas_gauche.X, haut_droit.X,
            bas_gauche.Z, haut_droit.Z,
            haut_droit.Y, bas_gauche.Y);
#endif

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
#ifdef TEAPOT
    glutSolidTeapot(600);
#else
    dessiner_graphe(*graphe);
#endif
    glFlush();
}

int main(int argc, char* argv[]) {
    // on lit le graphe
    CGraphe le_graphe = initialiser_graphe(cout);
    graphe = &le_graphe;

    // initialisation de GLUT
    glutInit(&argc, argv);
    initialiser_gl();
    glutDisplayFunc(dessiner_scene);
    glutMainLoop();
    return EXIT_SUCCESS;
}
