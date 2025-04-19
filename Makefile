all :
	g++ -I src/include/SDL2 -I headers -L src/lib -o game game.cpp -lmingw32 -lSDL2main -lSDL2  -lSDL2_image -lSDL2_ttf -lSDL2_mixer