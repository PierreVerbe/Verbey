		// Mode_PVP_2_joueurs => a transformer en fonction pour envoi dans code "menu"

	/*  Ce mode de jeu du VERBEY se joue avec 2 manettes
		le but est de tuer son adversaire !	*/

// prepros
#include "../../en-tetes/types.h"
#include "../../en-tetes/calculs.h"
#include "../../en-tetes/vs/gestion_SDL2.h"
#include "../../en-tetes/vs/init_donnees.h"
#include "../../en-tetes/vs/manette.h"
#include "../../en-tetes/vs/affichage.h"
#include "../../en-tetes/vs/balle.h"
#include "../../en-tetes/vs/grenade.h"
#include "../../en-tetes/vs/fct_jeu.h"
#include "../../en-tetes/vs/mine.h"


// corps du prg
int main(int argc, char* args[])
{
	/* decla et init */
	MonJoueur J1 = { 0 };				// init les données du joueur1
	MonJoueur J2 = { 0 };				// init Joueur2
	short int victoire = 0;				// pas de joueur GG

	// SDL2 ***
	MaFenetre Fenetre = { NULL };		// emplacement de la creation de la Fenetre et du renderer
	MesRects rects = { NULL };			// rectangle d'affichage
	MesTextures Textures = { NULL };	// texture des images

	// manette
	Input input;						// struture input manettes

	/* actions */
	if (ge_Initialize(&Fenetre) != NULL)				// -> window
	{
		if (ge_Initialize_renderer(&Fenetre) != NULL)	// -> renderer
		{
			// init
			ma_initialiserInput(&input, 1, 0, 1, 1);		// init touches manettes (espace memoire)
			init_joueur(&J1);								// init données Joueur1	/ pos random -> fixe / 3 PV
			init_joueur(&J2);								// init données J2
			af_texture_images(&Textures, &Fenetre);			// def textures (images)

			// boucle -> fct
			while (victoire == 0)		// test si un joueur a GG
			{
				// event + calculs
				ma_updateEvent(&input);							// lecture event manettes
				ma_gestion_event_manette(&input, &J1, &J2);		// utilisation event manettes
				ba_test_tir(&J1, &J2);							// verif/test balles
				gr_test_gre(&J1, &J2);							// verif/test grenades
				gr_explo_gre(&J1, &J2);							// temps explosion grenade
				mi_test_explos_mine(&J1, &J2);					// verif/test explo mines
				mi_explos_mine(&J1, &J2);						// temps afficahge mine

				// aff
				af_rectangles(&rects, &J1, &J2);					// def rect zone d'affichage
				af_images(&Fenetre, &Textures, &rects, &J1, &J2);	// place images dans rects sur arriere-plan
				SDL_RenderPresent(Fenetre.prenderer);				// aff images sur ecran

				// test victoire
				victoire = test_victoire(&J1, &J2);
			}

			// affichage -> fct
			if (victoire == 1) printf(" J1 a GG!\n");
			else printf(" J2 a GG!\n");
			if (victoire == -1) printf(" *** Fin du jeu ***");
			getchar();

			ma_detruireInput(&input);		// libere mem manettes
			ge_Close(&Fenetre);		// fermetture propre SDL2
		}
	}
	return 0;
}
