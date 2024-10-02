#include <iostream>
#include <string>
#include <ctime>
#include "Clique.h"

using namespace std;

int main() {

	int option = -1;

	while(option != 0){
		cout << "Seleccione una opción:" << endl;
		cout << "1)Encontrar el clique máximo de un grafo" << endl;
		cout << "2)Salir" << endl;
		cin >> option;

		if(option==1){
			
			unsigned t0, t1;
    		
    		cout << "Ingrese el nombre del archivo:" << endl;
    		string filename;
    		cin >> filename;

			t0 = clock();

    		Clique c(filename);

    		set<int> R;
    		set<int> P;
    		set<int> X;
	
    		int vertexMoreConected = c.findVertexMoreConected();
	

    		c.setVertexMoreConectedNeighbours(vertexMoreConected);
    		c.newTotalNeighbours(vertexMoreConected);

    		for(int i = 0; i < c.getSize(); i++) {
				int vertex = c.findVertexMoreConected();
        		P.insert(vertex);
        		c.setTotalNeighbours(vertex, -1);
    		}

    		c.BK(&R, &P, &X);

    		t1 = clock();
    		cout << "Tiempo de ejecución: " << (double(t1-t0)/CLOCKS_PER_SEC) << endl;

    		cout << "Tamaño del clique máximo: " << c.getMaxClique().size() << endl;
    		cout << "Clique máximo: ";
    		c.printMaxClique();
			cout << "---------------------------------------------" << endl;
		}else if(option ==2 ){
			cout << "Programa finalizado" << endl;
			return 0;

		}else{
			cout << "Opción no válida" << endl;
			cout << "---------------------------------------------" << endl;
		}
		option = -1;
	}
}