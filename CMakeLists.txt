cmake_minimum_required(VERSION 3.10)

# set project name
project(GLframe)

# library
add_library(glframe STATIC)

target_sources(glframe PRIVATE
	external/stb_image/stb_image.c
	src/Buffers.cpp
	src/Camera.cpp
	src/Display.cpp
	src/Entity.cpp
	src/Mesh.cpp
	src/Renderer.cpp
	src/Shader.cpp
	src/Texture.cpp
	src/Tracker.cpp
	src/Util.cpp
)

set(HeaderFiles 
	src/Buffers.hpp
	src/Camera.cpp
	src/Display.hpp
	src/Entity.hpp
	src/GLframe.hpp
	src/Mesh.hpp
	src/Renderer.hpp
	src/ShaderProgram.hpp
	src/Texture.hpp
	src/Tracker.hpp
	src/Util.hpp)

set_target_properties(glframe PROPERTIES
					  PUBLIC_HEADER ${HeaderFiles}
					  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")


# build the example project
add_executable(example ${CMAKE_SOURCE_DIR}/examples/main.cpp)

set_target_properties(example PROPERTIES
					  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/examples/")

target_include_directories(example PUBLIC "${CMAKE_SOURCE_DIR}/src/")

target_link_libraries(example glframe GL GLEW SDL2 assimp)
