#include "Puzzle.h"
#include <ctime> 

using namespace std;

int main() {

	unsigned t0, t1;

    cout << "Nombre de archivo:";
    char *filename;
    cin >> filename;

    t0=clock();

	Puzzle *p = new Puzzle(filename);
	p->solve();

	t1 = clock();
 
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion: " << time << endl;
	return 0;
    
 }
