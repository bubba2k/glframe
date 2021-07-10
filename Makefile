BDIR 	= ./build
SDIR 	= ./src

CC 		= g++
CFLAGS 	= -Wextra -Wall -g
LIBS   	= -lSDL2 -lGL -lGLEW

all: compile-all archive gen-template

compile-all: Display Buffers Renderer Mesh Shader Util Camera

archive:
	cp $(SDIR)/*.hpp $(BDIR)/
	ar rcs $(BDIR)/libglframe.a $(BDIR)/Display.o $(BDIR)/Buffers.o $(BDIR)/Renderer.o $(BDIR)/Mesh.o $(BDIR)/Shader.o $(BDIR)/Util.o $(BDIR)/Camera.o

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

Camera:
	$(CC) $(CFLAGS) -c $(SDIR)/$@.cpp -o $(BDIR)/$@.o

gen-template:
	cp $(BDIR)/libglframe.a ./template-project/libs/
	cp $(BDIR)/*.hpp		./template-project/libs/

clean:
	rm $(BDIR)/*.o
