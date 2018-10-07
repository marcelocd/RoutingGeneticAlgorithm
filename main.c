/* UFG - Instituto de Informática  *
 * Redes de Computadores 2         *
 * Alunos: Arnold Lima             *
 *         Luciano M. e M. Luiz    *   
 *		   Marcelo C. Dias         */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genetic_algorithm.h"

//Functions Prototypes ----------------------
//Control Functions -------------------------
void Control(Individual **, int ***);

//Printing Functions ------------------------
void Print_Path(Individual);

//-------------------------------------------

//Test --------------------------------------
int main(int argc, char *argv[]){
	srand(time(NULL));

	Individual **population = malloc(sizeof(Individual *) * POPULATION_SIZE);
	int **graph = NULL;

	Control(population, &graph);

	return 0;
}

//-------------------------------------------

//Functions Implementation ------------------
//Control Functions -------------------------
void Control(Individual **population, int ***graph){
	system("clear || cls");

	*graph = Init_Graph();
	Print_Graph(*graph);

	clock_t begin = clock();
	Init_Population(population, *graph);

	Individual *best_individual = Genetic_Algorithm(population, *graph);
	clock_t end = clock();

	printf("--------------------\nLowest Cost Path Found\n");
	printf("Cost: %d\n", best_individual->fitness);
	Print_Path(*best_individual);
	

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time Spent: %f\n", time_spent);

	Free_Graph(graph);
}

//Printing Functions ------------------------
void Print_Path(Individual individual){
	int i;

	printf("Path: [%hi", individual.gene[0]);

	for(i = 1 ; i <= individual.last_position ; i++)
		if(individual.gene[i] != individual.gene[i - 1])
			printf("|%hi", individual.gene[i]);

	printf("]\n\n");
}

//-------------------------------------------
