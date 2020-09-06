#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

 
void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t, Mix_Music *m)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);

    if(w != NULL)
        SDL_DestroyWindow(w);

    if(m != NULL)
    {
        Mix_FreeMusic(m);
        Mix_CloseAudio();
    }  

    SDL_Quit;
}

int main (int argc, char **argv)
{
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);

    SDL_Window *window = NULL;
    Mix_Music *musique = NULL;
    SDL_Rect dest_rect = {0, 0, 640, 480};

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Affichage avec la SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if(window == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        SDL_Log("ERREUR > %s\n", Mix_GetError());
    }

    musique = Mix_LoadMUS("src/test/resources/sounds/messenger_alert_message_sound.mp3");
    Mix_PlayMusic(musique, 1);

    SDL_Delay(5000);
    clean_ressources(window, NULL, NULL, musique);

    return EXIT_SUCCESS;
}
