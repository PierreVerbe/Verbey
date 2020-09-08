		// code source des fct de calculs du mode PVP

// prepros
#include <math.h>

#include "include/verbey/vs/calculs.h"


// fonctions

double ca_norme(MonVecteur* pvecteur)
{
	// decla
	double norme = 0;

	// corps prg
	norme = sqrt((pvecteur->x * pvecteur->x) + (pvecteur->y * pvecteur->y));

	return norme;
}
//------------------------------------------------------------------------


void ca_plus(MonVecteur* pvecteur, MonVecteur* pajout)
{
	pvecteur->x = pvecteur->x + pajout->x;
	pvecteur->y = pvecteur->y + pajout->y;
}
//------------------------------------------------------------------------


void ca_moins(MonVecteur* pvecteur, MonVecteur* pajout)
{
	pvecteur->x = pvecteur->x - pajout->x;
	pvecteur->y = pvecteur->y - pajout->y;
}
//------------------------------------------------------------------------
