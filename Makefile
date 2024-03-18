# Project Makefile ! Customize if needed.

CC = gcc
CXX = g++
CFLAGS = -Wall

#list of files to compile
files = raytracer_
objects = $(files:%_=%.o)

all: raytracer

$(objects) : $(cfiles)

raytracer: $(objects)
	@rm -f *.o *.gch
	@echo "raytracer created. Cleaning *.o and other useless files..."

clean:
	@rm -f *.o *.gch raytracer
	@echo "cleaning executable, *.o, *.gch"

