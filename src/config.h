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

#ifndef CONFIG_H
#define CONFIG_H

#include "_api/CPoint3f.h"

#include <string>
#define CHEMIN_DATA std::string("C:\\Users\\Alban\\IT2\\VALILAB\\OpenGL\\projet\\data\\")

struct Camera {
    CPoint3f oeil;//, centre, verticale; -> non implémenté
};

#define NOM_APPLICATION "Casey Jr."
enum Projection { ORTHO };

struct Config_params {
    /* INITIALISATION */
    int init_largeur_fenetre;
    int init_hauteur_fenetre;
    char* init_titre_fenetre;
    Projection init_projection;
    float init_camera_oeil_x;
    float init_camera_oeil_y;
    float init_camera_oeil_z;
    /*float init_camera_centre_x;
    float init_camera_centre_y;
    float init_camera_centre_z;
    float init_camera_verticale_x;
    float init_camera_verticale_y;
    float init_camera_verticale_z;*/// non implémenté
};

#define CAMERA_INIT(ox, oy, oz, cx, cy, cz, ux, uy, uz) \
    camera->oeil.X = ox;\
    camera->oeil.Y = oy;\
    camera->oeil.Z = oz;\
    /*camera->centre.X = cx;\
    camera->centre.Y = cy;\
    camera->centre.Z = cz;\
    camera->verticale.X = ux;\
    camera->verticale.Y = uy;\
    camera->verticale.Z = uz; // au moins pour les tests*/// non implémenté

#endif // CONFIG_H
