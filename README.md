# glframe

A library that provides a few convenient object-oriented wrappers over OpenGL calls, and implements a basic Blinn-Phong renderer.
Asset loading is supported through `assimp` and `stbimage`.
Only diffuse textures are supported.

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