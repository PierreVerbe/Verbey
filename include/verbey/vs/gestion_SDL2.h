		// fct header gestion de la SDL2 du mode PVP


#ifndef DEF_BIB_GESTION_SDL
#define DEF_BIB_GESTION_SDL

// prepros
#include <string>
#include "verbey/types.h"


// protos

// init generale SDL2
MaFenetre* ge_Initialize(MaFenetre* pfenetre);

// init renderer
MaFenetre* ge_Initialize_renderer(MaFenetre* pfenetre);

// fermetture propre SDL2
void ge_Close(MaFenetre* pfenetre);

// creation des rendus images
SDL_Texture* ge_LoadTexture(MaFenetre* pfenetre, std::string file);





#endif // !DEF_BIB_GESTION_SDL

