GCC = g++
CPPFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
# LDFLAGS = -L lib -lmingw32 -lSDL2main (only for linux)

Programme : main.o
	$(GCC) main.o -o main $(LDFLAGS)

main.o : src/main.cpp
	$(GCC) $(CPPFLAGS) -c src/main.cpp -o main.o

# Suppression des fichiers temporaires.
clean :
	del -rf *.o

# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.
mrproper : clean
	del main.exe

# g++ -L lib -I include ./src/*.cpp -o main -lmingw32 -lSDL2main -lSDL2  -mwindows
# TODO: mettre a jour le Makefile