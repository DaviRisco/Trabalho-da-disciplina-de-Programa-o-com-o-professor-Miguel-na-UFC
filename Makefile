ALL:	main

main:	main.o  funcoes.o
		gcc main.o funcoes.o -o main

main.o:	main.c funcoes.h
		gcc -c main.c

vetmat.o:	funcoes.c funcoes.h
			gcc -c funcoes.c

clean:
	rm -f *.o main