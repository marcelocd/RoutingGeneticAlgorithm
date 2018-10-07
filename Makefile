# Makefile: RoutingGeneticAlgorithm

CC = gcc
SRCS = main.c genetic_algorithm.c graph.c
OBJS = main.o genetic_algorithm.o graph.o
HEADERS = genetic_algorithm.h graph.h
APP_NAME = main

all:	$(APP_NAME)
$(APP_NAME):	$(OBJS)	$(HEADERS)
		$(CC) -o $(APP_NAME) $(OBJS)

objects:
		$(CC) -c $(SRCS)

clean:
		rm -f *.o $(APP_NAME)