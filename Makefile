GPP = g++
CXXFLAGS = -w
LIBS =
LDFLAGS = `sdl2-config --cflags --libs`
INCLUDES = -I include
EXEC = main
SRC = src/*.cpp
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(GPP) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(GPP) $(CXXFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)