#include "Clique.h"

int main() {

    Clique c("testClique.txt");

    set<int> R;
    set<int> P;
    set<int> X;

	int vertexMoreConected = c.findVertexMoreConected();

    c.setVertexMoreConectedNeighbours(vertexMoreConected);
    c.newTotalNeighbours(vertexMoreConected);

    for(int i = 0; i < c.size; i++) {
		int vertex = c.findVertexMoreConected();
        P.insert(vertex);
        c.totalNeighbours[vertex] = -1;
    }
    

    c.BK(&R, &P, &X);
	cout << "Tamaño del clique máximo: " << c.maxClique.size() << endl;
    cout << "Clique máximo: ";
	c.printMaxClique();
    
    return 0;
}