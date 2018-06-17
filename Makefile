test: test.o bin_tree.o 
	gcc -o test test.o bin_tree.o -lm

test.o: test.c
	gcc -c test.c

bin_tree.o: bin_tree.c bin_tree.h 
	gcc -c bin_tree.c

clean:
	rm test test.o bin_tree.o 
