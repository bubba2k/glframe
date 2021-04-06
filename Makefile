BDIR 	= ./build
SDIR 	= ./src

CC 		= g++
CFLAGS 	= -Wextra -Wall -g
LIBS   	= -lSDL2 -lGL -lGLEW

all: compile-all archive gen-template clean

compile-all: Display Buffers Renderer Mesh Shader Util

archive:
	cp $(SDIR)/GLframe.hpp $(BDIR)/
	ar rcs $(BDIR)/libglframe.a $(BDIR)/Display.o $(BDIR)/Buffers.o $(BDIR)/Renderer.o $(BDIR)/Mesh.o $(BDIR)/Shader.o $(BDIR)/Util.o

Display:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o
	
Buffers:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o
	
Renderer:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o
	
Mesh:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o
	
Shader:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o

Util:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o
	
gen-template:
	cp $(BDIR)/libglframe.a ./template-project/libs/
	cp $(BDIR)/GLframe.hpp	./template-project/libs/

clean:
	rm $(BDIR)/*.o
