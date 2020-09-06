#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

 
void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);

    if(w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit;
}

int main (int argc, char **argv)
{
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0, 0, 640, 480};

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Affichage avec la SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if(window == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(window, NULL, NULL);
        exit(EXIT_FAILURE);
    }

//http://sdz.tdct.org/sdz/jouer-du-son-avec-sdl-mixer.html
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }

Mix_Music *musique;
Mix_FreeMusic(musique);
musique = Mix_LoadMUS("src/test/resources/sounds/messenger_alert_message_sound.mp3");
Mix_PlayMusic(musique, 1); //Jouer infiniment la musique

/*
    picture = IMG_Load("src/test/resources/images/Simple_DirectMedia_Layer,_Logo.png");
    if(picture == NULL)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }
    

    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if(texture == NULL)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    if(SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(renderer);
    */
    SDL_Delay(5000);

    clean_ressources(window, renderer, texture);

    Mix_FreeMusic(musique);
    Mix_CloseAudio();
  

    return EXIT_SUCCESS;
}
