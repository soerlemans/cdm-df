CFLAGS = -std=c11 -O2 -c -Wall -Wextra
LIBS   = -lncurses -ltinfo

OBJECTS = main.o fire.o dialog.o

VPATH = src

cdm-df:$(OBJECTS)
	gcc -O2 -o $@ $^ $(LIBS)

main.o: main.c fire.o dialog.o
	gcc $(CFLAGS) $<

fire.o: fire.c fire.h
	gcc $(CFLAGS) $<

dialog.o: dialog.c dialog.h
	gcc $(CFLAGS) $<

clean: # remove all the object files
	rm cdm-df $(wildcard *.o)

# Set phony targets
.PHONY: clean
