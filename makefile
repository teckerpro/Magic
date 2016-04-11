all: saturated_add

saturated_add: main.o func4pix.o test.o
	g++ main.o func4pix.o test.o -o saturated_add

main.o: main.cpp
	g++ -c main.cpp

func4pix.o: func4pix.cpp
	g++ -c func4pix.cpp

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm -rf *.o saturated_add