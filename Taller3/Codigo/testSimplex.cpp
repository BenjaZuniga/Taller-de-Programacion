#include <iostream>
#include "Simplex.h"

using namespace std;

int main() {
    Simplex s("testSimplex.txt");
    
    vector<float> sol = s.solveWithBranchandBound(); //
	cout << "Solucion encontrada: ";
    for(auto x : sol) {
        cout << x << " ";
    }
    cout << endl;
}