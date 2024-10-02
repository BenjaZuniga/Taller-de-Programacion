#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Simplex.h"

int main() {
	
	int option = -1;

	while(option != 0){
		cout << "Seleccione una opción:" << endl;
		cout << "1)Resolver problema de la mochila" << endl;
		cout << "2)Salir" << endl;
		cin >> option;

		if(option==1){
			
			unsigned t0, t1;
    		
    		cout << "Ingrese el nombre del archivo:" << endl;
    		string filename;
    		cin >> filename;

			t0 = clock();
			Simplex s(filename);
	
			//s.greedySolve();
			vector<float> sol = s.solveWithBranchandBound(); //
			
			if(sol[0]==0){
				//sol = s.getGreedySolution();
			}

			t1 = clock();
    		cout << "Tiempo de ejecución: " << (double(t1-t0)/CLOCKS_PER_SEC) << endl;

			cout << "Solucion encontrada: " ;
			for(auto x : sol) {
				cout << x << " ";
			}		
			cout << endl;
			}
		else if(option==2){
			return 0;
		}
	}
	return 0;
}