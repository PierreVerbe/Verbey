		// code source des focntions du jeu du mode PVP

// prepros
#include "../../en-tetes/types.h"
#include "../../en-tetes/vs/fct_jeu.h"

// fonctions
// test de victoire
int test_victoire(MonJoueur* pjoueur1, MonJoueur* pjoueur2)
{
	// decla et init
	short int victoire = 0;

	// actions
	if (pjoueur1->pause == 1 || pjoueur2->pause == 1) victoire = -1;
	else victoire = 0;

	if (pjoueur1->pv <= 0) victoire = 2;
	else if (pjoueur2->pv <= 0) victoire = 1;

	return victoire;
}
// ---------------------------------------------------------------------------------------------------------


// gestion aff degat sur joueur
void degat(MonJoueur* pjoueur)
{
	if (pjoueur->degat != 0)
	{
		if(pjoueur->degat > 100) pjoueur->degat = 0;		// temps aff degat
		else pjoueur->degat++;
	}
}
// ---------------------------------------------------------------------------------------------------------


// collision bordure
void bordure(MonJoueur* pjoueur)
{
	// joueur
	if (pjoueur->position.x <= 0) pjoueur->position.x = CollisionMur;
	if (pjoueur->position.x >= CteLargeurFenetre) pjoueur->position.x = CteLargeurFenetre - CollisionMur;
	if (pjoueur->position.y <= 0) pjoueur->position.y = CollisionMur;
	if (pjoueur->position.y >= CteHauteurFenetre) pjoueur->position.y = CteHauteurFenetre - CollisionMur;

	// viseur
	if (pjoueur->curseur.x <= 0) pjoueur->curseur.x = CollisionMur;
	if (pjoueur->curseur.x >= CteLargeurFenetre) pjoueur->curseur.x = CteLargeurFenetre - CollisionMur;
	if (pjoueur->curseur.y <= 0) pjoueur->curseur.y = CollisionMur;
	if (pjoueur->curseur.y >= CteHauteurFenetre) pjoueur->curseur.y = CteHauteurFenetre - CollisionMur;

	/* armes */
}
// ---------------------------------------------------------------------------------------------------------
