/* UFG - Instituto de Informática  *
 * Redes de Computadores 2         *
 * Alunos: Arnold Lima             *
 *         Luciano M. e M. Luiz    *   
 *		   Marcelo C. Dias         */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

#define   N_VERTICES        10
#define   INITIAL_VERTICE   4
#define   FINAL_VERTICE     7
#define   MIN_WEIGHT        1
#define   MAX_WEIGHT        10

//Functions Prototypes ----------------------
//Problem Solving Functions -----------------
int Random_Number(int, int);
void Clear_Graph(int **);
int **Init_Graph();
void Free_Graph(int ***);

//Printing Functions ------------------------
void Print_Graph();

//-------------------------------------------

#endif
