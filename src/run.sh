gcc src/main.c \
    -o bin/prog \
    -I include/SDL2 \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2

./bin/prog.exe
sleep 5
