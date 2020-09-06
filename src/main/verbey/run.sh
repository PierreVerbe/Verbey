g++ src/main/verbey/main.cpp \
    src/main/verbey/bib_sdl.cpp \
    src/main/verbey/calculs.cpp \
    src/main/verbey/vs/affichage.cpp \
    src/main/verbey/vs/balle.cpp \
    src/main/verbey/vs/calculs.cpp \
    src/main/verbey/vs/fct_jeu.cpp \
    src/main/verbey/vs/gestion_SDL2.cpp \
    src/main/verbey/vs/grenade.cpp \
    src/main/verbey/vs/init_donnees.cpp \
    src/main/verbey/vs/manette.cpp \
    src/main/verbey/vs/mine.cpp \
    -o bin/prog \
    -I include/SDL2 \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2 \
    -lSDL2_image \
    -lSDL2_mixer

./bin/prog.exe
sleep 5
