		// fct d'init des données de base du jeu

// prepros
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../en-tetes/vs/init_donnees.h"


// fonctions

void init_pos_joueur(MonJoueur* pj1, MonJoueur* pj2)			// init pos joueurs	fixes
{
	srand(time(NULL));
	pj1->position.x = Spawn;
	pj1->position.y = CteHauteurFenetre - Spawn;

	pj2->position.x = CteLargeurFenetre - Spawn;
	pj2->position.y = Spawn;
}
// ----------------------------------------------------------------------------------------------------------


void init_joueur(MonJoueur* pjoueur)
{
	pjoueur->pv = PV_base;
	pjoueur->vitesse = vitesse_base_joueur;
	pjoueur->curseur = pjoueur->position;
	pjoueur->degat = 0;
	init_balle(pjoueur);
	init_grenade(pjoueur);
	init_mine(pjoueur);
}
// ----------------------------------------------------------------------------------------------------------


void init_balle(MonJoueur* pjoueur)
{
	pjoueur->arme.degat = 0;
	pjoueur->arme.etat = vide;
	pjoueur->arme.pos_balle = { NULL };
	pjoueur->arme.pos_final_tir = { NULL };
}
// ----------------------------------------------------------------------------------------------------------


void init_grenade(MonJoueur* pjoueur)
{
	pjoueur->grenade.degat = 0;
	pjoueur->grenade.etat = vide;
	pjoueur->grenade.pos_grenade = { NULL };
	pjoueur->grenade.pos_final_gre = { NULL };
	pjoueur->grenade.temps_explos = 0;
	pjoueur->grenade.nbr_gre = 0;
}
// ----------------------------------------------------------------------------------------------------------


void init_mine(MonJoueur* pjoueur)
{
	pjoueur->mine.degat = 0;
	pjoueur->mine.etat = vide;
	pjoueur->mine.pos_mine = { NULL };
	pjoueur->mine.temps_explos = 0;
	pjoueur->mine.nbr_mine = 0;
}
// ----------------------------------------------------------------------------------------------------------
