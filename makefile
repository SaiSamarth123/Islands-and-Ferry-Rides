
Project6: Proj6main.o
	g++ -o Project6 Proj6main.o

Proj6main.o: Proj6main.cpp Island.h
	g++ -c Proj6main.cpp

clean:
	rm  Proj6main.o Project6