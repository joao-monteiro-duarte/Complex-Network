#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define GRAPH_SIZE 5000


int main(void){
    int i = 0;
    int j = 0;
    int ** regular= NULL;
    FILE * fp;
    regular = (int**) malloc(sizeof(int*)*GRAPH_SIZE);
    for(i = 0; i<GRAPH_SIZE; i++){
        regular[i] = (int*) malloc(sizeof(int)*GRAPH_SIZE);
    }
    fp = fopen("regular.txt","w");
    for(i = 0; i < GRAPH_SIZE; i++){
        if(i+1<GRAPH_SIZE)
            regular[i][i+1] = 1;
        else   
            regular[i][0] = 1;
        if(i+2<GRAPH_SIZE)
            regular[i][i+2] = 1;
        else if(i+1<GRAPH_SIZE)
            regular[i][0] = 1;
        else
            regular[i][1] = 1;

        if(i-1>= 0)
            regular[i][i-1] = 1;
        else
            regular[i][GRAPH_SIZE-1] = 1;

        if(i-2>= 0)
            regular[i][i-2] = 1;
        else if(i-1>=0)
            regular[i][GRAPH_SIZE-1] = 1;  
        else
            regular[i][GRAPH_SIZE-2] = 1;
    }
    
    for(i = 0; i<GRAPH_SIZE; i++){
        for(j = 0; j<GRAPH_SIZE; j++){
            fprintf(fp,"%d ",regular[i][j]);
        }
        fprintf(fp,"\n");
    }
}