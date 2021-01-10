all: proj2.x

proj2.x: test_list.o
	g++ -o proj2.x test_list.o

test_list.o: test_list.cpp List.h List.hpp
	g++ -c test_list.cpp -std=c++11

clean:
	rm -f *.o proj2.x



