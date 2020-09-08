gcc src/test/SDL2/SDL2.c \
    -o bin/prog \
    -I include \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2

./bin/prog.exe
sleep 5
