BDIR 	= ./build
SDIR 	= ./src

CC 		= g++
CFLAGS 	= -Wextra -Wall -fPIC
LIBS   	= -lSDL2 -lGL -lGLEW

all: Display Buffers Renderer Mesh Shader Util

link:
	$(CC) $(CFLAGS) -shared $(BDIR)/Display.o $(BDIR)/Buffers.o $(BDIR)/Renderer.o $(BDIR)/Mesh.o $(BDIR)/Shader.o $(BDIR)/Util.o -o $(BDIR)/glframe.so

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
	
