// code source des fonctions de gestion de la SDL2 du menu

// prepros
#include "../en-tetes/SDL2/SDL_mixer.h"

#include "include/verbey/bib_sdl.h"
#include "include/verbey/calculs.h"
#include "include/verbey/types.h"

#include "include/verbey/vs/gestion_SDL2.h"
#include "include/verbey/vs/init_donnees.h"
#include "include/verbey/vs/manette.h"
#include "include/verbey/vs/affichage.h"
#include "include/verbey/vs/balle.h"
#include "include/verbey/vs/grenade.h"
#include "include/verbey/vs/fct_jeu.h"
#include "include/verbey/vs/mine.h"



// fonctions

//compteur descendant personnalisable
short int compteur_down(short int cpt, short int maximum)
{
    if ((cpt >= 0) && (cpt<maximum)) cpt = cpt+1;

    else cpt = 0;

    return cpt;
}

// ---------------------------------------------------------------------------------------------------------

//compteur montant personnalisable
short int compteur_up(short int cpt, short int minimum, short int retour)
{
    if ((cpt>0) && (cpt< minimum)) cpt=cpt-1;

    else cpt=retour;

    return  cpt;
}

// ---------------------------------------------------------------------------------------------------------

//gestion bouton SON
short int ge_son(short int son)
{
    if (son ==1)
    {
        son =0;
        Mix_PauseMusic();
    }

    else
    {
        Mix_ResumeMusic();
        son = son+1;
    }

    return son;
}

//---------------------------------------------------------------------------------------------------------------

//mode PVP
short int mode_PVP(MaFenetre* pfenetre, short int compteur)
{

	/* decla et init */
	MonJoueur J1 = { 0 };				// init les donn�es du joueur1
	MonJoueur J2 = { 0 };				// init Joueur2
	short int victoire = 0;				// pas de joueur GG

	// SDL2 ***
	MesRects rects = { NULL };			// rectangle d'affichage
	MesTextures Textures = { NULL };	// texture des images

	// manette
	Input input;						// struture input manettes

	/* actions */

			// init
			ma_initialiserInput(&input, 1, 0, 1, 1);		// init touches manettes (espace memoire)
			init_pos_joueur(&J1, &J2);						// init emplacement depart joueurs
			init_joueur(&J1);								// init donn�es Joueur1	/ pos random -> fixe / 3 PV
			init_joueur(&J2);								// init donn�es J2
			af_texture_images(&Textures, pfenetre);			// def textures (images)

			// boucle -> fct
			while (victoire == 0)		// test si un joueur a GG
			{
				// event + calculs
				ma_updateEvent(&input);							// lecture event manettes
				ma_gestion_event_manette(&input, &J1, &J2);		// utilisation event manettes
				bordure(&J1);									// collision bordure (rebond bloquant) J1
				bordure(&J2);									// collision J2
				ba_test_tir(&J1, &J2);							// verif/test balles	(J1 -> J2)
				ba_test_tir(&J2, &J1);							// tir (J2 -> J1)
				degat(&J1);										// temps aff degat J1
				degat(&J2);										// degat J2
				gr_test_gre(&J1, &J2);							// verif/test grenades	(J1 -> J2)
				gr_test_gre(&J2, &J1);							// gre (J2 -> J1)
				gr_explo_grenade(&J1);							// temps explos gre J1
				gr_explo_grenade(&J2);							// explos J2
				mi_test_explos_mine(&J1, &J2);					// verif/test explo mines	(J1 -> J2)
				mi_test_explos_mine(&J2, &J1);					// mine (J2 -> J1)
				mi_explosion_mine(&J1);							// temps afficahge mine J1
				mi_explosion_mine(&J2);							// temps explos J2

				// aff
				af_rectangles(&rects, &J1, &J2);					// def rect zone d'affichage
				af_images(pfenetre, &Textures, &rects, &J1, &J2);	// place images dans rects sur arriere-plan
				SDL_RenderPresent(pfenetre->prenderer);				// aff images sur ecran

				// test victoire
				victoire = test_victoire(&J1, &J2);
			}

			aff_joueur_victoire(pfenetre, &Textures, victoire);		// affiche joueur gagnant ou fin de la partie

			ma_detruireInput(&input);
			compteur = 0;

	return compteur;
}

