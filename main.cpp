#include <iostream>
#include <climits>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime> 
#include <cassert>
#include <unordered_set>
#include "graph.hpp"
#include "time.h"

using namespace std;

Graph random_clique(int n){
	Graph g(n);

	int i;
	int j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < i)
		{
			g.add_edge(i, j, 1 + rand() % n);
			j += 1;
		}
		i += 1;
	}

	return g;
}

/******************/
/* Floyd-Warshall */
/******************/

/*
 *
 *
 * Entr ́ees : Un graphe pond ́er ́e G = (|S|, |A|, w)
 1 2 3
 4 5
 6 7 8
 9
Sorties : La matrice des distances entre chaque paire de points
pour i,j = 1,...,n faire D[i][j][0] ← ∞ D[i][i][0] ← 0
pour ij ∈ A faire D[i][j][0] ← w(ij)
pour k = 1,...,n faire pour i,j = 1,...,n faire
D[i][j][k] ← min(D[i][j][k − 1], D[i][k][k − 1] + D[k][j][k − 1]) retourner D[][][n]
*/

#include <limits.h>
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
vector<vector<int>> floydwarshall(Graph& G) {
	int	D[G.get_size()][G.get_size()][G.get_size()];
	vector<vector<int>> 		distances;

	int	i;
	int	j;
	int	k;


	i = 1;
	while (i <= G.get_size())
	{
		j = 1;
		while (j <= G.get_size())
		{
			D[i][j][0] = INT_MAX; // maybe int max / 10
			D[i][i][0] = 0;
			j += 1;
		}
		printf("it\n");
		i += 1;
	}

	i = 0;
	while (i < G.get_size())
	{
		j = 0;
		while (j < G.get_size())
		{
			if (G.has_edge(i, j))
			{
				D[i][j][0] = G.get_weight(i, j);
			}
			j += 1;
		}
		i += 1;
	}

	k = 1;
	while (k <= G.get_size())
	{
		i = 1;
		while (i <= G.get_size())
		{
			j = 1;
			while (j <= G.get_size())
			{
				D[i][j][k] = 
		MIN(D[i][j][k - 1], D[i][k][k - 1] + D[k][j][k - 1]) ;
				j += 1;
			}
			i += 1;
		}
		k += 1;
	}

	return distances;
}


/*******************************/
/* Floyd-Warshall avec chemins */
/*******************************/

pair<vector<vector<int>>,vector<vector<int>>> floydwarshall2(Graph& G) {
	pair<vector<vector<int>>,vector<vector<int>>> res;
	return res;
}


/**************************************/
/* Génération des plus courts chemins */
/**************************************/

vector<int> get_path(vector<vector<int>> parent, int i, int j){
	vector<int> v;
	return v;
}

/********/
/* MAIN */
/********/

int main() {
	srand(time(NULL));
	/*
	   Graph g(4);
	   g.add_edge(0,1);
	   g.add_edge(0,2);
	   g.add_edge(0,3,3);
	   g.add_edge(1,2,6);
	   g.add_edge(1,3);
	   g.add_edge(2,3,-1);
	   g.print();
	   g.show();
	   */
	Graph g = random_clique(4);

	auto r = floydwarshall(g);


	g.print();
	g.show();

	return 0;
}
