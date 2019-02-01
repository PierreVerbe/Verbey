		// protos fct init données de base du jeu

#ifndef DEF_BIB_INIT_DONNEES
#define DEF_BIB_INIT_DONNEES

// prepros
#include "../../en-tetes/types.h"
#include "../../en-tetes/vs/constantes.h"

// protos
// init position joueur
void init_pos_joueur(MonJoueur* pj1, MonJoueur* pj2);			// init pos joueurs;

// init données joueur
void init_joueur(MonJoueur* pjoueur);

// init données balles
void init_balle(MonJoueur* pjoueur);

// init données grenades
void init_grenade(MonJoueur* pjoueur);

// init données mines
void init_mine(MonJoueur* pjoueur);



#endif // !DEF_BIB_INIT_DONNEES
