#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "../en-tetes/SDL2/SDL.h"
#include "../en-tetes/SDL2/SDL_image.h"
#include "../en-tetes/SDL2/SDL_mixer.h"

#include "include/verbey/bib_sdl.h"
//#include "include/verbey/calculs.h"
#include "include/verbey/constante.h"
//#include "include/verbey/constantes.h"
#include "include/verbey/types.h"

#include "include/verbey/vs/affichage.h"
#include "include/verbey/vs/balle.h"
#include "include/verbey/vs/calculs.h"
#include "include/verbey/vs/constantes.h"
#include "include/verbey/vs/fct_jeu.h"
#include "include/verbey/vs/gestion_SDL2.h"
#include "include/verbey/vs/grenade.h"
#include "include/verbey/vs/init_donnees.h"
#include "include/verbey/vs/manette.h"
#include "include/verbey/vs/mine.h"

//dimentions ecran
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// declaration et initialisation des variables
short int compteur = 1;
short int compteur_help = 1;
short int num = 0;
short int num_mode =0;
short int valide = 0;
int fullscreen = 0;
short int son = 1;

short int selection_mode =0;
short int selection_map =0;
short int selection_j1 =0;
short int selection_j2 = 0;

SDL_Surface* nom1 = NULL;

SDL_Event event;
SDL_Event event_help;

//Programme SDL2
int main( int argc, char* args[] )
{
    printf("fenetre ");
    MaFenetre Fenetre = { NULL };
    if(ge_Initialize(&Fenetre) != NULL)
    {
        if(ge_Initialize_renderer(&Fenetre) != NULL)
        {


        //creation fenetre
             if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 )
            {
                fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
                return -1;
            }

            //initialisation SDL mixer
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

            // chargement musiques et sons
            Mix_Music *backgroundSound = Mix_LoadMUS("son/fond.mp3");
            Mix_Chunk *clic = Mix_LoadWAV("son/switch.wav");

            //sons debut
            Mix_Chunk *pret = Mix_LoadWAV("son/play/pret.wav");
            Mix_Chunk *decomptage = Mix_LoadWAV("son/play/3_2_1.wav");
            Mix_Chunk *partez = Mix_LoadWAV("son/play/partez.wav");

            //son fond
            Mix_Chunk *duel = Mix_LoadWAV("son/mode/duel.wav");
            Mix_Chunk *survie = Mix_LoadWAV("son/mode/rester_en_vie.wav");


            // debut musique fond
            Mix_PlayMusic(backgroundSound, -1); // jouer en boucle


            // Cr�ation de la fen�tre
            SDL_Window* pWindow = NULL;
            pWindow = SDL_CreateWindow("La super fenetre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);

            //Load icone
            SDL_SetWindowIcon(pWindow, SDL_LoadBMP("image/icone.bmp"));


            //boucle programme
            if( Fenetre.pwindow )
            {

                //creation renderer
                //SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Cr�ation d'un SDL_Renderer utilisant l'acc�l�ration mat�rielle

                //chargement des images
                // image 1
                SDL_Surface* pSprite = IMG_Load("image/menu/menu_jeu(play_select).jpg");
                SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite);
                SDL_Rect dest = { SCREEN_WIDTH/2 - pSprite->w/2,SCREEN_HEIGHT/2 - pSprite->h/2, pSprite->w, pSprite->h};

                // image 2
                SDL_Surface* pSprite2 = IMG_Load("image/menu/menu_jeu(mode_select).jpg");
                SDL_Texture* pTexture2 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite2);
                SDL_Rect dest2 = { SCREEN_WIDTH/2 - pSprite2->w/2,SCREEN_HEIGHT/2 - pSprite2->h/2, pSprite2->w, pSprite2->h};

                // image 3
                SDL_Surface* pSprite3 = IMG_Load("image/menu/menu_jeu(option_select).jpg");
                SDL_Texture* pTexture3 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite3);
                SDL_Rect dest3 = { SCREEN_WIDTH/2 - pSprite3->w/2,SCREEN_HEIGHT/2 - pSprite3->h/2, pSprite3->w, pSprite3->h};

                // image 4
                SDL_Surface* pSprite4 = IMG_Load("image/menu/menu_jeu(help_select).jpg");
                SDL_Texture* pTexture4 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite4);
                SDL_Rect dest4 = { SCREEN_WIDTH/2 - pSprite4->w/2,SCREEN_HEIGHT/2 - pSprite4->h/2, pSprite4->w, pSprite4->h};

                // image 4
                SDL_Surface* pSprite5 = IMG_Load("image/menu/menu_jeu(son_select).jpg");
                SDL_Texture* pTexture5 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite5);
                SDL_Rect dest5 = { SCREEN_WIDTH/2 - pSprite5->w/2,SCREEN_HEIGHT/2 - pSprite5->h/2, pSprite5->w, pSprite5->h};

                //chargement image help
                // image 4
                SDL_Surface* pSprite6 = IMG_Load("image/help/help.jpg");
                SDL_Texture* pTexture6 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite6);
                SDL_Rect dest6 = { SCREEN_WIDTH/2 - pSprite6->w/2,SCREEN_HEIGHT/2 - pSprite6->h/2, pSprite6->w, pSprite6->h};

                //chargement image mode
                //image 1
                SDL_Surface* pSprite_mode1 = IMG_Load("image/mode/mode_skins.jpg");
                SDL_Texture* pTexture_mode1 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode1);
                SDL_Rect dest_mode1 = { SCREEN_WIDTH/2 - pSprite_mode1->w/2,SCREEN_HEIGHT/2 - pSprite_mode1->h/2, pSprite_mode1->w, pSprite_mode1->h};

                //image 2
                SDL_Surface* pSprite_mode2 = IMG_Load("image/mode/mode_maps.jpg");
                SDL_Texture* pTexture_mode2 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode2);
                SDL_Rect dest_mode2 = { SCREEN_WIDTH/2 - pSprite_mode2->w/2,SCREEN_HEIGHT/2 - pSprite_mode2->h/2, pSprite_mode2->w, pSprite_mode2->h};

                //image 3
                SDL_Surface* pSprite_mode3 = IMG_Load("image/mode/mode_mode_jeu.jpg");
                SDL_Texture* pTexture_mode3 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode3);
                SDL_Rect dest_mode3 = { SCREEN_WIDTH/2 - pSprite_mode3->w/2,SCREEN_HEIGHT/2 - pSprite_mode3->h/2, pSprite_mode3->w, pSprite_mode3->h};

                //Chargement image mode mode de jeu
                //1VS1
                SDL_Surface* pSprite_mode_1vs1 = IMG_Load("image/mode/mode_jeu/1vs1.png");
                SDL_Texture* pTexture_mode_1vs1 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode_1vs1);
                SDL_Rect dest_mode_1vs1 = { POS_NOM_X, POS_NOM_Y, pSprite_mode_1vs1->w, pSprite_mode_1vs1->h};
                //survie
                SDL_Surface* pSprite_mode_survie = IMG_Load("image/mode/mode_jeu/survie.png");
                SDL_Texture* pTexture_mode_survie = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode_survie);
                SDL_Rect dest_mode_survie = { POS_NOM_X, POS_NOM_Y, pSprite_mode_survie->w, pSprite_mode_survie->h};
                //mini_map
                SDL_Surface* pSprite_mode_minimap1 = IMG_Load("image/mode/maps/petite_mapVS.jpg");
                SDL_Texture* pTexture_mode_minimap1 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode_minimap1);
                SDL_Rect dest_mode_minimap1 = { POS_MAP_X, POS_MAP_Y, pSprite_mode_minimap1->w, pSprite_mode_minimap1->h};
                //skin bleu
                SDL_Surface* pSprite_mode_skin_bleu = IMG_Load("image/mode/skins/skin_bleu.png");
                SDL_Texture* pTexture_mode_skin_bleu = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode_skin_bleu);
                SDL_Rect dest_mode_skin_bleu = { POS_J1_X, POS_J1_Y, pSprite_mode_skin_bleu->w, pSprite_mode_skin_bleu->h};
                //skin rouge
                SDL_Surface* pSprite_mode_skin_rouge = IMG_Load("image/mode/skins/skin_rouge.png");
                SDL_Texture* pTexture_mode_skin_rouge = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_mode_skin_rouge);
                SDL_Rect dest_mode_skin_rouge = { POS_J2_X, POS_J2_Y, pSprite_mode_skin_rouge->w, pSprite_mode_skin_rouge->h};

                //chargement image option
                //image 1
                SDL_Surface* pSprite_option = IMG_Load("image/option/option.jpg");
                SDL_Texture* pTexture_option = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_option);
                SDL_Rect dest_option = { SCREEN_WIDTH/2 - pSprite_option->w/2,SCREEN_HEIGHT/2 - pSprite_option->h/2, pSprite_option->w, pSprite_option->h};

                //chargement image play
                //map
                SDL_Surface* pSprite_play_map = IMG_Load("image/maps/mapVS.jpg");
                SDL_Texture* pTexture_play_map = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_play_map);
                SDL_Rect dest_play_map = { SCREEN_WIDTH/2 - pSprite_play_map->w/2,SCREEN_HEIGHT/2 - pSprite_play_map->h/2, pSprite_play_map->w, pSprite_play_map->h};

                //pret
                SDL_Surface* pSprite_play_pret = IMG_Load("image/play/pret.png");
                SDL_Texture* pTexture_play_pret = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_play_pret);
                SDL_Rect dest_play_pret = { SCREEN_WIDTH/2 - pSprite_play_pret->w/2,SCREEN_HEIGHT/2 - pSprite_play_pret->h/2, pSprite_play_pret->w, pSprite_play_pret->h};

                //321
                SDL_Surface* pSprite_play_321 = IMG_Load("image/play/321.png");
                SDL_Texture* pTexture_play_321 = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_play_321);
                SDL_Rect dest_play_321 = { SCREEN_WIDTH/2 - pSprite_play_321->w/2,SCREEN_HEIGHT/2 - pSprite_play_321->h/2, pSprite_play_321->w, pSprite_play_321->h};

                //partez
                SDL_Surface* pSprite_play_partez = IMG_Load("image/play/partez.png");
                SDL_Texture* pTexture_play_partez = SDL_CreateTextureFromSurface(Fenetre.prenderer,pSprite_play_partez);
                SDL_Rect dest_play_partez = { SCREEN_WIDTH/2 - pSprite_play_partez->w/2,SCREEN_HEIGHT/2 - pSprite_play_partez->h/2, pSprite_play_partez->w, pSprite_play_partez->h};

                //utilisation touches du clavier
                while(compteur !=0)
                {
                    SDL_WaitEvent(&event);
                    switch(event.type)
                {

                case SDL_KEYDOWN:

                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                    compteur_help = 1;
                    num = compteur_down(num, 4); // fct compteur down

                    switch(num)
                    {
                        case 0:
                        SDL_RenderCopy(Fenetre.prenderer,pTexture,NULL,&dest);
                        SDL_RenderPresent(Fenetre.prenderer);
                        Mix_PlayChannel(-1, clic, 0);
                        break;

                        case 1:
                        SDL_RenderCopy(Fenetre.prenderer,pTexture2,NULL,&dest2);
                        SDL_RenderPresent(Fenetre.prenderer);
                        Mix_PlayChannel(-1, clic, 0);
                        break;

                        case 2:
                        SDL_RenderCopy(Fenetre.prenderer,pTexture3,NULL,&dest3);
                        SDL_RenderPresent(Fenetre.prenderer);
                        Mix_PlayChannel(-1, clic, 0);
                        break;

                        case 3:
                        SDL_RenderCopy(Fenetre.prenderer,pTexture4,NULL,&dest4);
                        SDL_RenderPresent(Fenetre.prenderer);
                        Mix_PlayChannel(-1, clic, 0);
                        break;

                        case 4:
                        SDL_RenderCopy(Fenetre.prenderer,pTexture5,NULL,&dest5);
                        SDL_RenderPresent(Fenetre.prenderer);
                        Mix_PlayChannel(-1, clic, 0);
                        break;
                        }

                    break;

                    case SDLK_UP:
                        compteur_help = 1;
                        num = compteur_up(num, 5, 4); // fonction compteur up

                        switch(num)
                            {
                            case 0:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture,NULL,&dest);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);
                            break;

                            case 1:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture2,NULL,&dest2);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);
                            break;

                            case 2:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture3,NULL,&dest3);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);
                            break;

                            case 3:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture4,NULL,&dest4);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);
                            break;

                            case 4:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture5,NULL,&dest5);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);
                            break;
                            }

                    break;

                    case SDLK_RETURN:

                        switch(num)
                            {

        //################################################--------------------PLAY------------------------###############################
                            case 0:
                            // pret
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_map,NULL,&dest_play_map);
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_pret,NULL,&dest_play_pret);
                            SDL_RenderPresent(Fenetre.prenderer);

                            Mix_PlayChannel(-1, pret, 0);
                            SDL_Delay(1000);

                            //321
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_map,NULL,&dest_play_map);
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_321,NULL,&dest_play_321);
                            SDL_RenderPresent(Fenetre.prenderer);

                            Mix_PlayChannel(-1, decomptage, 0);
                            SDL_Delay(3500);

                            //partez

                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_map,NULL,&dest_play_map);
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_play_partez,NULL,&dest_play_partez);
                            SDL_RenderPresent(Fenetre.prenderer);

                            Mix_PlayChannel(-1, partez, 0);
                            SDL_Delay(1000);

                            // chargement de map machin
                            // partez
                            compteur = mode_PVP(&Fenetre, compteur);

                            break;

        //####################################################---------------MODE-------------------#################################################################################################
                            case 1:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                            //test affichage joueur 2
                            if (selection_j2==0)
                            {
                                SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                            }

                            //test affichage joueur 1
                            if (selection_j1==0)
                            {
                                SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                            }

                            //test map
                            if (selection_map==0)
                                {
                                SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);

                                }

                            if(selection_mode==0)
                                {
                                SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                SDL_RenderPresent(Fenetre.prenderer);
                                }

                            else if (selection_mode ==1)
                                {
                                SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                SDL_RenderPresent(Fenetre.prenderer);
                                }

                            Mix_PlayChannel(-1, clic, 0);

                            while (compteur_help != 0)
                            {

                                SDL_WaitEvent(&event_help);
                                switch(event_help.type)
                                    {

                                    case SDL_KEYDOWN:

                                    switch(event_help.key.keysym.sym)
                                    {
                                    case SDLK_ESCAPE:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture2,NULL,&dest2);
                                        SDL_RenderPresent(Fenetre.prenderer);
                                        Mix_PlayChannel(-1, clic, 0);
                                        compteur_help = 0;
                                    break;
        //---------------------------------------------------------------------------------------------------
                                    case SDLK_DOWN:
                                        num_mode = compteur_down(num_mode, 3); // fonction compteur down

                                        switch(num_mode)
                                        {
                                        case 0:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //test affichage joueur 2
                                        if (selection_j2==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }
                                        Mix_PlayChannel(-1, clic, 0);
                                        break;


                                        case 1:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //test affichage joueur 2
                                        if (selection_j2==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }
                                        Mix_PlayChannel(-1, clic, 0);
                                        break;

                                        case 2:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode2,NULL,&dest_mode2);

                                        //test affichage joueur 2
                                        if (selection_j2==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }
                                        Mix_PlayChannel(-1, clic, 0);
                                        break;

                                        case 3:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode3,NULL,&dest_mode3);

                                        //test affichage joueur 2
                                        if (selection_j2==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }
                                        Mix_PlayChannel(-1, clic, 0);
                                        break;
                                        }

                                    break;

        //-------------------------------------------------------------------------------------------------------
        //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]------------------CHANGER-----------------------[[[[[[[[[[[[[[[[[[[[[[[[[[[
                                    case SDLK_RIGHT:

                                    switch(num_mode)
                                    {
                                        case 0:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        SDL_RenderPresent(Fenetre.prenderer);
                                        break;

                                        case 1:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        SDL_RenderPresent(Fenetre.prenderer);
                                        break;

                                        case 2:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode2,NULL,&dest_mode2);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);

                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        SDL_RenderPresent(Fenetre.prenderer);

                                        break;


                                        case 3:
                                        Mix_PlayChannel(-1, clic, 0);
                                        //variable mode
                                        if (selection_mode ==0)
                                        {
                                            selection_mode=1;
                                        }

                                        else
                                        {
                                            selection_mode=0;
                                        }
                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode3,NULL,&dest_mode3);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage j1
                                        if (selection_j1 == 0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //texte
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                            Mix_PlayChannel(-1, duel, 0);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                            Mix_PlayChannel(-1, survie, 0);
                                        }

                                        break;
                                    }

                                    break;

                                    case SDLK_LEFT:

                                    switch(num_mode)
                                    {
                                        case 0:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }


                                        SDL_RenderPresent(Fenetre.prenderer);
                                        break;

                                        case 1:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);

                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);

                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }


                                        SDL_RenderPresent(Fenetre.prenderer);
                                        break;

                                        case 2:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //text
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                        }

                                        //map
                                        if (selection_map==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //joueur 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }


                                        SDL_RenderPresent(Fenetre.prenderer);
                                        break;







                                        case 3:
                                        Mix_PlayChannel(-1, clic, 0);

                                        //variable mode
                                        if (selection_mode ==0)
                                        {
                                            selection_mode=1;
                                        }

                                        else
                                        {
                                            selection_mode=0;
                                        }

                                        //efface
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode3,NULL,&dest_mode3);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage jouuer 1
                                        if (selection_j1==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //texte
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                            Mix_PlayChannel(-1, duel, 0);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                            Mix_PlayChannel(-1, survie, 0);
                                        }
                                        break;

                                    }

                                    break;

        //[[[[[[[[[[[[[[[[[[[[[----------------------------------FIN CHANGER------------------------]]]]]]]]]]]]]]]]]]]]]]

                                    case SDLK_UP:
                                    num_mode = compteur_up(num_mode, 4, 3); // fct compteur


                                    switch(num_mode)
                                    {
                                        case 0:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }
                                        Mix_PlayChannel(-1, clic, 0);
                                        break;

                                        case 1:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode1,NULL,&dest_mode1);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        Mix_PlayChannel(-1, clic, 0);
                                        break;

                                        case 2:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode2,NULL,&dest_mode2);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        Mix_PlayChannel(-1, clic, 0);
                                        break;

                                        case 3:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode3,NULL,&dest_mode3);

                                        //joueur 2
                                        if (selection_j2==0)
                                        {
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_rouge,NULL,&dest_mode_skin_rouge);
                                        }

                                        //test affichage joueur 1
                                        if (selection_j1==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_skin_bleu,NULL,&dest_mode_skin_bleu);
                                        }

                                        //test affichage map
                                        if (selection_map==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_minimap1,NULL,&dest_mode_minimap1);
                                        }

                                        //test affichage txt
                                        if(selection_mode==0)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_1vs1,NULL,&dest_mode_1vs1);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        else if (selection_mode ==1)
                                        {
                                            SDL_RenderCopy(Fenetre.prenderer,pTexture_mode_survie,NULL,&dest_mode_survie);
                                            SDL_RenderPresent(Fenetre.prenderer);
                                        }

                                        Mix_PlayChannel(-1, clic, 0);
                                        break;
                                        }

                                    break;
                                    }
                                    break;
                                    }
                            }
                            break;

        //####################################---------------------option--------------------######################
                            case 2:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture_option,NULL,&dest_option);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);

                            while (compteur_help != 0)
                            {

                                SDL_WaitEvent(&event_help);
                                switch(event_help.type)
                                    {

                                    case SDL_KEYDOWN:

                                    switch(event_help.key.keysym.sym)
                                    {
                                    case SDLK_ESCAPE:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture3,NULL,&dest3);
                                        SDL_RenderPresent(Fenetre.prenderer);
                                        Mix_PlayChannel(-1, clic, 0);
                                        compteur_help = 0;
                                    break;
                                    }
                                    break;
                                    }
                            }
                            break;


        //#####################################------------HELP-------------------###################################
                            case 3:
                            SDL_RenderCopy(Fenetre.prenderer,pTexture6,NULL,&dest6);
                            SDL_RenderPresent(Fenetre.prenderer);
                            Mix_PlayChannel(-1, clic, 0);

                            while (compteur_help != 0)
                            {

                                SDL_WaitEvent(&event_help);
                                switch(event_help.type)
                                    {

                                    case SDL_KEYDOWN:

                                    switch(event_help.key.keysym.sym)
                                    {
                                    case SDLK_ESCAPE:
                                        SDL_RenderCopy(Fenetre.prenderer,pTexture4,NULL,&dest4);
                                        SDL_RenderPresent(Fenetre.prenderer);
                                        Mix_PlayChannel(-1, clic, 0);
                                        compteur_help = 0;
                                    break;
                                    }
                                    break;
                                    }
                            }
                            break;

        //##################################--------------------SONS--------------#####################
                            case 4:
                            son = ge_son(son); // fonction case son
                            break;

        //#############################-----------------FIN-MENU-----------------##############################
                        }
                        break;


                    case SDLK_ESCAPE:
                    compteur =0;
                    break;
                    }

                break;
                }
            }
                    // liberaton de la memeoire associ� � la texture
                    SDL_DestroyTexture(pTexture);
                    SDL_DestroyTexture(pTexture2);
                    SDL_DestroyTexture(pTexture3);
                    SDL_DestroyTexture(pTexture4);
                    SDL_DestroyTexture(pTexture5);
                    SDL_DestroyTexture(pTexture6);
                    SDL_DestroyTexture(pTexture_mode1);
                    SDL_DestroyTexture(pTexture_mode2);
                    SDL_DestroyTexture(pTexture_mode3);
                    SDL_DestroyTexture(pTexture_option);
                    SDL_DestroyTexture(pTexture_mode_1vs1);
                    SDL_DestroyTexture(pTexture_mode_survie);
                    SDL_DestroyTexture(pTexture_mode_minimap1);
                    SDL_DestroyTexture(pTexture_mode_skin_rouge);
                    SDL_DestroyTexture(pTexture_mode_skin_bleu);

            }

            //SDL_DestroyWindow(Fenetre.pwindow);

            //lib�ration sons
            Mix_FreeMusic(backgroundSound);
            Mix_FreeChunk(clic);
            Mix_FreeChunk(decomptage);
            Mix_FreeChunk(partez);
            Mix_FreeChunk(pret);
            Mix_FreeChunk(duel);
            Mix_FreeChunk(survie);
            //Mix_FreeChunk(play_explosion);
        }
    }
//fermeture
//Mix_CloseAudio();
//SDL_Quit();
ge_Close(&Fenetre);
return 0;
}
