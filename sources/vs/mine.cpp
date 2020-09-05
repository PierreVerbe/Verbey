		// code source de l'utilisation de la mine

// prepros
#include "../../en-tetes/vs/calculs.h"
#include "../../en-tetes/vs/mine.h"

// fonctions
// init de base de la balle
void mi_mine_init(MonJoueur* pjoueur)
{
	if (pjoueur->mine.etat == vide)
	{
		pjoueur->mine.degat = 2;							// 2 degat
		pjoueur->mine.etat = objet;							// mine posee
		pjoueur->mine.pos_mine = pjoueur->position;			// init pos mine sur pos joueur
	}
}
// ---------------------------------------------------------------------------------------------------------


// gestion de la mine
void mi_test_explos_mine(MonJoueur* pj1, MonJoueur* pj2)
{
	// mine j1
	if (pj1->mine.etat == objet)
	{
		MonVecteur ME = { (pj1->mine.pos_mine.x - pj2->position.x), (pj1->mine.pos_mine.y - pj2->position.y) };		// veteur mine/joueur_adverse
		double N_BE = ca_norme(&ME);	// calc Norme mine/enemi

		// test mine explo
		if (N_BE < rayon_explosion)
		{
			pj2->pv -= pj1->mine.degat;		// si enemi touch� par la mine
			pj1->mine.etat = explos;		// pour affichage
			pj2->degat++;					// aff degat sur J2
		}
		else pj1->mine.etat = objet;
	}
}
// ---------------------------------------------------------------------------------------------------------


// affichage explosion mine
void mi_explosion_mine(MonJoueur* pjoueur)
{
	if (pjoueur->mine.etat == explos)
	{
		pjoueur->mine.temps_explos++;			// dur�e aff explosion
		if (pjoueur->mine.temps_explos > 100)	// temps aff explos
		{
			pjoueur->mine.pos_mine = { 0 };		// re-init pos -> angle sup gauche
			pjoueur->mine.etat = vide;			// pour fin affichage
		}
		else pjoueur->mine.etat = explos;		//  fin affichage -> re-init mine
	}
}
// ---------------------------------------------------------------------------------------------------------
