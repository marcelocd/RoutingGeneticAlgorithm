/* UFG - Instituto de Informática  *
 * Redes de Computadores 2         *
 * Alunos: Arnold Lima             *
 *         Luciano M. e M. Luiz    *   
 *		   Marcelo C. Dias         */

#include <time.h>
#include "graph.h"
#include "genetic_algorithm.h"

#define   N_GENERATIONS     10000
#define   MUTATION_PROB     0.2

//Functions Prototypes ----------------------
//Initializing Functions --------------------
Individual *New_Individual();
Individual *Generate_Random_Individual(int **);

//Problem Solving Functions -----------------
int Fitness(Individual, int **);
void Assign_Mating_Probability(Individual **);
Individual *Random_Selection(Individual **);
bool Individuals_Are_Equal(Individual, Individual);
void Reproduce(Individual, Individual, Individual *, int **);
void Transfer_Individual(Individual *, Individual);
void Transfer_Population(Individual **, Individual **);
bool Small_Random_Probability();
void Mutate(Individual *);

//Printing Functions ------------------------
void Print_Family(Individual, Individual, Individual);

//-------------------------------------------

//Functions Implementation ------------------
//Initializing Functions --------------------
Individual *New_Individual(){
	Individual *new_individual = malloc(sizeof(Individual));

	new_individual->gene = malloc(sizeof(short) * GENE_SIZE);

	int i;

	for(i = 0 ; i < GENE_SIZE ; i++)
		new_individual->gene[i] = 0;

	return new_individual; 
}

Individual *Generate_Random_Individual(int **graph){
	Individual *individual = New_Individual();
	int i, j;

	individual->gene[0] = INITIAL_VERTICE;
	individual->last_position = Random_Number(1, GENE_SIZE - 1);
	individual->gene[individual->last_position] = FINAL_VERTICE;

	int random_number;

	for(i = 1 ; i < individual->last_position ; i++){
		random_number = Random_Number(0, N_VERTICES - 1);

		individual->gene[i] = (short) random_number;
	}

	individual->fitness = Fitness(*individual, graph);

	return individual;
}

void Init_Population(Individual **population, int **graph){
	int i;
	Individual *cleiton;

	for(i = 0 ; i < POPULATION_SIZE ; i++)
		population[i] = Generate_Random_Individual(graph);

	Assign_Mating_Probability(population);
}

//Problem Solving Functions -----------------
int Fitness(Individual individual, int **graph){
	int fitness = 0;
	int i;

	for(i = 1 ; i <= individual.last_position ; i++){
		if(individual.gene[i] != individual.gene[i - 1])
			if(graph[individual.gene[i]][individual.gene[i - 1]] == 0)
				fitness += (MAX_WEIGHT * 10);

		else
			fitness += graph[individual.gene[i]][individual.gene[i - 1]];
	}

	return fitness;
}

void Assign_Mating_Probability(Individual **population){
	float fitness_sum = 0;
	int i;

	for(i = 0 ; i < POPULATION_SIZE ; i++)
		fitness_sum += population[i]->fitness;

	if(fitness_sum == 0)
		for(i = 0 ; i < POPULATION_SIZE ; i++)
			population[i]->mating_probability = ((float) 1) / POPULATION_SIZE;
	
	else
		for(i = 0 ; i < POPULATION_SIZE ; i++)
			population[i]->mating_probability = population[i]->fitness / fitness_sum;
}

Individual *Random_Selection(Individual **population){
	float random_number = ((float) Random_Number(0, 1000)) / 1000;
	float aux = 0.0;
	int i;

	for(i = 0 ; i < POPULATION_SIZE ; i++){
		aux += population[i]->mating_probability;
	
		if(random_number <= aux)
			return population[i];
	}

	return population[i- 1];
}

bool Individuals_Are_Equal(Individual x, Individual y){
	if(x.last_position != y.last_position)
		return false;

	int i;

	for(i = 0 ; i <= x.last_position ; i++)
		if(x.gene[i] != y.gene[i])
			return false;

	return true;
}

void Reproduce(Individual x, Individual y, Individual *child, int **graph){
	int random_number = Random_Number(0, 1);
	int i;

	if(Random_Number(0, 1))
		child->last_position = x.last_position;

	else
		child->last_position = y.last_position;

	child->gene[0] = INITIAL_VERTICE;
	child->gene[child->last_position] = FINAL_VERTICE;

	
	for(i = 1 ; i < x.last_position && i < y.last_position ; i++){
		if((i + random_number) % 2)
			child->gene[i] = x.gene[i];

		else
			child->gene[i] = y.gene[i];
	}

	if(i < child->last_position){
		for(; i < x.last_position ; i++)
			child->gene[i] = x.gene[i];


		for(; i < y.last_position ; i++)
			child->gene[i] = y.gene[i];
	}

	if(Small_Random_Probability())
		Mutate(child);

	child->fitness = Fitness(*child, graph);
}

void Transfer_Individual(Individual *a, Individual b){
	a->last_position = b.last_position;
	a->fitness = b.fitness;

	int i;

	for(i = 0 ; i <= a->last_position ; i++)
		a->gene[i] = b.gene[i];
}

void Transfer_Population(Individual **a, Individual **b){
	int i;

	for(i = 0 ; i < POPULATION_SIZE ; i++)
		Transfer_Individual(a[i], *(b[i]));
}

bool Small_Random_Probability(){
	float random_number = Random_Number(0, 1000);

	random_number /= 1000;

	if(random_number <= MUTATION_PROB)
		return true;

	return false;
}

void Mutate(Individual *child){
	int random_number;
	int c;

	/* CASO O TAMANHO DO GENE MUDE */
	if(Random_Number(0, 1)){
		/* CASO AUMENTE */
		if(child->last_position == 1 || (Random_Number(0, 1) && child->last_position < (N_VERTICES - 1))){
			child->last_position++;
			child->gene[child->last_position] = FINAL_VERTICE;

			c = Random_Number(1, child->last_position - 1);

			random_number = Random_Number(0, N_VERTICES - 1);

			while(random_number == child->gene[c]){
				random_number = Random_Number(0, N_VERTICES - 1);
			}

			child->gene[c] = (short) random_number;

			return;
		}

		/* CASO DIMINUA */
		child->last_position--;
		child->gene[child->last_position] = FINAL_VERTICE;

		if(child->last_position <= 1) return;

		c = Random_Number(1, child->last_position - 1);

		random_number = Random_Number(0, N_VERTICES - 1);

		while(random_number == child->gene[c]){
			random_number = Random_Number(0, N_VERTICES - 1);
		}

		child->gene[c] = (short) random_number;

		return;
	}

	/* CASO CONTRÁRIO */
	if(child->last_position == 1)
		return;

	c = Random_Number(1, child->last_position - 1);
	random_number = Random_Number(0, N_VERTICES - 1);

	while(random_number == child->gene[c]){
		random_number = Random_Number(0, N_VERTICES - 1);
	}

 	child->gene[c] = (short) random_number;
}

Individual *Genetic_Algorithm(Individual **population, int **graph){
	Individual **new_population = malloc(sizeof(Individual *) * POPULATION_SIZE);

	int iteration = 1;
	int i, j;

	Individual *x, *y;
	Individual *child = New_Individual();
	Individual *best_individual = New_Individual();

	Transfer_Individual(best_individual, **population);

	/* FIND INITIAL BEST INDIVIDUAL */
	for(i = 1 ; i < POPULATION_SIZE ; i++)
		if(population[i]->fitness < best_individual->fitness)
			Transfer_Individual(best_individual, *(population[i]));

	for(i = 0 ; i < POPULATION_SIZE ; i++)
		new_population[i] = New_Individual();

	for(iteration = 1 ; iteration <= N_GENERATIONS ; iteration++){
		/*getchar();
		printf("------------------------------------------\nPopulation %d\n", iteration);
		Print_Population(population);*/

		/*if(iteration % 1000 == 0)
			printf("%d\n", iteration);*/

		Transfer_Individual(new_population[0], *best_individual);

		for(i = 1 ; i < POPULATION_SIZE ; i++){
			x = Random_Selection(population);
			y = Random_Selection(population);

			for(j = 1 ; Individuals_Are_Equal(*x, *y) && j <= 100 ; j++)
				y = Random_Selection(population);

			Reproduce(*x, *y, child, graph);

			if(child->fitness < best_individual->fitness){
				Transfer_Individual(best_individual, *child);
				
				/*printf("Best Individual Family ---------------------------\n");
				Print_Family(*x, *y, *best_individual);*/
				printf("--------------------\nBest Individual\n");
				printf("Generation: %d\n", iteration);
				Print_Individual(*best_individual);
			}

			Transfer_Individual(new_population[i], *child);
		}

		Assign_Mating_Probability(new_population);
		Transfer_Population(population, new_population);
	}

	Free_Population(population);
	Free_Population(new_population);
	free(new_population);

	return best_individual;
}

void Free_Population(Individual **population){
	int i, j;

	for(i = 0 ; i < POPULATION_SIZE ; i++){
		free(population[i]->gene);
		free(population[i]);
	}
}

//Printing Functions ------------------------
void Print_Individual(Individual individual){
	int i;

	printf("Fitness: %d\n", individual.fitness);
	printf("Gene: [%hi", individual.gene[0]);

	for(i = 1 ; i <= individual.last_position ; i++)
		printf("|%hi", individual.gene[i]);

	printf("]\n\n");
}

void Print_Population(Individual **population){
	int i, j;

	for(i = 0 ; i < POPULATION_SIZE ; i++){
		printf("Individual %d\n", i + 1);
		Print_Individual(*(population[i]));
	}
}

void Print_Family(Individual dad, Individual mom, Individual child){
	printf("Pai\n");
	Print_Individual(dad);
	printf("Mae\n");
	Print_Individual(mom);
	printf("Filho\n");
	Print_Individual(child);
}

//-------------------------------------------