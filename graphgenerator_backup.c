#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRAPH_SIZE 1000
#define DEGREE_MAX 200
//#define COEFF Algo
/*
typedef struct Adjacency_list{
    int * adjacent_vertexes;
    //int * costs;
}adjl;
*/

typedef struct graph_net{
    int ** adjacency_vector;
    int * degree;
    int behaviour;
}grafo;


grafo * graph_generator (int size, int degree);

void random_walker(grafo* graph);

void graph_printer(grafo* graph);
int main (void){
    srand(time(NULL));
    grafo* graph = graph_generator(GRAPH_SIZE, DEGREE_MAX);
    graph_printer(graph);
    random_walker(graph);

    return 1;
}

grafo* graph_generator(int size, int degree){
    int i = 0;
    int j = 0;
    int connects = 0;
    int aux = 0;
    int randomizer = 0;
    int starter = 0;
    int limit = size - 1;
    grafo * creator = NULL;
    int ** auxiliarymatrix = NULL;

    creator = (grafo *) malloc(sizeof(grafo));


    auxiliarymatrix = (int **) malloc(sizeof(int *)* size);
    creator->degree = (int *) malloc(sizeof(int)* size);
    for(i = 0; i < size; i++)
        auxiliarymatrix[i] = (int*) malloc(sizeof(int)*size);
    creator->adjacency_vector=auxiliarymatrix;
    for(i = 0; i < size; i++){
        for(j = 0; j < size ; j++){
            creator->adjacency_vector[i][j] = -1;
        }
    }
    for (i = 0; i < size; i++)
    {
        for(j = 0; j < i; j++){
            randomizer = rand()%2;
            if(randomizer == 1 && creator->adjacency_vector[i][creator->degree[i]] == -1)
            {
                creator->adjacency_vector[i][creator->degree[i]] = j;
                creator->adjacency_vector[j][creator->degree[j]] = i;
                creator->degree[i] ++;
                creator->degree[j] ++;
            }
        } 
    }

    return creator;
}


void graph_printer(grafo* graph){
    int i = 0;
    int j = 0;
    for(i = 0; i < GRAPH_SIZE ; i++){
        //for(j = 0; j < graph->degree[i]; j++)
            printf("%d \n", graph->degree[i]);
        //printf("\n");
    }
}

void random_walker (grafo* graph){
    int start = rand()%GRAPH_SIZE;
    int end = start;
    int road = start;
    int next = 0;
    int RNG = 0;
    int steps = 0;
    while(end == start){
        end = rand()%GRAPH_SIZE;
    }

    printf("Started at node %d: \n", start);
    printf("%d", start);
    while(road != end){
        RNG =  rand()%graph->degree[road];
        next = graph->adjacency_vector[road][RNG];
        printf("-> %d \n", next);
        road = next;
        steps += 1;
    }
    printf("Took %d steps. \n", steps);
    printf("Ended successfully at: %d = %d \n", end, road);
}