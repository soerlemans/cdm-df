CFLAGS = -O2 -c -Wall -Wextra
LIBS   = -lncurses -ltinfo

OBJECTS = main.o fire.o

VPATH = src

cdm-df:$(OBJECTS)
	gcc -O2 -o $@ $^ $(LIBS)

main.o: main.c fire.o
	gcc $(CFLAGS) $<

fire.o: fire.c fire.h
	gcc $(CFLAGS) $<

clean: # remove all the object files
	rm cdm-df $(wildcard *.o)

# Set phony targets
.PHONY: clean
