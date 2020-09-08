		// code source gestion grenades mode PVP

// prepros
#include <SDL2/SDL_mixer.h>

#include "verbey/vs/calculs.h"
#include "verbey/vs/grenade.h"

// focntions
// init de base de la balle
void gr_grenade(MonJoueur* pjoueur)
{
	if (pjoueur->grenade.etat == vide)
	{
		pjoueur->grenade.degat = 2;								// 2 degats
		pjoueur->grenade.etat = objet;							// grenade lancee
		pjoueur->grenade.pos_grenade = pjoueur->position;		// init pos grenade sur pos joueur
		pjoueur->grenade.pos_final_gre = pjoueur->curseur;		// init destination grenade sur pos curseur
		pjoueur->grenade.temps_explos = 0;						// temps d'afficahge de l'explo
		pjoueur->grenade.nbr_gre++;								// compte le nombre de grenade lanc�es
	}
}
// ---------------------------------------------------------------------------------------------------------


// gestion de la grenade
void gr_test_gre(MonJoueur* pj1, MonJoueur* pj2)
{
    // chargement son
   // Mix_Chunk *play_explosion = Mix_LoadWAV("son/play/action/explosion.wav");

	// grenade j1
	if (pj1->grenade.etat == objet)

	{
		MonVecteur FD = { (pj1->grenade.pos_final_gre.x - pj1->grenade.pos_grenade.x), (pj1->grenade.pos_final_gre.y - pj1->grenade.pos_grenade.y) };	// veteur curseur/balle
		double NG = ca_norme(&FD);		// calc Norme FD2 (pos gre final/depart)

		if (NG < 5)
		{
			pj1->grenade.etat = explos;
			pj1->grenade.pos_grenade = pj1->grenade.pos_final_gre;

			MonVecteur GE = { (pj1->grenade.pos_grenade.x - pj2->position.x), (pj1->grenade.pos_grenade.y - pj2->position.y) };		// veteur grenade/joueur_adverse
			double N_GE = ca_norme(&GE);		// calc Norme grenade/enemi

			if (N_GE < rayon_explosion)
			{
				pj2->pv -= pj1->grenade.degat;	    // si enemi touch� par l'eplosion de la grenade
				pj2->degat++;					    // aff degat sur J2
				//Mix_PlayChannel(-1, play_explosion, 0);  // son
			}
		}

		else		// deplacement de la grenade jusqu'a ca cible
		{
			pj1->grenade.etat = objet;
			FD.x = FD.x / NG * vitesse_balle;
			FD.y = FD.y / NG * vitesse_balle;
			ca_plus(&pj1->grenade.pos_grenade, &FD);
		}
	}

}
// ---------------------------------------------------------------------------------------------------------


// affichage explosion grenade
void gr_explo_grenade(MonJoueur* pjoueur)
{
	if (pjoueur->grenade.etat == explos)
	{
		pjoueur->grenade.temps_explos++;
		if (pjoueur->grenade.temps_explos > 100)		// fin temps explos
		{
			pjoueur->grenade.pos_grenade = { 0 };	// re-init pos -> angle sup gauche
			pjoueur->grenade.temps_explos = 0;
			pjoueur->grenade.etat = vide;
		}
	}
	else pjoueur->grenade.etat == explos;
}
// -----------------------------------------------------------------
