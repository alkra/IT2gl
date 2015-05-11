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

#include "tests.h" // le temps du débogage

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
    /* DÉFINITION DE LA FENÊTRE */

    // taille de l'écran
    GLint larg_ecran = glutGet(GLUT_SCREEN_WIDTH),
            haut_ecran = glutGet(GLUT_SCREEN_HEIGHT);

    // taille de la fenêtre
    glutInitWindowSize(larg_ecran, haut_ecran);
    glutCreateWindow(NOM_APPLICATION);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // couleur d'effacement de la fenêtre
    glClearColor(0, 0, 0, 1);
}

GLvoid initialiser_projection(GLint largeur_fenetre, GLint hauteur_fenetre) {
    /* DÉFINITION DE LA VISION */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // définition de la zone de la fenêtre utilisée pour le dessin
    glViewport(0, 0, largeur_fenetre, hauteur_fenetre);
    // toute la fenêtre (comportement par défaut)

    // définition du volume de vision
    // voir aussi https://www.opengl.org/discussion_boards/showthread.php/132447-Relationship-between-glOrtho()-and-gluLookAt()
    static CPoint3f bas_gauche = graphe->getExtentLowerLeft(),
            haut_droit = graphe->getExtentUpperRight();
    static GLdouble ratio = largeur_fenetre/hauteur_fenetre;
    if(ratio > 1) { // plus large que haut
        glOrtho(bas_gauche.X, haut_droit.X,
                bas_gauche.X*ratio, haut_droit.X*ratio,
                haut_droit.Z, bas_gauche.Z);
    } else {
        glOrtho(bas_gauche.Y*ratio, haut_droit.Y*ratio,
                bas_gauche.Y, haut_droit.Y,
                -haut_droit.Z, bas_gauche.Z);
    }
}

Camera *camera = NULL;

GLvoid deplacer_oeil_x(GLfloat nouv) { camera->oeil.X += nouv; }
GLvoid deplacer_oeil_y(GLfloat nouv) { camera->oeil.Y += nouv; }
GLvoid deplacer_oeil_z(GLfloat nouv) { camera->oeil.Z += nouv; }
/*GLvoid deplacer_centre_x(GLfloat nouv) { camera->centre.X += nouv; }
GLvoid deplacer_centre_y(GLfloat nouv) { camera->centre.Y += nouv; }
GLvoid deplacer_centre_z(GLfloat nouv) { camera->centre.Z += nouv; }
GLvoid deplacer_verticale_x(GLfloat nouv) { camera->verticale.X += nouv; }
GLvoid deplacer_verticale_y(GLfloat nouv) { camera->verticale.Y += nouv; }
GLvoid deplacer_verticale_z(GLfloat nouv) { camera->verticale.Z += nouv; }*/// non implémenté

GLvoid dessiner_scene() {
    // effacement de la scène
    glClear(GL_COLOR_BUFFER_BIT);

    // réinitialisation de la matrice de vue
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // définition de la vue
    glTranslatef(-camera->oeil.X, -camera->oeil.Y, -camera->oeil.Z);

    // dessin
    TEST_DESSIN_REPERE
    dessiner_graphe(*graphe);
    dessiner_trains(*graphe);

    glFlush();
}

int main(int argc, char* argv[]) {
    // on lit le graphe
    ostream nul(0);
    CGraphe le_graphe = initialiser_graphe(nul);
    graphe = &le_graphe;

    // initialisation de GLUT
    glutInit(&argc, argv);
    initialiser_gl();

    // définition de la projection
    glutReshapeFunc(initialiser_projection);

    // initialisation de la caméra
    camera = new Camera;
    CAMERA_INIT(0, 0, 0, 0, 0, 0, 0, 1, 0)

    // dessin
    glutDisplayFunc(dessiner_scene);

    glutMainLoop();

    delete camera;
    return EXIT_SUCCESS;
}
