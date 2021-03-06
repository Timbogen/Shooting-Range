# Shooting-Range
This is a little 3D shooting range, kind of like an aim trainer. The project is built with OpenGL.

# Controls

The player can move with WASD and look around with the mouse.

For extended control over the program you can open the game console with TAB.
The game console provides a bunch of useful commands. Typing in **help** will get
you started.

# Development

## Project Setup
**Important!** To make use of conan **on Windows it is required to have the Visual Studio Compiler** installed, since
some of the dependencies listed in the *conanfile.txt* aren't available for GCC etc. under Windows.

* Clone repository:
  
  ```
  > git clone https://github.com/Timbogen/Shooting-Range.git
  ```


* Install dependencies with the package manager [Conan](https://conan.io/):
  ```
  > cd Shooting-Range
  Shooting-Range> mkdir cmake-build-debug
  Shooting-Range> cd cmake-build-debug
  Shooting-Range\cmake-build-debug> conan install ..
  ```
  Optional to build GFLW from source (Conan doesn't provide binaries for some compilers):
  ```
  Shooting-Range\cmake-build-debug> conan install --build=glfw ..
  ```