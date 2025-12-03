CC := clang
CFLAGS := -Wall -Wextra -O2 -Iinclude 
CDEPS := -lglfw -lm

all: build

run: build
	bin/viewer bin/assets/cube.stl

build: create_dir src/*
	$(CC) $(CFLAGS) -c src/*.c
	mv *.o bin/obj/
	$(CC) $(CDEPS) bin/obj/*.o -o bin/viewer
	cp -r assets/ bin/assets 

.PHONY: clean create_dir
create_dir:
	mkdir -p bin/obj
clean: 
	rm -r bin
