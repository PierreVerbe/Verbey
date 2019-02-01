		// code source de l'utilisation des manettes du mode PVP

// prepros
#include "../en-tetes/vs/manette.h"
#include "../en-tetes/vs/balle.h"
#include "../en-tetes/vs/grenade.h"
#include "../en-tetes/vs/mine.h"

// fonctions
// init des infos des manettes
void ma_initialiserInput(Input *input, int utiliserJoystick1, int numeroJoystick1, int utiliserJoystick2, int numeroJoystick2)	// pour 2 manette : 1 0 1 1
{
	input->nombreJoysticks = 0;

	if (utiliserJoystick1 == 1 && SDL_NumJoysticks() > numeroJoystick1)
		input->nombreJoysticks++;

	if (utiliserJoystick2 == 1 && numeroJoystick2 != numeroJoystick1 && SDL_NumJoysticks() > numeroJoystick2)
		input->nombreJoysticks++;

	// si il y a des joystick, on les alloue et initialise
	if (input->nombreJoysticks != 0)
	{
		SDL_JoystickEventState(SDL_ENABLE);		// active envent

		input->joystick = (InputJoystick*)malloc(input->nombreJoysticks * sizeof(InputJoystick));

		for (int i = 0; i<input->nombreJoysticks; i++)
		{
			input->joystick[i].joystick = SDL_JoystickOpen((i == 0) ? (numeroJoystick1) : (numeroJoystick2));
			input->joystick[i].numero = (i == 0) ? (numeroJoystick1) : (numeroJoystick2);


			input->joystick[i].boutons = (char*)malloc(SDL_JoystickNumButtons(input->joystick[i].joystick) * sizeof(char));
			input->joystick[i].axes = (int*)malloc(SDL_JoystickNumAxes(input->joystick[i].joystick) * sizeof(int));
			input->joystick[i].chapeaux = (int*)malloc(SDL_JoystickNumHats(input->joystick[i].joystick) * sizeof(int));

			for (int j = 0; j<SDL_JoystickNumButtons(input->joystick[i].joystick); j++)
				input->joystick[i].boutons[j] = 0;

			for (int j = 0; j<SDL_JoystickNumAxes(input->joystick[i].joystick); j++)
				input->joystick[i].axes[j] = 0;

			for (int j = 0; j<SDL_JoystickNumHats(input->joystick[i].joystick); j++)
				input->joystick[i].chapeaux[j] = 0;
		}
	}

	else
	{
		input->joystick = NULL;
	}
}
// ---------------------------------------------------------------------------------------------------------------


// libere espace utilisé pour infos manette
void ma_detruireInput(Input *input)
{
	if (input->joystick != NULL)
	{
		SDL_JoystickEventState(SDL_DISABLE); // desactive les événts du joystick

		for (int i = 0; i<input->nombreJoysticks; i++) // tant qu'un joystick est connecté
		{
			input->joystick[i].numero = 0;

			// on libère la mémoire
			free(input->joystick[i].boutons);
			//free(input->joystick[i].axes);
			free(input->joystick[i].chapeaux);
			SDL_JoystickClose(input->joystick[i].joystick);
		}

		free(input->joystick);
		input->joystick = NULL;
	}
}
// ---------------------------------------------------------------------------------------------------------------


// lecture event manette
void ma_updateEvent(Input *input)
{
	// decla et init
	static SDL_Event evenements; // en static car appelle plusieurs fois par seconde

								 // actions
	if (input->nombreJoysticks != 0) // on ne vérifie qu'une seule fois qu'un joystick existe
	{
		while (SDL_PollEvent(&evenements))
		{
			// on vérifie qu'un des joysticks est concerné
			if (input->joystick[0].numero == evenements.jbutton.which		// manette 1
				|| input->joystick[0].numero == evenements.jaxis.which
				|| input->joystick[0].numero == evenements.jhat.which
				|| input->joystick[1].numero == evenements.jbutton.which	// manette 2
				|| input->joystick[1].numero == evenements.jaxis.which
				|| input->joystick[1].numero == evenements.jhat.which)
			{
				switch (evenements.type)
				{
					// appuis buttons
				case SDL_JOYBUTTONDOWN:
					input->joystick[evenements.jbutton.which].boutons[evenements.jbutton.button] = 1;
					printf(" bouttons bas appuis\n");
					break;
					// relacher buttons
				case SDL_JOYBUTTONUP:
					input->joystick[evenements.jbutton.which].boutons[evenements.jbutton.button] = 0;
					printf(" bouttons haut appuis\n");
					break;
					// axes
				case SDL_JOYAXISMOTION:
					input->joystick[evenements.jaxis.which].axes[evenements.jaxis.axis] = evenements.jaxis.value;
					printf(" axe: appuis\n");
					break;
					// hat
				case SDL_JOYHATMOTION:
					input->joystick[evenements.jhat.which].chapeaux[evenements.jhat.hat] = evenements.jhat.value;
					printf(" axe: appuis\n");
					break;

				default:
					break;
				}
			}
		}
	}
	printf(" %d joystick connecte !!! \n", input->nombreJoysticks);		// aff nbr joy co
}
// ---------------------------------------------------------------------------------------------------------------


// gestion des events de la manette
void ma_gestion_event_manette(Input* input, MonJoueur* pjoueur1, MonJoueur* pjoueur2)
{
	// 1ere manette(0) liée au J1
		// bouttons J1
	if (input->joystick[0].boutons[5]) ba_tir(pjoueur1);						// RB		printf(" tir J1\n");
	if (input->joystick[0].boutons[3]) mi_mine_init(pjoueur1);					// Y		printf(" mine J1\n");
	if (input->joystick[0].boutons[7]) pjoueur1->pause = 1;						// start	printf(" pause J1\n");
	if (input->joystick[0].boutons[4]) gr_grenade(pjoueur1);					// LB		printf(" grenade J1\n");
	if (input->joystick[0].boutons[2]) pjoueur1->curseur = pjoueur1->position;	// X		printf(" centrage curseur J1\n");

		// analog droit deplacement joueur 1
	if (input->joystick[0].axes[4] > -10000) pjoueur1->position.y = pjoueur1->position.y + pjoueur1->vitesse;
	if (input->joystick[0].axes[4] < 10000) pjoueur1->position.y = pjoueur1->position.y - pjoueur1->vitesse;
	if (input->joystick[0].axes[3] > -10000) pjoueur1->position.x = pjoueur1->position.x + pjoueur1->vitesse;
	if (input->joystick[0].axes[3] < 10000) pjoueur1->position.x = pjoueur1->position.x - pjoueur1->vitesse;

		// analog gauche visée j1
	if (input->joystick[0].axes[1] > -10000) pjoueur1->curseur.y = pjoueur1->curseur.y + vitesse_curseur;
	if (input->joystick[0].axes[1] < 10000) pjoueur1->curseur.y = pjoueur1->curseur.y - vitesse_curseur;
	if (input->joystick[0].axes[0] > -10000) pjoueur1->curseur.x = pjoueur1->curseur.x + vitesse_curseur;
	if (input->joystick[0].axes[0] < 10000) pjoueur1->curseur.x = pjoueur1->curseur.x - vitesse_curseur;


	// 2eme manette(1) liée au J2
		// bouttons J2
	if (input->joystick[1].boutons[5]) ba_tir(pjoueur2);						// RB		printf(" tir J2\n");
	if (input->joystick[1].boutons[3]) mi_mine_init(pjoueur2);					// Y		printf(" mine J2\n");
	if (input->joystick[1].boutons[7]) pjoueur2->pause = 1;						// start	printf(" pause J2\n");
	if (input->joystick[1].boutons[4]) gr_grenade(pjoueur2);					// LB		printf(" grenade J2\n");
	if (input->joystick[1].boutons[2]) pjoueur2->curseur = pjoueur2->position;	// X		printf(" centrage curseur J2\n");

		// analog droit deplacement joueur 2
	if (input->joystick[1].axes[4] > -10000) pjoueur2->position.y = pjoueur2->position.y + pjoueur2->vitesse;
	if (input->joystick[1].axes[4] < 10000) pjoueur2->position.y = pjoueur2->position.y - pjoueur2->vitesse;
	if (input->joystick[1].axes[3] > -10000) pjoueur2->position.x = pjoueur2->position.x + pjoueur2->vitesse;
	if (input->joystick[1].axes[3] < 10000) pjoueur2->position.x = pjoueur2->position.x - pjoueur2->vitesse;

		// analog gauche visée j2
	if (input->joystick[1].axes[1] > -10000) pjoueur2->curseur.y = pjoueur2->curseur.y + vitesse_curseur;
	if (input->joystick[1].axes[1] < 10000) pjoueur2->curseur.y = pjoueur2->curseur.y - vitesse_curseur;
	if (input->joystick[1].axes[0] > -10000) pjoueur2->curseur.x = pjoueur2->curseur.x + vitesse_curseur;
	if (input->joystick[1].axes[0] < 10000) pjoueur2->curseur.x = pjoueur2->curseur.x - vitesse_curseur;

}
// ---------------------------------------------------------------------------------------------------------------
