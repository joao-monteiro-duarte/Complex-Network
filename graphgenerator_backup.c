#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GRAPH_SIZE 5000
#define DEBUG 0
#define DEGREE_MAX 200
#define TOURNAMENT_LENGTH 10
#define NR_TOURNAMENTS 10
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
    int * average_aux;
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

void quota_deffiner(grafo* graph);

void natural_selection(grafo * graph);

grafo * graph_generator (int size, int degree);

int action_selector(grafo* graph, int agent, int opponent, int round);

void tournament_arc(grafo* graph);

void trust_game (grafo * graph, int agent, int opponent, int action_a, int action_o);

void graph_printer(grafo* graph);



int main (void){
    srand(time(NULL));
    int i = 0;
    grafo* graph = graph_generator(GRAPH_SIZE, DEGREE_MAX);
    //graph_printer(graph);
    tournament_arc(graph);
    printf("Final Results: \n");
    for(i = 0; i<8;i++)
    {
        printf("Strategy %d average: %d \n",i, graph->average_aux[i]/NR_TOURNAMENTS);
    }
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
    creator->average_aux = (int *) malloc(sizeof(int)*8);
    for(i = 0; i < size; i++)
        auxiliarymatrix[i] = (int*) malloc(sizeof(int)*size);
        
    creator->adjacency_vector=auxiliarymatrix;
    for(i = 0; i < size; i++){
        for(j = 0; j < size ; j++){
            creator->adjacency_vector[i][j] = -1;
            /*if(DEBUG == 1)
                creator->adjacency_vector[i][j] = 1;
            */
        }
    }
    /*if(DEBUG == 1)
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
    }*/
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
    int strat_count[8] = {0};
    printf("Meet your challengers: \n");
    for(i = 0; i < GRAPH_SIZE ; i++){
        //for(j = 0; j < graph->degree[i]; j++)
        j = graph->behaviour[i];
        strat_count[j] ++;
        //printf("\n");
    }

    for(i = 0; i < 8; i++){
        printf("Strategy %d count: %d \n", i, strat_count[i]);
        graph->average_aux[i] += strat_count[i];
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

void quota_deffiner(grafo* graph){
    int quota = GRAPH_SIZE/8;
    int i = 0;
    int aux = 0;
    int strat_number[8] = {0};
    for(i = 0; i < GRAPH_SIZE; i++){
        graph->behaviour[i] = rand()%8;
        aux = graph->behaviour[i];
        while(strat_number[aux] >= quota)
        {
            graph->behaviour[i] = rand()%8;
            aux = graph->behaviour[i];
        }
        strat_number[aux] += 1;
    }
}

void natural_selection(grafo * graph){
    int * old_vector = NULL;
    int i = 0;
    int j = 0;
    int aux = 0;
    int neighbour_select = 0;
    int neighbour = 0;
    int * aux_vector = NULL;

    aux_vector = (int *) malloc(sizeof(int)*GRAPH_SIZE);
    old_vector = (int *) malloc(sizeof(int)*GRAPH_SIZE);

    for(i = 0; i < GRAPH_SIZE; i++)
    {
        old_vector[i] = graph->behaviour[i];
    }

    for(i = 0; i < GRAPH_SIZE; i++){
        for(j = 0; j < GRAPH_SIZE; j++)
        {
            if(graph->adjacency_vector[i][j] == 1){
                aux_vector[aux] = j;
                aux++; 
            }
            graph->behaviour_aux[i][j] = 0;
        }
        
        neighbour_select = rand()%aux;
        neighbour = aux_vector[neighbour_select];
        if(graph->wallet[i] < graph->wallet[neighbour]){
            graph->behaviour[i] = old_vector[neighbour];
        }
        aux = 0;
        
    }
    for(i = 0; i < GRAPH_SIZE; i++){
        graph->wallet[i] = 100;
    }
}
void tournament_arc(grafo* graph){
    int round = 0;
    int action1 = 0;
    int action2 = 0;
    int i = 0;
    int j = 0;
    int tournament = 0;
    double total_actions = 0;
    double goodness_counter = 0;
    printf("LET'S GET READY TO RUMBLE !!!! \n \n \n");
    for(tournament = 0; tournament<NR_TOURNAMENTS; tournament++){
        printf("Tournament nr: %d \n", tournament);
        quota_deffiner(graph);
        //graph_printer(graph);
        for(round = 0; round < TOURNAMENT_LENGTH; round++){
            //printf("\nROUND %d! GO! \n \n", round);
            for(i = 0; i< GRAPH_SIZE; i++){
                //printf("Player %d analysis: \n", i);
                for(j = 0; j< i; j++)
                {
                    if(graph->adjacency_vector[i][j] == 1){
                        action1 = action_selector(graph, i, j, round);
                        action2 = action_selector(graph, j, i, round);
                        trust_game(graph, i, j, action1, action2);
                        /*if(action1 == 1 && action2 == 1)
                            printf("Jolly cooperation between %d and %d \n", i, j);
                        if(action1 == 1 && action2 == 0)
                            printf("Lies, Deception! %d betrayed by %d ! \n", i, j);
                        if(action1 == 0 && action2 == 1)
                            printf("Plot twist! %d betrays %d ! \n", i, j);
                        if(action1 == 0 && action2 == 0)
                            printf("%d and %d are bitter enemies \n", i, j);*/
                        total_actions += 2;
                        if(action1 == 1)
                            goodness_counter++;
                        if(action2 == 1)
                            goodness_counter++;
                    }
                }
            }
            natural_selection(graph);
            //graph_printer(graph);
        }
        
        graph_printer(graph);
        printf("\n \nTotal_actions: %lf \nTotal hope: %lf \nGoodness fraction: %lf \n", total_actions,goodness_counter,(goodness_counter/total_actions)*100);
        total_actions = 0;
        goodness_counter = 0;
    }
        

   /* printf("Final balance: \n");
    for(i = 0; i <  GRAPH_SIZE; i++){
        printf("Player %d: %d \n", i + 1, graph->wallet[i]);
    }*/
}

