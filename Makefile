### The relative path for all of the commands executed in this makefile is the WORKING DIRECTORY ###

# You can change to whatever directory or files the following global values
lib-dir = lib
lib-soil-dir = $(lib-dir)/soil
lib-stb-image-dir = $(lib-dir)/stb_image
obj-dir = obj
out-file = out

# make: executes functions build, run and clear
output: obj build run

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

# make git-init: makes the directory a git repository
git-init:
	git init
# make git-connect url="https://github.com/user/repo.git": connects the git repository to the GitHub one
git-connect:
	git remote add origin $(url)
	git branch -M master
# make git-disconnect: disconnects GitHub from the git repository
git-disconnect:
	git remote rm origin
# make git-status: shows the files that are syncronised with the git repository, the ones that had been modified and the untracked ones
git-status:
	git status
# make git-add file="code.cpp": adds files to the git repository
git-add:
	git add $(file)
# make git-rm file="code.cpp": removes files from the git repository
git-rm:
	git rm $(file)
# make git-commit msg="Commit\ message": updates the git and the GitHub repositories
git-commit:
	git add -u
	git commit -m $(msg)
	git push -u origin master
