CC = gcc
CFLAGS = -ansi -Wall -pedantic
INCLUDES = funcoes.c
SRC =  main.c 


all: proj2

proj2: $(INCLUDES) $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o proj2
