CFLAGS = -std=c11 -O0 -c -Wall -Wextra -ggdb # Debug flags
#CFLAGS = -std=c11 -O2 -c -Wall -Wextra -ggdb
LIBS   = -lncurses -lmenu -ltinfo

OBJECTS = main.o fire.o menu.o utils.o

VPATH = src


cdm-df:$(OBJECTS)
	gcc -O2 -o $@ $^ $(LIBS)


main.o: main.c fire.o menu.o
	gcc $(CFLAGS) $<

fire.o: fire.c fire.h utils.o
	gcc $(CFLAGS) $<

menu.o: menu.c menu.h utils.o
	gcc $(CFLAGS) $<

utils.o: utils.c utils.h
	gcc $(CFLAGS) $<

# Phony targets
clean: # Remove all the object files
	rm cdm-df $(wildcard *.o)

tree: # List the dependency tree
	gcc -MM ${LIBS} *.[ch]

tags: # update the tags file
	etags *.[ch]

# Set phony targets
.PHONY: clean tree tags
