CFLAGS = -std=c11 -O2 -c -Wall -Wextra -ggdb
LIBS   = -lncurses -lmenu -ltinfo

OBJECTS = main.o fire.o menu.o

VPATH = src

cdm-df:$(OBJECTS)
	gcc -O2 -o $@ $^ $(LIBS)

main.o: main.c fire.o menu.o
	gcc $(CFLAGS) $<

fire.o: fire.c fire.h
	gcc $(CFLAGS) $<

menu.o: menu.c menu.h
	gcc $(CFLAGS) $<

clean: # remove all the object files
	rm cdm-df $(wildcard *.o)

tree:
	gcc -MM ${LIBS} *.[ch]

# Set phony targets
.PHONY: clean tree
