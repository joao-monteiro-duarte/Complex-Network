#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define GRAPH_SIZE 5000


int main(void){
    int i = 0;
    int j = 100;
    int **lattice = NULL;
    FILE * fp;
    lattice = (int**) malloc(sizeof(int*)*GRAPH_SIZE);
    for(i = 0; i<GRAPH_SIZE; i++){
        lattice[i] = (int*) malloc(sizeof(int)*GRAPH_SIZE);
    }
    fp = fopen("lattice.txt","w");
    for(i = 0; i < GRAPH_SIZE; i++){
        if(i%j == 0 && i!=0){
            j = j+100;
        }
        if(i+1<j){
            lattice[i][i+1] = 1;
        }
        if(i+100 < GRAPH_SIZE){
            lattice[i][i+100]=1;
        }
        if(i-1>=j-100){
            lattice[i][i-1] = 1;
        }
        if(i-100>=0){
            lattice[i][i-100] = 1;
        }   
    }
    
    for(i = 0; i<GRAPH_SIZE; i++){
        for(j = 0; j<GRAPH_SIZE; j++){
            fprintf(fp,"%d ",lattice[i][j]);
        }
        fprintf(fp,"\n");
    }
}