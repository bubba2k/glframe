CC 		:= g++
CFLAGS 	:= -Werror -Wextra -g

OBJ = $(shell find -name '*.o')

STATLIBS:= -L ./libs -lglframe
DYNLIBS := -lSDL2 -lGL -lGLEW -lassimp

all: main link
	rm $(OBJ)

main:
	$(CC) $(CFLAGS) -c $@.cpp -o $@.o

link:
	$(CC) $(CFLAGS) $(OBJ) $(DYNLIBS) $(STATLIBS) -o prog
