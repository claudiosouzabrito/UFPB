all: xbee

serial2.o: serial2.h serial2.cpp
	g++ -o serial2.o serial2.cpp -c -W -Wall -ansi -pedantic

mainteste2.o: mainteste2.cpp serial2.h
	g++ -o mainteste2.o mainteste2.cpp -c -W -Wall -ansi -pedantic

xbee: mainteste2.o serial2.o
	g++ -o xbee mainteste2.o serial2.o

clean:
	rm -rf *.o *~ xbee
	
