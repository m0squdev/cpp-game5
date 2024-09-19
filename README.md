# OpenGL Game Engine

This is a simple OpenGL-based game engine that provides basic functionality for 3D graphics rendering and game development.

## Features

- OpenGL rendering
- Camera management
- Shader compilation and management
- Mesh handling
- Texture loading
- Lighting system
- Material system
- Window management
- Logging utilities

## Dependencies

- OpenGL
- GLEW
- GLFW
- SOIL (Simple OpenGL Image Library)
- STB Image

## Directory Structure

```
.
├── lib/
│   ├── soil/
│   └── stb_image/
├── obj/
├── log.cpp
├── camera.cpp
├── shader.cpp
├── program.cpp
├── mesh.cpp
├── texture.cpp
├── light.cpp
├── material.cpp
├── listener.cpp
├── window.cpp
├── main.cpp
└── Makefile
```

## Compilation

This project uses a Makefile for compilation. Here are the main commands:

### Initialize

Before compiling, initialize the output directory:

```
make init
```

### Compile Library

To compile just the engine library:

```
make obj-engine
```

### Compile Example

To compile the example (including the library):

```
make obj
```

### Build and Run

To compile, build, and run the example:

```
make
```

This command will compile the library, the example (`main.cpp`), build the executable, and run it.

### Clean Up

To clean up object files and executables:

```
make clean
```

## Usage

1. Include the necessary header files in your project.
2. Use the provided classes and functions to create your game or application.
3. Compile your project along with the engine library.

## Example

The `main.cpp` file provides an example of how to use the engine. You can compile it using:

```
make obj
```

And then build and run it using:

```
make build
make run
```

Or do all steps at once with:

```
make output
```

## Installation of Dependencies

### For Debian-based systems (using apt):

```
make apt-install
```

### For Arch-based systems (using pacman):

```
make pacman-install
```

## Notes

- On Linux, you may need to set the following environment variable for shader loading:
  ```
  export MESA_GL_VERSION_OVERRIDE=3.3
  ```
