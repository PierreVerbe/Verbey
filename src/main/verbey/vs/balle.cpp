		// code source balle du mode PVP

// prepros
#include "include/verbey/vs/balle.h"
#include "include/verbey/vs/calculs.h"

// fonctions
// init de base de la balle
void ba_tir(MonJoueur* pjoueur)
{
	if (pjoueur->arme.etat == vide)
	{
		pjoueur->arme.degat = 1;							// 1 degat
		pjoueur->arme.etat = objet;							// balle tiree
		pjoueur->arme.pos_balle = pjoueur->position;		// init pos balle sur pos joueur
		pjoueur->arme.pos_final_tir = pjoueur->curseur;		// init destination balle sur pos curseur
	}
}
// ---------------------------------------------------------------------------------------------------------


// gestion de la balle
void ba_test_tir(MonJoueur* pj1, MonJoueur* pj2)
{
	// tir j1
	if (pj1->arme.etat == objet)
	{
		MonVecteur AB = { (pj1->arme.pos_final_tir.x - pj1->arme.pos_balle.x), (pj1->arme.pos_final_tir.y - pj1->arme.pos_balle.y) };	// veteur curseur/balle
		double N = ca_norme(&AB);		// calc Norme AB

		MonVecteur BE = { (pj1->arme.pos_balle.x - pj2->position.x), (pj1->arme.pos_balle.y - pj2->position.y) };		// veteur balle/joueur_adverse
		double N_BE = ca_norme(&BE);	// calc Norme Balle/enemi

										// test cible (curseur) atteinte -> ~= 10 pixels
		if (N_BE < 10)
		{
			pj2->pv -= pj1->arme.degat;		// si enemi touch� par la balle
			pj1->arme.pos_balle = { 0 };	// re-init pos -> angle sup gauche
			pj1->arme.etat = vide;			// pour affichage
			pj2->degat++;					// aff degat sur j2
		}
		else	// deplacement de la balle jusqu'a ca cible
		{
			pj1->arme.etat = objet;

			AB.x = AB.x / N * vitesse_balle;
			AB.y = AB.y / N * vitesse_balle;

			ca_plus(&pj1->arme.pos_balle, &AB);
			if (N < 5)
			{
				pj1->arme.pos_balle = { 0 };	// re-init pos -> angle sup gauche
				pj1->arme.etat = vide;
			}
		}
	}
}
