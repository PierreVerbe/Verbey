gcc src/test/SDL2/SDL2_mixer/SDL2_mixer.c \
    -o bin/TestSDL2_mixer \
    -I include \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2 \
    -lSDL2_mixer

./bin/TestSDL2_mixer.exe
sleep 5
