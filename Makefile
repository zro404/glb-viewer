CC := clang
CFLAGS := -Wall -Wextra -O2 -Iinclude 
CDEPS := -lglfw

all: main

run: main
	./bin/viewer

main: create_dir src/*
	$(CC) $(CFLAGS) -c src/*.c
	mv *.o bin/obj/
	$(CC) $(CDEPS) bin/obj/*.o -o bin/viewer

.PHONY: clean create_dir
create_dir:
	mkdir -p bin/obj
clean: 
	rm -r bin
