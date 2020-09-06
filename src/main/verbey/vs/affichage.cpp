		// code source affichage du mode PVP

// prepros
#include "include/verbey/types.h"

#include "include/verbey/vs/affichage.h"
#include "include/verbey/vs/gestion_SDL2.h"

//fonctions
// texture images
void af_texture_images(MesTextures* textures, MaFenetre* pfenetre)
{
	textures->Texture_fond = ge_LoadTexture(pfenetre, "image/maps/mapVS.jpg");							// creation image background (+nom de l'image de fond)
	textures->Texture_joueur1 = ge_LoadTexture(pfenetre, "image/skins/rouge.png");			// creation image personnage du joueur 1
	textures->Texture_joueur2 = ge_LoadTexture(pfenetre, "image/skins/bleu.png");			// creation image personnage du joueur 2
	textures->Texture_curs_joueur1 = ge_LoadTexture(pfenetre, "image/skins/shoot_rouge.png");			// creation image curseur du joueur 1
	textures->Texture_curs_joueur2 = ge_LoadTexture(pfenetre, "image/skins/shoot_bleu.png");			// creation image curseur du joueur 2
	textures->Texture_balle = ge_LoadTexture(pfenetre, "image/play/balle2.png");						// creation image balle des joueurs
	textures->Texture_grenade = ge_LoadTexture(pfenetre, "image/play/grenade.png");					// creation image grenade des joueurs
	textures->Texture_explosion = ge_LoadTexture(pfenetre, "image/play/explosion.png");				// creation image explosion
	textures->Texture_mine = ge_LoadTexture(pfenetre, "image/play/mine.png");					// creation image mine des joueurs
	textures->Texture_degat = ge_LoadTexture(pfenetre, "image/play/sang.png");								// creation image degat/sang des joueurs
	textures->Texture_victoire1 = ge_LoadTexture(pfenetre, "image/play/joueur_1_gagne.png");						// creation image victoire J1
	textures->Texture_victoire2 = ge_LoadTexture(pfenetre, "image/play/joueur_2_gagne.png");						// creation image victoire J2
	textures->Texture_gameover = ge_LoadTexture(pfenetre, "image/play/game_over.jpg");						// creation image fin de partie
	textures->Texture_vie1 = ge_LoadTexture(pfenetre, "image/play/coeur_1p.png");					// creation image 1 PV
	textures->Texture_vie2 = ge_LoadTexture(pfenetre, "image/play/coeur_2p.png");					// creation image 2 PV
	textures->Texture_vie3 = ge_LoadTexture(pfenetre, "image/play/coeur_3p.png");					// creation image 3 PV
}
// ---------------------------------------------------------------------------------------------------------


// zones d'affichages
void af_rectangles(MesRects* rects, MonJoueur* j1, MonJoueur* j2)
{
	// personnage
	SDL_Rect rect_joueur1 = { (int)j1->position.x - 33, (int)j1->position.y - 40, 66, 80 };					// rectangle d'affichage de la pos de l'image du joueur 1
	rects->rect_joueur1 = rect_joueur1;
	SDL_Rect rect_joueur2 = { (int)j2->position.x - 33, (int)j2->position.y - 40, 66, 80 };					// aff rect J2
	rects->rect_joueur2 = rect_joueur2;

	// curseur tir
	SDL_Rect rect_curseur_j1 = { (int)j1->curseur.x - 25, (int)j1->curseur.y - 25, 50, 50 };				// aff rect curseur J1
	rects->rect_curseur_j1 = rect_curseur_j1;
	SDL_Rect rect_curseur_j2 = { (int)j2->curseur.x - 25, (int)j2->curseur.y - 25, 50, 50 };				// aff rect curseur J2
	rects->rect_curseur_j2 = rect_curseur_j2;

	// balles
	SDL_Rect rect_balle1 = { (int)j1->arme.pos_balle.x - 15, (int)j1->arme.pos_balle.y - 7, 30, 14 };		// balle J1
	rects->rect_balle1 = rect_balle1;
	SDL_Rect rect_balle2 = { (int)j2->arme.pos_balle.x - 15, (int)j2->arme.pos_balle.y - 7, 30, 14 };		// balle J2
	rects->rect_balle2 = rect_balle2;

	// grenades
	SDL_Rect rect_grenade1 = { (int)j1->grenade.pos_grenade.x - 15, (int)j1->grenade.pos_grenade.y - 13, 30, 26 };		// grenade J1
	rects->rect_grenade1 = rect_grenade1;
	SDL_Rect rect_grenade2 = { (int)j2->grenade.pos_grenade.x - 15, (int)j2->grenade.pos_grenade.y - 13, 30, 26 };		// grenade J2
	rects->rect_grenade2 = rect_grenade2;

	// explosions grenades
	SDL_Rect rect_explosion_grenade1 = { (int)j1->grenade.pos_grenade.x - rayon_explosion, (int)j1->grenade.pos_grenade.y - rayon_explosion, rayon_explosion*2, rayon_explosion*2 };	// rectangle d'affichage de la pos de l'image de l'explosion
	rects->rect_explosion_grenade1 = rect_explosion_grenade1;
	SDL_Rect rect_explosion_grenade2 = { (int)j2->grenade.pos_grenade.x - rayon_explosion, (int)j2->grenade.pos_grenade.y - rayon_explosion, rayon_explosion*2, rayon_explosion*2 };	// rectangle d'affichage de la pos de l'image de l'explosion
	rects->rect_explosion_grenade2 = rect_explosion_grenade2;

	// mine
	SDL_Rect rect_mine1 = { (int)j1->mine.pos_mine.x - 10, (int)j1->mine.pos_mine.y - 10, 20, 20 };				// rectangle d'affichage de la pos de l'image de la mine
	rects->rect_mine1 = rect_mine1;
	SDL_Rect rect_mine2 = { (int)j2->mine.pos_mine.x - 10, (int)j2->mine.pos_mine.y - 10, 20, 20 };				// rectangle d'affichage de la pos de l'image de la mine
	rects->rect_mine2 = rect_mine2;

	// eplosion de la mine
	SDL_Rect rect_eplos_mine1 = { (int)j1->mine.pos_mine.x - rayon_explosion, (int)j1->mine.pos_mine.y - rayon_explosion, rayon_explosion*2, rayon_explosion*2 };		// rectangle d'affichage de la pos de l'image de l'explosion
	rects->rect_eplos_mine1 = rect_eplos_mine1;
	SDL_Rect rect_eplos_mine2 = { (int)j2->mine.pos_mine.x - rayon_explosion, (int)j2->mine.pos_mine.y - rayon_explosion, rayon_explosion*2, rayon_explosion*2 };		// rectangle d'affichage de la pos de l'image de l'explosion
	rects->rect_eplos_mine2 = rect_eplos_mine2;

	// degat
	SDL_Rect rect_degat1 = { (int)j1->position.x - 35, (int)j1->position.y - 35, 70, 70 };								// rectangle d'affichage de la pos de l'image des degats
	rects->rect_degat1 = rect_degat1;
	SDL_Rect rect_degat2 = { (int)j2->position.x - 35, (int)j2->position.y - 35, 70, 70 };								// rectangle d'affichage de la pos de l'image des degats
	rects->rect_degat2 = rect_degat2;

	// vie
	SDL_Rect rect_vie1 = { Spawn - Spawn/2, Spawn - Spawn/2, Spawn, Spawn };							// emplacement vie J1
	rects->rect_vie1 = rect_vie1;
	SDL_Rect rect_vie2 = { CteLargeurFenetre - Spawn - Spawn/2, Spawn - Spawn/2, Spawn, Spawn };		// emplacement vie j2
	rects->rect_vie2 = rect_vie2;
}
// ---------------------------------------------------------------------------------------------------------


// affichage des images
void af_images(MaFenetre* pfenetre, MesTextures* textures, MesRects* rects, MonJoueur* pj1, MonJoueur* pj2)
{
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_fond, NULL, NULL);									// aff fond
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_joueur1, NULL, &rects->rect_joueur1);					// aff perso J1
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_joueur2, NULL, &rects->rect_joueur2);					// aff perso J2
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_curs_joueur1, NULL, &rects->rect_curseur_j1);			// aff curseur J1
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_curs_joueur2, NULL, &rects->rect_curseur_j2);			// aff curseur J2
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_balle, NULL, &rects->rect_balle1);					// aff balle J1
	SDL_RenderCopy(pfenetre->prenderer, textures->Texture_balle, NULL, &rects->rect_balle2);					// aff balle J2
	if (pj1->grenade.etat == objet) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_grenade, NULL, &rects->rect_grenade1);				// aff grenade J1
	if (pj2->grenade.etat == objet) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_grenade, NULL, &rects->rect_grenade2);				// aff grenade J2
	if (pj1->grenade.etat == explos) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_explosion, NULL, &rects->rect_explosion_grenade1);	// aff explosion grenade J1
	if (pj2->grenade.etat == explos) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_explosion, NULL, &rects->rect_explosion_grenade2);	// aff explosion grenade J2
	if (pj1->mine.etat == objet) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_mine, NULL, &rects->rect_mine1);		// aff mine j1
	if (pj2->mine.etat == objet) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_mine, NULL, &rects->rect_mine2);		// aff mine j2
	if (pj1->mine.etat == explos) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_explosion, NULL, &rects->rect_eplos_mine1);		// aff explosion mine j1
	if (pj2->mine.etat == explos) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_explosion, NULL, &rects->rect_eplos_mine2);		// aff explosion mine j2
	if (pj1->degat != 0) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_degat, NULL, &rects->rect_degat1);		// aff degat j1
	if (pj2->degat != 0) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_degat, NULL, &rects->rect_degat2);		// aff degat j2
	if (pj1->pv == 3) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie3, NULL, &rects->rect_vie1);		// aff vie 1 j1
	if (pj1->pv == 2) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie2, NULL, &rects->rect_vie1);		// aff vie 2 j1
	if (pj1->pv == 1) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie1, NULL, &rects->rect_vie1);		// aff vie 3 j1
	if (pj2->pv == 3) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie3, NULL, &rects->rect_vie2);		// aff vie 1 j2
	if (pj2->pv == 2) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie2, NULL, &rects->rect_vie2);		// aff vie 2 j2
	if (pj2->pv == 1) SDL_RenderCopy(pfenetre->prenderer, textures->Texture_vie1, NULL, &rects->rect_vie2);		// aff vie 3 j2
}
// ---------------------------------------------------------------------------------------------------------


// aff joueur victoire / fin partie
void aff_joueur_victoire(MaFenetre* pfenetre, MesTextures* textures, short int victoire)
{
	if (victoire == 1)
        {
            SDL_RenderCopy(pfenetre->prenderer, textures->Texture_victoire1, NULL, NULL);	// aff victoire J1 plein ecran	//printf(" J1 a GG!\n");
            printf(" J1 a GG!\n");
        }
	else if (victoire == 2)
	{
	    SDL_RenderCopy(pfenetre->prenderer, textures->Texture_victoire2, NULL, NULL);       // aff victoire J2 plein ecran	//printf(" J2 a GG!\n");
	    printf(" J2 a GG!\n");
	}
	else SDL_RenderCopy(pfenetre->prenderer, textures->Texture_gameover, NULL, NULL);						// fin de partie(-1)	// printf(" *** Fin du jeu ***");
	SDL_RenderPresent(pfenetre->prenderer);																	// aff image sur ecran
	SDL_Delay(2000);
}
// ---------------------------------------------------------------------------------------------------------
