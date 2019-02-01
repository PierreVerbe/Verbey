		// biblio types du mode PVP

#ifndef DEF_TYPES
#define DEF_TYPES

// prepros global
#include <stdio.h>
#include <stdlib.h>
#include "../en-tetes/SDL2/SDL.h"
#include "../en-tetes/SDL2/SDL_image.h"
#include "../en-tetes/SDL2/SDL_mixer.h"
#include "../en-tetes/vs/constantes.h"

// Types enumerations ___ *********************

	typedef enum { vide, objet, explos } etat_arme;		// etat de l'arme (pour affichage explosion)

	typedef enum { droite, gauche, haut, bas, defaut} direction_joueur;	// enumeration des direction que peut prendre le joueur


// Types structures ___ *********************

	typedef struct				// type vecteur
	{
		double x;
		double y;
	} MonVecteur;


	typedef struct				// type arme
	{
		short int degat;
		MonVecteur pos_balle;			// pos de la balle
		MonVecteur pos_final_tir;		// pos joueur au moment du tir
		etat_arme etat;					// pour visu
	} MonArme;

	typedef struct				// type arme grenade
	{
		short int degat;
		MonVecteur pos_grenade;			// pos de la balle
		MonVecteur pos_final_gre;		// pos joueur au moment du tir
		etat_arme etat;					// pour explosion
		short int temps_explos;			// temps d'affichage de l'explosion < 50
		short int nbr_gre;				// nombre max de grenades
		//bool tir_actif;					// si balle/ grenade/ mine lancée
	} MaGrenade;

	typedef struct				// type arme balle
	{
		short int degat;
		MonVecteur pos_mine;			// pos de la balle
		etat_arme etat;					// pour explosion
		short int temps_explos;			// temps d'affichage de l'explosion < 50
		short int nbr_mine;				// nombre max de mines
		//bool tir_actif;					// si balle/ grenade/ mine lancée
	} MaMine;

	typedef struct				// type joueur
	{
		MonVecteur position;
		MonVecteur curseur;
		double vitesse;
		short int pv;
		MonArme arme;					// type arme -> arme_active
		MaGrenade grenade;
		MaMine mine;
		short int pause;				// "start"
		short int degat;
	} MonJoueur;




// SDL2 ___ *********************

	typedef struct {			// reference fenetre
		SDL_Window* pwindow;
		SDL_Renderer* prenderer;
	} MaFenetre;

	typedef struct {							// zones d'affichages des images
		SDL_Rect rect_joueur1;
		SDL_Rect rect_joueur2;
		SDL_Rect rect_curseur_j1;
		SDL_Rect rect_curseur_j2;
		SDL_Rect rect_balle1;
		SDL_Rect rect_balle2;
		SDL_Rect rect_grenade1;
		SDL_Rect rect_grenade2;
		SDL_Rect rect_explosion_grenade1;
		SDL_Rect rect_explosion_grenade2;
		SDL_Rect rect_mine1;
		SDL_Rect rect_mine2;
		SDL_Rect rect_eplos_mine1;
		SDL_Rect rect_eplos_mine2;
		SDL_Rect rect_degat1;
		SDL_Rect rect_degat2;
		SDL_Rect rect_vie1;
		SDL_Rect rect_vie2;
	} MesRects;

	typedef struct {							// textures des images
		SDL_Texture* Texture_fond;
		SDL_Texture* Texture_joueur1;
		SDL_Texture* Texture_joueur2;
		SDL_Texture* Texture_curs_joueur1;
		SDL_Texture* Texture_curs_joueur2;
		SDL_Texture* Texture_balle;
		SDL_Texture* Texture_grenade;
		SDL_Texture* Texture_explosion;
		SDL_Texture* Texture_mine;
		SDL_Texture* Texture_degat;
		SDL_Texture* Texture_victoire1;
		SDL_Texture* Texture_defaite1;
		SDL_Texture* Texture_victoire2;
		SDL_Texture* Texture_gameover;
		SDL_Texture* Texture_vie1;
		SDL_Texture* Texture_vie2;
		SDL_Texture* Texture_vie3;
	} MesTextures;



// Manette ___ *********************

/* structure qui gère un joystick */
	typedef struct
	{
		SDL_Joystick *joystick;
		char *boutons;
		int *axes;
		int *chapeaux;
		int numero;
	} InputJoystick;

	/* la structure qui gère les événements */
	typedef struct
	{
		InputJoystick *joystick;	// pointeur car il y a plusieurs joysticks
		int nombreJoysticks;		// sert à détruire à la fin
	} Input;



#endif // !DEF_TYPES

