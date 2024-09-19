### The relative path for all of the commands executed in this makefile is the WORKING DIRECTORY                     ###
### If you're on Linux, you may need to run the following command in order for the shaders to be loaded successfully ###
###    export MESA_GL_VERSION_OVERRIDE=3.3                                                                           ###
### Also, if you have apt you can run                                                                                ###
###    make apt-install                                                                                              ###
### to install GLFW and GLEW by using apt or if you have pacman                                                      ###
###    make pacman-install                                                                                           ###
### to do the same                                                                                                   ###
### Remember to initialize the output directory with                                                                 ###
###    make init                                                                                                     ###
### before compiling anything!                                                                                       ###
### To compile just the library run                                                                                  ###
###    make obj-engine                                                                                               ###
### To compile also the example (main.cpp) run                                                                       ###
###    make obj                                                                                                      ###

# You can change to whatever directory or files the following global values
lib-dir = lib
lib-soil-dir = $(lib-dir)/soil
lib-stb-image-dir = $(lib-dir)/stb_image
obj-dir = obj
out-file = out

# make: executes functions build, run and clear
output: obj build run

# make apt-install: [ONLY IF YOU HAVE APT] installs the GLFW and GLEW libraries
apt-install:
	sudo apt install libglfw3-dev libglew-dev

# make pacman-install: [ONLY IF YOU HAVE PACMAN] installs the GLFW and GLEW libraries
pacman-install:
	sudo pacman -S glfw glew --needed

# make init: creates the directories where the .o files are stored
init:
	mkdir $(obj-dir)

# make obj-lib-<lib>: converts the needed .c files in lib/<lib> to .o files
obj-lib-soil: lib/soil/image_DXT.c lib/soil/image_helper.c lib/soil/wfETC.c lib/soil/SOIL2.c
	gcc -c $(lib-soil-dir)/image_DXT.c -o $(obj-dir)/image_DXT.o
	gcc -c $(lib-soil-dir)/image_helper.c -o $(obj-dir)/image_helper.o
	gcc -c $(lib-soil-dir)/wfETC.c -o $(obj-dir)/wfETC.o
	gcc -c $(lib-soil-dir)/SOIL2.c -o $(obj-dir)/SOIL2.o
#	gcc -c lib/soil/image_DXT.c -o lib/soil/image_DXT.o
#	gcc -c lib/soil/image_helper.c -o lib/soil/image_helper.o
#	gcc -c lib/soil/wfETC.c -o lib/soil/wfETC.o
#	gcc -c lib/soil/SOIL2.c -o lib/soil/SOIL2.o
obj-lib-stb-image: lib/stb_image/stb_image.cpp
	gcc -c $(lib-stb-image-dir)/stb_image.cpp -o $(obj-dir)/stb_image.o
#	gcc -c lib/stb_image/stb_image.cpp -o lib/stb_image/stb_image.o
# make obj-game: converts all the game's .cpp files but main.cpp
obj-game: log.cpp camera.cpp shader.cpp program.cpp mesh.cpp texture.cpp light.cpp material.cpp listener.cpp window.cpp
	gcc -c log.cpp -o $(obj-dir)/log.o
	gcc -c camera.cpp -o $(obj-dir)/camera.o
	gcc -c shader.cpp -o $(obj-dir)/shader.o
	gcc -c program.cpp -o $(obj-dir)/program.o
	gcc -c mesh.cpp -o $(obj-dir)/mesh.o
	gcc -c texture.cpp -o $(obj-dir)/texture.o
	gcc -c light.cpp -o $(obj-dir)/light.o
	gcc -c material.cpp -o $(obj-dir)/material.o
	gcc -c listener.cpp -o $(obj-dir)/listener.o
	gcc -c window.cpp -o $(obj-dir)/window.o
#	gcc -c camera.cpp log.cpp program.cpp shader.cpp texture.cpp mesh.cpp window.cpp
# make obj-engine: calls all the obj-* functions except obj-main
obj-engine: obj-lib-soil obj-game
# make obj-main: converts main.cpp to main.o
obj-main: main.cpp
	gcc -c main.cpp -o $(obj-dir)/main.o
# make obj: calls all the obj-* functions
obj: obj-engine obj-main

# make build: converts all the .cpp files to .o files and compiles them with all the modules included
build:
	gcc $(obj-dir)/* -ldl -lstdc++ -lGL -lGLEW -lglfw -lm -o $(out-file)
#	gcc lib/stb_image/stb_image.o *.o -ldl -lstdc++ -lGL -lGLEW -lglfw -lm -o output

# make run: runs the executable file created by the function build
run:
	./$(out-file)

# make clean-obj: removes the .o file created by the functions obj and obj-*
clean-obj:
	rm -r $(obj-dir)
# make clean-out: removes the executable file created by the function build
clean-out:
	rm $(out-file)
# make clean: removes the files created by the functions build_<cpp file>, obj and build
clean: clean-obj clean-out
