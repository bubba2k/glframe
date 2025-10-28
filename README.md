# glframe

This project provides a few convenient object-oriented wrappers over OpenGL calls and implements a Blinn-Phong renderer.

![Screenshot of the example program built with glframe](https://github.com/bubba2k/glframe/blob/master/screenshot.png?raw=true)

## Features
- Convenient abstractions to quickly load and display 3D models
- Realtime affine transformations on models
- Freely placable and modifiable camera
- Support for wide variety of 3D model formats through [https://github.com/assimp/assimp](Open Asset Import Library)
- UV mapping of diffuse textures  

## Building (Linux)

Prerequisites: Have `GLEW`, `SDL2` and `assimp` libraries installed and on path.

```
mkdir build
cd build
cmake ..
make
```

The built dynamic library will then appear in the build directory.


An example program is also built inside the `examples/` directory.
Run it from inside the example directory like `cd examples && ./example`.
