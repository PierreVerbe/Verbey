// fonction header gestion de la SDL2 du menu

#ifndef DEF_BIB_SDL
#define DEF_BIB_SDL

// prepros
#include "../en-tetes/bib_sdl.h"
#include "../en-tetes/SDL2/SDL_mixer.h"
#include "../en-tetes/types.h"

//compteur down
short int compteur_down(short int num, short int maximum);

//compteur up
short int compteur_up(short int num, short int minimum, short int retour);

//gestion bouton SON
short int ge_son(short int son);

//mode PVP
short int mode_PVP(MaFenetre* pfenetre, short int compteur);

#endif

