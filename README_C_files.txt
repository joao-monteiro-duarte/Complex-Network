This readme pertains to the use of all programs developed using C language:

lattice.c:

Given a maximum number of nodes, generates a lattice with a square pattern. In other words, 
each node has at most 4 edges.  Currently generates a lattice representing a 50*100 square 
graph.


Graph generator files:

Divided depending on the input format. Two of them receive as inputs the name of a txt file
where an adjacency matrix or a list of edges are stored. The other generates, for a given
graph size, a random graph.

They share the following structure:

--	Graph generator:

Creates the graph used for the trust game. Only function that is different across the 3 files:

-Generates an adjacency matrix where 1 indicates a connection and -1 indicates no connection.

If a correctly formatted adjacency matrix is received, for all lines in the txt file, it checks
each even character in the total line length and fills out the adjacency matrix accordingly.

If a list of edges is received, by reading each line, we know what lines and columns to fill
out in the adjacency matrix by reading the two corresponding indexing integers.

The random graph generator simply generates a number between 0 and 1 for each possible link.
If it generates a 1, it creates a link.

--	Graph printer:

Checks all nodes in a given graph and counts the number of players currently using each strategy
then proceeds to print out the corresponding numbers. Since it is only used after the end of each
tournament, it additionally adds the strategy counters to an auxiliary vector that is used to calculate
the final strategy average.

--	Action selector:

A switch case based on the used strategy: (see: https://ncase.me/trust/)

0-Copycat:
Starts with cooperation then copies the opponent's last move;

1-Always Cheat:
Always defects;

2-Always Cooperate:
Always cooperates;

3-Grudger:
Cooperates until cheated. If cheated, always cheat.

4-Detective:
Starts cooperate, cheat, cooperate, cooperate. If cheated, becomes copycat. Else, always cheated.

5-Copykitten:
Like copycat but only cheats if cheated two times in a row;

6-Simpleton:
Starts by cooperating. If cooperated, keeps same strategy. If cheated, changes strategy.

7-Random:
50/50 on whether he cheats or cooperates.

--	Trust Game:

Given two actions between two players, computes the fitness of each player after resolving the trust game
then proceeds to update all necessary auxiliary variables if needed.

--	Quota deffiner:

Ensures an even spread of all strategies at the start of each tournament.

--	Natural selection:

At the end of each round, updates each node based on the fitness of a random neighbour then proceeds to
reset the fitness of all players.

--	Tournament arc:

Plays a given number of tournaments that each have a number of rounds.

Each round all nodes interact with all nodes and then are updated based on their fitness.

After all rounds are played, the strategies are counted as well as the total number of cooperative actions
out of all actions taken.

Each new tournament starts with the same number of players using each strategy.

