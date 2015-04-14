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

#include "dessin.h"

GLvoid dessiner_graphe(const CGraphe &graphe) {
    std::vector<CArc> arcs = graphe.list_arc;
    std::vector<CSommet> sommets = graphe.list_sommet;
    std::vector<CPointAnnexe> pts_annexes = graphe.list_point_annexe;

    CSommet *sommet_ini = NULL, *sommet_fin = NULL;
    for(int i = 0 ; i < graphe.nb_arc ; i++) {
        sommet_ini = &sommets[arcs[i].id_sommet_ini];
        sommet_fin = &sommets[arcs[i].id_sommet_fin];

        glBegin(GL_LINE_STRIP);

        // point de départ
        glVertex3f(sommet_ini->X, sommet_ini->Z, -sommet_ini->Y);

        // point d'arrivée
        glVertex3f(sommet_fin->X, sommet_fin->Z, -sommet_fin->Y);

        glEnd();
    }
}
