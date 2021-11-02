#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRAPH_SIZE 25
#define DEBUG 0
#define DEGREE_MAX 200
#define TOURNAMENT_LENGTH 5
//#define COEFF Algo
/*
typedef struct Adjacency_list{
    int * adjacent_vertexes;
    //int * costs;
}adjl;
*/

typedef struct graph_net{
    int ** adjacency_vector;
    int *behaviour;
    int *wallet;
    int **behaviour_aux;
}grafo;

/*
* 0: Copycat - Start coop, replicate last move
* 1: Cheater - Always cheat
* 2: Cooperator - Always Coop
* 3: Grudger - Always coop. If cheated, always cheat
* 4: Detective - Starts coop, coop, cheat, coop. If cheated, becomes copycat, else always cheat.
* 5: Copykitten - Cheats only if 2x cheat
* 6: Simpleton - Start cooperate, if cooperated back, keeps same move, if cheated, changes move
* 7: Random - Coops or cheats randomly
*
*/


grafo * graph_generator (int size, int degree);

int action_selector(grafo* graph, int agent, int opponent, int round);

void tournament_arc(grafo* graph);

void trust_game (grafo * graph, int agent, int opponent, int action_a, int action_o);

void graph_printer(grafo* graph);

int main (void){
    srand(time(NULL));
    grafo* graph = graph_generator(GRAPH_SIZE, DEGREE_MAX);
    graph_printer(graph);
    tournament_arc(graph);
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
    creator->behaviour = (int * ) malloc(sizeof(int)*size);
    creator->wallet = (int * ) malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
        auxiliarymatrix[i] = (int*) malloc(sizeof(int)*size);
        
    creator->adjacency_vector=auxiliarymatrix;
    for(i = 0; i < size; i++){
        for(j = 0; j < size ; j++){
            creator->adjacency_vector[i][j] = -1;
            if(DEBUG == 1)
                creator->adjacency_vector[i][j] = 1;
        }
    }
    if(DEBUG == 1)
    {
        for(i = 0; i < size; i++){
            creator->behaviour[i] = i;
        }
        creator->behaviour_aux = (int **) malloc(sizeof(int*)*size);

        for(i = 0; i < size; i++){
            creator->behaviour_aux[i] = (int *) malloc(sizeof(int)*size);
            creator->wallet[i] = 100;
        }
        return creator;
    }
    for (i = 0; i < size; i++)
    {
        creator->behaviour[i] = rand()%8;
        for(j = 0; j < i; j++){
            randomizer = rand()%2;
            if(randomizer == 1)
            {
                creator->adjacency_vector[i][j] = 1;
                creator->adjacency_vector[j][i] = 1;
            }
        } 
    }
    creator->behaviour_aux = (int **) malloc(sizeof(int*)*size);

    for(i = 0; i < size; i++){
        creator->behaviour_aux[i] = (int *) malloc(sizeof(int)*size);
        creator->wallet[i] = 100;
    }
    return creator;

}


void graph_printer(grafo* graph){
    int i = 0;
    int j = 0;
    printf("Meet your challengers: \n");
    for(i = 0; i < GRAPH_SIZE ; i++){
        //for(j = 0; j < graph->degree[i]; j++)
            printf("%d \n", graph->behaviour[i]);
        //printf("\n");
    }
}

int action_selector(grafo* graph, int agent, int opponent, int round){
    
    switch(graph->behaviour[agent]){
        case 0:
            if(round == 0)
                return 1;
            return graph->behaviour_aux[agent][opponent];
            break;
        case 1:
            return 0;
            break;
        case 2:
            return 1;
            break;
        case 3:
            if(round == 0)
                return 1;
            if (graph->behaviour_aux[agent][opponent] == 1)
                return 0;
            else if(graph->behaviour_aux[agent][opponent] == 0)
                return 1;
            break;
        case 4:
            if(round == 0)
                return 1;
            if(round == 1)
                return 0;
            if(round == 2)
                return 1;
            if(round == 3)
                return 1;
            if(graph->behaviour_aux[agent][opponent] == 0)
                return 0;
            if(graph->behaviour_aux[agent][opponent] == 1)
                graph->behaviour[agent] = 0;
                return 0;
            break;
        case 5:
            if(round == 0)
                return 1;
            if(graph->behaviour_aux[agent][opponent] <= 1)
                return 1;
            else{
                return 0;
            }
            break;
        case 6:
            if(round == 0)
                return 1;
            if(graph->behaviour_aux[agent][opponent] == 0)
                return 1;
            else if(graph->behaviour_aux[agent][opponent] == 1)
                return 0;
            break;
        case 7:
            return rand()%2;
            break;
        default:
            return 1;
            break;
    }
    printf("Fatal ERROR: no action selected \n");
    return 1;
}

void trust_game (grafo * graph, int agent, int opponent, int action_a, int action_o){
    if(action_a == 1 && action_o == 1){
        graph->wallet[agent] +=2;
        graph->wallet[opponent] +=2;
        switch(graph->behaviour[agent]){
            case 0:
                graph->behaviour_aux[agent][opponent] = 1; 
                break;
            case 3:
                if(graph->behaviour_aux[agent][opponent] != 1)
                    graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 4:
                if(graph->behaviour_aux[agent][opponent] != 1)
                    graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 5:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 6:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 7:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            default: break;
        }
        switch(graph->behaviour[opponent]){
            case 0:
                graph->behaviour_aux[opponent][agent] = 1; 
                break;
            case 3:
                if(graph->behaviour_aux[opponent][agent] != 1)
                    graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 4:
                if(graph->behaviour_aux[opponent][agent] != 1)
                    graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 5:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 6:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 7:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            default: break;
        }
        return;
    }else if(action_a == 1 && action_o == 0){
        graph->wallet[opponent] +=3;
        graph->wallet[agent] -=1;
        switch(graph->behaviour[agent]){
            case 0:
                graph->behaviour_aux[agent][opponent] = 0; 
                break;
            case 3:
                graph->behaviour_aux[agent][opponent] = 1;
                break;
            case 4:
                graph->behaviour_aux[agent][opponent] = 1;
                break;
            case 5:
                graph->behaviour_aux[agent][opponent] += 1;
                break;
            case 6:
                graph->behaviour_aux[agent][opponent] = 1;
                break;
            case 7:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            default: break;
        }
        switch(graph->behaviour[opponent]){
            case 0:
                graph->behaviour_aux[opponent][agent] = 1; 
                break;
            case 3:
                break;
            case 4:
                if(graph->behaviour_aux[opponent][agent] != 1)
                    graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 5:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 6:
                graph->behaviour_aux[opponent][agent] = 1;
                break;
            case 7:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            default: break;
        }
        return;
    }else if(action_a == 0 && action_o == 0){
         switch(graph->behaviour[agent]){
            case 0:
                graph->behaviour_aux[agent][opponent] = 0; 
                break;
            case 3:
                break;
            case 4:
                graph->behaviour_aux[agent][opponent] = 1;
                break;
            case 5:
                graph->behaviour_aux[agent][opponent] += 1;
                break;
            case 6:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 7:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            default: break;
        }
        switch(graph->behaviour[opponent]){
            case 0:
                graph->behaviour_aux[opponent][agent] = 0; 
                break;
            case 3:
                break;
            case 4:
                if(graph->behaviour_aux[opponent][agent] != 1)
                    graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 5:
                graph->behaviour_aux[opponent][agent] += 1;
                break;
            case 6:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            case 7:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            default: break;
        }
        return;
    }else if(action_a == 0 && action_o == 1){
        graph->wallet[agent] +=3;
        graph->wallet[opponent] -=1;
        switch(graph->behaviour[opponent]){
            case 0:
                graph->behaviour_aux[opponent][agent] = 0; 
                break;
            case 3:
                graph->behaviour_aux[opponent][agent] = 1;
                break;
            case 4:
                graph->behaviour_aux[opponent][agent] = 1;
                break;
            case 5:
                graph->behaviour_aux[opponent][agent] += 1;
                break;
            case 6:
                graph->behaviour_aux[opponent][agent] = 1;
                break;
            case 7:
                graph->behaviour_aux[opponent][agent] = 0;
                break;
            default: break;
        }
        switch(graph->behaviour[agent]){
            case 0:
                graph->behaviour_aux[agent][opponent] = 1; 
                break;
            case 3:
                break;
            case 4:
                if(graph->behaviour_aux[agent][opponent] != 1)
                    graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 5:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            case 6:
                graph->behaviour_aux[agent][opponent] = 1;
                break;
            case 7:
                graph->behaviour_aux[agent][opponent] = 0;
                break;
            default: break;
        }
        return;
    }
    return;
}
void tournament_arc(grafo* graph){
    int round = 0;
    int action1 = 0;
    int action2 = 0;
    int i = 0;
    int j = 0;
    printf("LET'S GET READY TO RUMBLE !!!! \n \n \n");
    for(round = 0; round < TOURNAMENT_LENGTH; round++){
        printf("\nROUND %d! GO! \n \n", round);
        for(i = 0; i< GRAPH_SIZE; i++){
            printf("Player %d analysis: \n", i);
            for(j = 0; j< i; j++)
            {
                if(graph->adjacency_vector[i][j] == 1){
                    action1 = action_selector(graph, i, j, round);
                    action2 = action_selector(graph, j, i, round);
                    trust_game(graph, i, j, action1, action2);
                    if(action1 == 1 && action2 == 1)
                        printf("Jolly cooperation between %d and %d \n", i, j);
                    if(action1 == 1 && action2 == 0)
                        printf("Lies, Deception! %d betrayed by %d ! \n", i, j);
                    if(action1 == 0 && action2 == 1)
                        printf("Plot twist! %d betrays %d ! \n", i, j);
                    if(action1 == 0 && action2 == 0)
                        printf("%d and %d are bitter enemies \n", i, j);
                }
            }
        }
    }

    printf("Final balance: \n");
    for(i = 0; i <  GRAPH_SIZE; i++){
        printf("Player %d: %d \n", i + 1, graph->wallet[i]);
    }
}

