### The relative path for all of the commands executed in this makefile is the WORKING DIRECTORY                     ###
### If you're on Linux, you may need to run the following command in order for the shaders to be loaded successfully ###
###    export MESA_GL_VERSION_OVERRIDE=3.3                                                                           ###
### Also, on Linux Debian and derived distros you can run                                                            ###
###    make install                                                                                                  ###
### to install GLFW and GLEW by using apt                                                                            ###

### Get started by calling the following commands ###
#   $ git init
#   $ make config email="user@website.com" name="user"
#   $ git add
#   $ git commit -m "Commit message"
#   $ make connect url="https://github.com/user/repo.git"
#   $ make push

### Useful Git commands ###
#   $ git add    | Add files to commit
#   $ git init   | Make the directory a Git repository
#   $ git status | Show the committed, modified and untracked files in the directory

# You can change to whatever directory or files the following global values
lib-dir = lib
lib-soil-dir = $(lib-dir)/soil
lib-stb-image-dir = $(lib-dir)/stb_image
obj-dir = obj
out-file = out

# make: executes functions build, run and clear
output: obj build run

# make install: [ONLY FOR LINUX DEBIAN AND DERIVED DISTROS] installs the GLFW and GLEW libraries
install:
	sudo apt install libglfw3-dev
	sudo apt install libglew-dev

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
# make obj-main: converts main.cpp to main.o
obj-main: main.cpp
	gcc -c main.cpp -o $(obj-dir)/main.o
# make obj: calls all the obj-* functions
obj: obj-lib-soil obj-game obj-main

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

# make config email="user@website.com" name="user": configures your Git profile. This is required for you to commit your work
config:
	git config --global user.email "$(email)"
	git config --global user.name "$(name)"
# make connect url="https://github.com/user/repo.git"           : connects the external repository to the Git one
#              url="https://user:token@github.com/user/repo.git": this also sets the user and the token to use when updating the external repository
connect:
	git remote add origin $(url)
	git branch -M master
# make disconnect: disconnects the external repository from the Git repository
disconnect:
	git remote rm origin
# make update: updates modified files on the Git repository
update:
	git add -u
# make rm file="file.txt": removes a file from the Git repository
rm:
	git rm $(file) --cached

# make push: updates the external repository
push:
	git push -u origin master