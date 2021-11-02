import random 
import numpy
random.seed(4)
# In this model, an initial network of n0 nodes has to be generated (randomly) until all nodes
#are connected, and after, a node is picked randomly, and it's connected to some other node i,
#with probability p_i=k_i/E, where k_i is the degree of that node and E is the total number of
#edges.

def BA_generator(N,k):
    adjencyMatrix=[[0 for _ in range(N)] for _ in range(N)]
    adjencyMatrix[0][1]= 1
    adjencyMatrix[N-1][N-2] = 1


    for i in range(1,N-1):
        adjencyMatrix[i][i+1]=1
        adjencyMatrix[i][i-1]=1
        
    print(adjencyMatrix)
    E=N*k
    nE=N-1
    prob_list=[1/nE]
    for _ in range(N-2):
        prob_list.append(2/nE)
    prob_list.append(1/nE)
    print(prob_list)
    
    while nE != E:
        n1 = random.randint(0,N-1)
        while numpy.size(adjencyMatrix[n1])==N-1:
            n1 = random.randint(0,N-1)
        r = random.random()

        for i in range(N):  
            if sum(prob_list[:i+1]) > r and i!=n1 :
                print("n1")
                print(n1)
                print("i")
                print(i)
                adjencyMatrix[i][n1]=1
                adjencyMatrix[n1][i]=1
                nE+=1
                print(k)
                print(nE)
                print(prob_list)
                prob_list=[k*((nE-1)/nE) for k in prob_list]
                [prob_list[i],prob_list[n1]] = [numpy.size(adjencyMatrix[i])/nE,numpy.size(adjencyMatrix[n1])/nE]
                break
    print(nE)
    print(E)
    print(adjencyMatrix)


BA_generator(4,3)
