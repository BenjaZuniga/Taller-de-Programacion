#include "Puzzle.h"
#include <ctime> 
#include <string>

using namespace std;

int main() {

	unsigned t0, t1;

    cout << "Nombre de archivo:";
    string filename;
    cin >> filename; // se lee el nombre del archivo

    t0=clock(); // se inicia el tiempo

	Puzzle *p = new Puzzle(filename); //se crea el puzzle segun el archivo de texto
	p->solve(); //se resuelve el puzzle

	t1 = clock(); //se finaliza el tiempo
 
    double time = (double(t1-t0)/CLOCKS_PER_SEC); //se calcula el tiempo
    cout << "Tiempo de ejecucion: " << time << endl; // se imprime el tiempo final

    
	return 0;
    
 }
