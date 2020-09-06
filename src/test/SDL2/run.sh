gcc src/test/SDL2/image.c \
    -o bin/SDL2test \
    -I include/SDL2 \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2 \
    -lSDL2_image

./bin/SDL2test.exe
sleep 5
