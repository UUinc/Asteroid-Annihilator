all:
	g++ -Isrc/Include -Lsrc/Lib -o main main.cpp assets/codes/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && main.exe