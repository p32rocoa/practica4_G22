all: main 

main: main.o agenda.o profesor.o
	@g++ -o main main.o agenda.o profesor.o
	@echo "Makefile: Creación de <main>"

main.o: main.cpp
	@g++ -c main.cpp -Wall
	@echo "Makefile: Creación de <main.o>"

agenda.o: agenda.cpp
	@g++ -c agenda.cpp -Wall
	@echo "Makefile: Creación de <agenda.o>"

profesor.o: profesor.cpp
	@g++ -c profesor.cpp -Wall
	@echo "Makefile: Creación de <profesor.o>"


.PHONY: clean cleanExe

clean:
	#@rm -f *.o
	@echo "Makefile: Ficheros objeto eliminados."

cleanExe:
	#@rm -f main
	@echo "Makefile: Archivos ejecutables eliminados."
