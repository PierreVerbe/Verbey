		// biblio utilisation de la mine du mode PVP

#ifndef DEF_MINE
#define DEF_MINE

// prepros
#include "../types.h"

// protos
// init mine
void mi_mine_init(MonJoueur* pjoueur);

// test de l'explosion de la mine
void mi_test_explos_mine(MonJoueur* pj1, MonJoueur* pj2);

// affichage explos mine essamblege fct
void mi_explosion_mine(MonJoueur* pjoueur);


#endif // !DEF_MINE

