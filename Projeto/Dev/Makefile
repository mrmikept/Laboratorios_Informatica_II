FLAGS=-Wall -Wextra -pedantic-errors -O2
DFLAGS=-Wall -Wextra -pedantic-errors -O2 -g
LIBS=-lm
CFILES=*.c
FILES=*.c *.h
EXE=projeto
CC=gcc

all: 
	$(CC) -o $(EXE) $(FLAGS) $(CFILES) $(LIBS)

gdb:
	$(CC) -o $(EXE) $(DFLAGS) $(CFILES) $(LIBS)

zip:
	mkdir code
	cp $(FILES) code
	zip -9r submissao.zip code
	rm -rf code

