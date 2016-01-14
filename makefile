OPTIONS = -std=c90 -pedantic -Wall -Werror

a.out: main.o PlayGame.o Create.o ListImplementation.o Load.o Functions.h Run.o
	gcc $(OPTIONS) -lncurses -o crun.out main.o PlayGame.o Create.o ListImplementation.o Load.o Run.o

main.o: main.c ListInterface.h ListType.h Functions.h
	gcc $(OPTIONS) -c main.c

PlayGame.o: PlayGame.c ListInterface.h ListType.h Load.c Functions.h
	gcc $(OPTIONS) -c PlayGame.c

ListImplementation.o: ListImplementation.c ListInterface.h ListType.h Functions.h
	gcc $(OPTIONS) -c ListImplementation.c

Create.o: Create.c ListInterface.h ListType.h Functions.h
	gcc $(OPTIONS) -c Create.c

Load.o: Load.c ListInterface.h ListType.h Functions.h
	gcc $(OPTIONS) -c Load.c

Run.o: Run.c ListInterface.h ListType.h Functions.h
	gcc $(OPTIONS) -c Run.c

clean:
	rm *.o crun.out