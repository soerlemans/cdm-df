#!/bin/bash

#script file that generates a makefile for this project

echo -e 'CXXFLAGS = -std=c++17 -O2 -c -Wall -Wextra -Wno-narrowing #--help=optimizers' > makefile
echo -e 'LIBS = -lncurses -ltinfo\n' >> makefile

echo -en 'OBJECTS =\\\n\t' >> makefile

objects="$(ls | grep "\.cpp$" | sed "s/.cpp/.o/g")"
for object in $objects
do
    echo -n "$object " >> makefile
done

echo -e '\nVPATH = src\n' >> makefile

echo 'drawterm : $(OBJECTS)'         >> makefile
echo -e '\tg++ -O2 -o $@ $^ $(LIBS)\n' >> makefile

cpp_files="$(ls *.cpp)"

for file in $cpp_files
do
    gcc -MM $file >> makefile
    echo -e '\tg++ $(CXXFLAGS) $<\n' >> makefile
done

echo -e 'clean :  #remove all the executable and all the object files' >> makefile
echo -e '\trm drawterm $(wildcard *.o)\n'   >> makefile
echo -e '.PHONY: clean\n' >> makefile
