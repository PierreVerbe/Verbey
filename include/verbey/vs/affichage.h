		// biblio affichage images du mode PVP

#ifndef DEF_AFFICHAGE
#define DEF_AFFICHAGE

// prepros
#include "../types.h"

//protos
// texture images + emplacements
void af_texture_images(MesTextures* textures, MaFenetre* pfenetre);

// rectangles images
void af_rectangles(MesRects* rects, MonJoueur* j1, MonJoueur* j2);

// affichage des images
void af_images(MaFenetre* pfenetre, MesTextures* textures, MesRects* rects, MonJoueur* pj1, MonJoueur* pj2);

// aff victoire joueur / fin partie
void aff_joueur_victoire(MaFenetre* pfenetre, MesTextures* textures, short int victoire);


#endif // !DEF_AFFICHAGE

