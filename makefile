cache: main.o estado.o cache.o
	g++ -o cache main.o estado.o cache.o

main.o: main.cpp cache.o
	g++ -c main.cpp

estado.o: estado.cpp estado.h
	g++ -c estado.cpp
	
cache.o: cache.cpp cache.h estado.o
	g++ -c cache.cpp
	
clean:
	rm *.o
	rm cache
