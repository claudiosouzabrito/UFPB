all: addac.o ../inv/goldenmodel/inv.o ../mux/goldenmodel/mux.o ../acc/goldenmodel/acc.o ../somador/goldenmodel/somador.o  
	cc -o all addac.o inv.o mux.o acc.o somador.o  

addac.o: addac.c
	cc -c addac.c

../inv/goldenmodel/inv.o: ../inv/goldenmodel/inv.c ../inv/goldenmodel/inv.h
	cc -c ../inv/goldenmodel/inv.c

../mux/goldenmodel/mux.o: ../mux/goldenmodel/mux.c ../mux/goldenmodel/mux.h
	cc -c ../mux/goldenmodel/mux.c

../acc/goldenmodel/acc.o: ../acc/goldenmodel/acc.c ../acc/goldenmodel/acc.h
	cc -c ../acc/goldenmodel/acc.c

../somador/goldenmodel/somador.o: ../somador/goldenmodel/somador.c ../somador/goldenmodel/somador.h
	cc -c ../somador/goldenmodel/somador.c

clean: 
	rm all addac.o inv.o acc.o mux.o somador.o