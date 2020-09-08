		// biblio grenade mode PVP

#ifndef DEF_GRENADE
#define DEF_GRENADE

// prepros
#include <SDL2/SDL_mixer.h>

#include "verbey/types.h"



// protos
// init grenade
void gr_grenade(MonJoueur* pjoueur);

// test explo gre
void gr_test_gre(MonJoueur* pj1, MonJoueur* pj2);

// aff explos gre assemblage fct
void gr_explo_grenade(MonJoueur* pjoueur);


#endif // !DEF_GRENADE

