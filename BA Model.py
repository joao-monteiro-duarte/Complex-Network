import random 
import numpy
random.seed(4)
# In this model, an initial network of n0 nodes has to be generated (randomly) until all nodes
#are connected, and after, a node is picked randomly, and it's connected to some other node i,
#with probability p_i=k_i/E, where k_i is the degree of that node and E is the total number of
#edges.

#N-total number of nodes; m-number of connections made by each node added to the network (in essence, the average degree); 
# m0-number of initial nodes (m<=m0)
def BA_generator(N, m, m0):
    file = open("BAModel{0}NodesAnd{1}AverageDegree.txt".format(N,m*2),"w")

    adjencyMatrix=[[0 for _ in range(N)] for _ in range(N)]
    adjencyMatrix[0][1]=1
    adjencyMatrix[m0-1][m0-2]=1

    for i in range(1,m0-1):
        adjencyMatrix[i][i+1]=1
        adjencyMatrix[i][i-1]=1
    
    nE = (m0-1)
    #prob_i= #neighbours_i/nE
    prob_list=[0]*N

          
    n=m0
    while n <= N:
        print(n)



        for i in range(n):

            neighbours_i = sum(adjencyMatrix[i])
            prob_list[i] = prob_list[i-1] + neighbours_i/(2*nE)
          
        for _ in range(m+1):
            r=random.random()
            i=0
            while i<n:
                if prob_list[i] >= r:

                    if adjencyMatrix[n-1][i] == 1:
                        r=random.random()
                        i=0


                    else:
                        adjencyMatrix[n-1][i]=1

                        adjencyMatrix[i][n-1]=1

                        prob_list[n-1]=prob_list[n-2]
                        
                        break
                else:
                    i+=1

        n+=1
        nE+=m
    print()
    for i in range (N):
        for j in range(N):
            if adjencyMatrix[i][j]==1:
                file.write("1 ")
            else:
                file.write("0 ")

        file.write("\n")
    print(adjencyMatrix)
    return adjencyMatrix


BA_generator(200,2,3)