gcc src/test/SDL2/SDL2_image/SDL2_image.c \
    -o bin/TestSDL2_image \
    -I include \
    -L lib \
    -lmingw32 \
    -lSDL2main \
    -lSDL2 \
    -lSDL2_image

./bin/TestSDL2_image.exe
sleep 5
