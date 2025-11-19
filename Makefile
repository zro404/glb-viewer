all: main

main: create_dir
	clang -c src/*.c
	mv *.o bin/obj/
	clang bin/obj/*.o -o bin/viewer

.PHONY: clean create_dir
create_dir:
	mkdir -p bin/obj
clear:
	rm -r bin
