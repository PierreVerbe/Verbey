		// code source des fonctions de gestion de la SDL2 du mode PVP

// prepros
#include "../../en-tetes/vs/gestion_SDL2.h"


// fonctions

MaFenetre* ge_Initialize(MaFenetre* pfenetre)
{
	// init SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) != 0)
	{
		printf(" *SDL* ne peut pas etre initialisee! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	// init SDL2_image
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;				// definition pour .png	& .jpg	-> ++ ici
	if (!(IMG_Init(imgFlags) & imgFlags))					// init SDL2_images + test
	{
		printf(" *SDL_image* ne peut pas etre init! SDL_image Error: %s\n", IMG_GetError());
		return NULL;
	}

	//initialisation SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// JOY: autorise les �v�nements pour les joysticks
	SDL_JoystickEventState(SDL_ENABLE);

	// creation window
	pfenetre->pwindow = SDL_CreateWindow(" Mode PVP_2joueurs *Verbey* ",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,					// pas de position fixe de la fenetre
		CteLargeurFenetre, CteHauteurFenetre, SDL_WINDOW_FULLSCREEN);			// ecran de taille fixe avec bordure visible

	// test creation window
	if (pfenetre->pwindow == NULL)
	{
		printf(" *Fenetre* ne peut pas etre creee! SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	// changement de l'icone de la fenetre
	SDL_SetWindowIcon(pfenetre->pwindow, SDL_LoadBMP("image/icone.bmp"));	// changer icon

	return pfenetre;
}
// ---------------------------------------------------------------------------------------------------------


MaFenetre* ge_Initialize_renderer(MaFenetre* pfenetre)
{
	// creation renderer
	pfenetre->prenderer = SDL_CreateRenderer(pfenetre->pwindow, -1, SDL_RENDERER_ACCELERATED);

	// test creation renderer
	if (pfenetre->prenderer == NULL)
	{
		printf(" *Renderer* ne peut pas etre cree! SDL Error: %s\n", SDL_GetError());
		return NULL;
	}

	// appliquer un fond noir sur le renderer
	SDL_SetRenderDrawColor(pfenetre->prenderer, 0, 0, 0, 255);		// creer fond noir (plein)

	return pfenetre;
}
// ---------------------------------------------------------------------------------------------------------


void ge_Close(MaFenetre* pfenetre)
{
	// + fermer le joystick
	SDL_DestroyRenderer(pfenetre->prenderer);
	pfenetre->pwindow = NULL;
	SDL_DestroyWindow(pfenetre->pwindow);

	SDL_Quit();
}
// ---------------------------------------------------------------------------------------------------------


// transformation des images (surface en texture)
SDL_Texture* ge_LoadTexture(MaFenetre* pfenetre, std::string file)
{
	// decla et init
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(file.c_str());		// type structure -> .c_str() pour referencer � l'image .png

	// test
	if (loadedSurface == NULL)
		printf(" impossible de charger l'image *%s* ! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	else
	{
		newTexture = SDL_CreateTextureFromSurface(pfenetre->prenderer, loadedSurface);
		if (newTexture == NULL) printf(" impossible de creer la texture depuis *%s* ! SDL Error: %s\n", file.c_str(), SDL_GetError());

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
// ---------------------------------------------------------------------------------------------------------
