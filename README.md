# OPENGLNGINE

OpenGL sandbox.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- [Conan](https://conan.io/) : The C / C++ Package Manager for Developers.
- [OpenGL](https://www.opengl.org/) : An environment for developing portable, interactive 2D and 3D graphics applications.
- [glew](http://glew.sourceforge.net/index.html) : The OpenGL Extension Wrangler Library.
- [glfw](http://www.glfw.org/) : It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
- [glm](https://glm.g-truc.net/0.9.9/index.html) : A mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [SOIL](https://www.lonesock.net/soil.html) : A library used primarily for uploading textures into OpenGL.

### Generation

Add bincrafters remote : `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`

Use conan to download/build libraries : `conan install -s build_type=Release -if C:\build_release .`

Generate using cmake in the same build directory than conan: `cmake`.

## Authors

* **MANCIAUX Romain** - *Initial work* - [PamplemousseMR](https://github.com/PamplemousseMR).

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.