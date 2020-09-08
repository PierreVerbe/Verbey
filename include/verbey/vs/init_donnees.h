		// protos fct init donn�es de base du jeu

#ifndef DEF_BIB_INIT_DONNEES
#define DEF_BIB_INIT_DONNEES

// prepros
#include "../types.h"
#include "../constantes.h"

// protos
// init position joueur
void init_pos_joueur(MonJoueur* pj1, MonJoueur* pj2);			// init pos joueurs;

// init donn�es joueur
void init_joueur(MonJoueur* pjoueur);

// init donn�es balles
void init_balle(MonJoueur* pjoueur);

// init donn�es grenades
void init_grenade(MonJoueur* pjoueur);

// init donn�es mines
void init_mine(MonJoueur* pjoueur);



#endif // !DEF_BIB_INIT_DONNEES
