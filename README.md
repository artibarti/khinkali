# khinkhali
experimental c++ graphic library for practicing

The main goal of this project is to create an API for creating simple games and scenes with OpenGL. The main concept is to hide low-level OpenGL calls behind easy-to-understand functions, so users can easily create scenes with pre-defined objects, textures and phisics. That way the users loose the ability to use all setting options for OpenGL, but hey, this is a sandboy project.

# requirements
You must use the --std=c++11 compiler option (for g++) when compiling your depending project.

Also, you need the following libraries to be installed:

	glew
	glfw3
	glm

On Ubuntu systems, you can install them like this:

	sudo apt-get install libglfw3 libglfw3-dev
	sudo apt-get install libglew-dev
	sudo apt-get install libglm-dev

After that, you can use the khinkali headers. The library is an only-header library, so you just need to include the following file:

	khinkali.hpp

from the include folder.

# run examples
In the example folder you can find a main.cpp file, which gives you some hints of the basic features and usage. If you have all dependencies installed, you can compile this program with the provided Makefile by type

	make

in the example folder.

# notes
This project is only for practicing and self-entertaining purpose, there could be various bugs, leaks, etc. Use it only on your own risk.


	
	
