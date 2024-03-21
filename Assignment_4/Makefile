grid: driver.o grid.o
	g++ -o grid  driver.o grid.o

driver.o: driver.cpp grid.h
	g++ -c driver.cpp

grid.o: grid.cpp grid.h
	g++ -c grid.cpp



clean:
	rm *.o grid



