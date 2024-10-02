#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;
/*
	* Clase Clique
	* Esta clase es utilizada para representar un grafo mediante una matriz de adyacencia
	* La clase está compuesta de una matriz de adyacencia, un tamaño, un vector de vecinos 
	* totales, un vector de vecinos del vertice con más conexiones y un conjunto de la clique máximo
*/
class Clique {
    private:
        vector<vector<int>> adyacency;
        int size;
        vector<int> totalNeighbours;
        vector<int> neighboursVertexMoreConected;
        set<int> maxClique;

    public:
	    // Constructor
        Clique(string filename);

        // Getters
        int getSize();
        set<int> getMaxClique();

        // Setters
        void setTotalNeighbours(int vertex, int totalNeighbours);

	    // Otros métodos
        void printMaxClique();
        void setVertexMoreConectedNeighbours(int vertex);
        int findVertexMoreConected();
        void newTotalNeighbours(int v);
        int getOptimalPivot(set<int> *P, set<int> *X); ;

        void BK(set<int> *R,set<int> *P, set<int> *X);
    

};