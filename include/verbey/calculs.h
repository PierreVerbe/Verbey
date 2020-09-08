// fichier header de calculs du mode PVP

#ifndef DEF_BIB_CALCULS
#define DEF_BIB_CALCULS

// prepros
#include "types.h"

// protos
// calcul la norme du vecteur
double ca_norme(MonVecteur* pvecteur);

// addition de vecteurs
void ca_plus(MonVecteur* pvecteur, MonVecteur* pajout);

// soustraction de vecteurs
void ca_moins(MonVecteur* pvecteur, MonVecteur* pajout);


#endif // !DEF_BIB_CALCULS

