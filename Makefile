objects = main.o RBT.o

test: $(objects)
	g++ -o test $(objects)
main.o: RBT.h

.PHONY: clean
clean:
	-rm test $(objects)