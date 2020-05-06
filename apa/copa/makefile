all: apa

apa: main.o vizinhancas.o construtiva.o heuristica.o
	 gcc -o apa main.o vizinhancas.o construtiva.o heuristica.o -lm

main.o: main.o vizinhancas.h construtiva.h heuristica.h
		gcc -c -g main.c

vizinhancas.o: vizinhancas.c vizinhancas.h
			   gcc -c vizinhancas.c

construtiva.o: construtiva.h construtiva.c
				gcc -c construtiva.c

heuristica.o: heuristica.h heuristica.c
				gcc -c heuristica.c


clean:
	  rm -rf *.o *~ apa