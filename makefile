CC = gcc
OBJ = main.o map.o game.o world.o terminal.o algorithm.o
EXEC = maze
CFLAGS = -Wall -pedantic -ansi 

maze: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) 

main.o: main.c map.h game.h world.h terminal.h algorithm.h
	$(CC) $(CFLAGS) -c main.c -D DARK

map.o: map.c
	$(CC) $(CFLAGS) -c map.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

world.o: world.c
	$(CC) $(CFLAGS) -c world.c

terminal.o: terminal.c
	$(CC) $(CFLAGS) -c terminal.c

algorithm.o: algorithm.c
	$(CC) $(CFLAGS) -c algorithm.c

clean:
	rm -f $(OBJ) $(EXEC)
