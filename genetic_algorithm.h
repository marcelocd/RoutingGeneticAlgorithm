/* UFG - Instituto de Informática  *
 * Redes de Computadores 2         *
 * Alunos: Arnold Lima             *
 *         Luciano M. e M. Luiz    *   
 *		   Marcelo C. Dias         */

#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_AGLORITHM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "graph.h"

#define   GENE_SIZE         10
#define   POPULATION_SIZE   10

//Problem Models ----------------------------
typedef struct{
	short *gene;
	short last_position;
	int fitness;
	float mating_probability;
}Individual;

//-------------------------------------------

//Functions Prototypes ----------------------
//Initializing Functions --------------------
void Init_Population(Individual **, int **);

//Genetic Algorithm Function ----------------
Individual *Genetic_Algorithm(Individual **, int **);
void Free_Population(Individual **);

//Printing Functions ------------------------
void Print_Individual(Individual);
void Print_Population(Individual **);
//-------------------------------------------

#endif
