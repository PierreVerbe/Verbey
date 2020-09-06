		// biblio utilisaitons des manettes du mode PVP

#ifndef DEF_MANETTE
#define DEF_MANETTE

// prepros
#include "../types.h"

// protos

// protos

// initialise en fonction du num�ro du joystick
//void initialiserInput(Input *input, int numeroJoystick);
void ma_initialiserInput(Input *input, int utiliserJoystick1, int numeroJoystick1, int utiliserJoystick2, int numeroJoystick2);

// lib�re la m�moire allou�e
void ma_detruireInput(Input *input);

// r�cup�re les �v�nements
void ma_updateEvent(Input *input);

// gestion event manettes
void ma_gestion_event_manette(Input* input, MonJoueur* pjoueur1, MonJoueur* pjoueur2);



#endif // !DEF_MANETTE
