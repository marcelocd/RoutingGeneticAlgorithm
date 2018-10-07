/* UFG - Instituto de Informática  *
 * Redes de Computadores 2         *
 * Alunos: Arnold Lima             *
 *         Luciano M. e M. Luiz    *   
 *		   Marcelo C. Dias         */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"


//Functions Prototypes ----------------------
//Problem Solving Functions -----------------
int **New_Graph();

//Printing Functions ------------------------
void Print_Border_Of_Graph();

//-------------------------------------------

//Functions Implementations -----------------
//Problem Solving Functions -----------------
int Random_Number(int min, int max){
    return min + (rand() % (max - min + 1));
}

int **New_Graph(){
	int **new_graph;

	if((new_graph = malloc(sizeof(int *) * N_VERTICES)) == NULL)
		return NULL;

	int index;

	for(index = 0 ; index < N_VERTICES ; index++)
		if((*(new_graph + index) = malloc(sizeof(int) * N_VERTICES)) == NULL){
			Free_Graph(&new_graph);
			break;
		}

	return new_graph;
}

void Clear_Graph(int **graph){
	int i, j;

	for(i = 0 ; i < N_VERTICES ; i++)
		for(j = 0 ; j < N_VERTICES ; j++)
			graph[i][j] = 0;
}

int **Init_Graph(){
	int **graph = New_Graph();

	Clear_Graph(graph);

	graph[0][1] = 1;
	graph[0][4] = 8;
	graph[0][5] = 6;
	graph[0][6] = 7;
	graph[1][3] = 3;
	graph[1][5] = 5;
	graph[1][8] = 3;
	graph[2][6] = 7;
	graph[2][7] = 9;
	graph[2][8] = 6;
	graph[2][9] = 3;
	graph[3][4] = 1;
	graph[3][5] = 9;
	graph[3][8] = 3;
	graph[4][8] = 1;
	graph[4][9] = 6;
	graph[5][7] = 8;
	graph[6][8] = 6;
	graph[6][9] = 5;
	graph[8][9] = 2;

	int i, j;

	for(i = 0 ; i < N_VERTICES ; i++)
		for(j = 0 ; j < N_VERTICES ; j++)
			if(i < j)
				if(graph[i][j] != 0)
					graph[j][i] = graph[i][j];

	/*
	graph[0][1] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[0][4] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[0][5] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[0][6] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[1][3] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[1][5] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[1][8] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[2][6] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[2][7] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[2][8] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[2][9] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[3][4] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[3][5] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[3][8] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[4][8] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[4][9] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[5][7] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[6][8] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[6][9] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	graph[8][9] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
	*/

	/*for(i = 0 ; i < N_VERTICES ; i++)
		for(j = 0 ; j < N_VERTICES ; j++)
			if(i < j)
				if(Random_Number(1, 10) == 1){
					graph[i][j] = Random_Number(MIN_WEIGHT, MAX_WEIGHT);
					graph[j][i] = graph[i][j];
				}*/


	return graph;
}

void Free_Graph(int ***graph){
	if(*graph != NULL){
		int index;

		for(index = 0 ; index < N_VERTICES ; index++)
			free(*(*graph + index));

		free(*graph);
	}

	*graph = NULL;
}

//Printing Functions ------------------------
void Print_Border_Of_Graph(){
	int j;

	printf("+");

	for(j = 1 ; j <= N_VERTICES ; j++)
		printf("--");

	printf("-+\n");
}

void Print_Graph(int **graph){
	int i, j;

	Print_Border_Of_Graph();

	for(i = 0 ; i < N_VERTICES ; i++){
		printf("| ");

		for(j = 0 ; j < N_VERTICES ; j++)
				printf("%d ", graph[i][j]);

		printf("|\n");
	}

	Print_Border_Of_Graph();
	printf("\n");
}

//-------------------------------------------
