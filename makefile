
all: gol.c
	gcc -pthread gol.c

clean:
	rm a.out