vector: vector.c vector.h
	gcc main.c vector.c -o vector -g

.PHONY: check clean

check:
	valgrind --leak-check=full ./vector

clean:
	rm vector
