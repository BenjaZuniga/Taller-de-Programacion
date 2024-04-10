#include "Puzzle.h"

/// Aqui se implementan los cuerpo de las funciones

// Dado el nombre de dominio Puzzle (classe) defino la funcion Puzzle
Puzzle::Puzzle(string filename){
	ifstream file(filename);

    if (!file.is_open()) {
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(0);
    }

    string line;
    stringstream ss;
    int num, n=0;
    if(getline(file,line,'\n')){
        ss << line; // cargo el el obejto de flujo de datos mi linea 
        while(ss >> num) {
            n++;
        }
    }

    file.close();

    int **board;
    board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }
    file.open(filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> board[i][j];
        }
    } 
    file.close();

    act_stat = new State(n, nullptr, board);
	open = new List();
	closed = new List();

	

}
// utiliza el algoritmo A* para resolver el puzzle
void Puzzle::solve() {
	if(act_stat->isSol()){
		cout << "La configuracion entregada no es solucionable" << endl;
		exit(0);
	}
	act_stat->steps = 0;
	act_stat->setWeight(act_stat->board);
	act_stat->getId();
	open->add(act_stat); // agrega en abiertos el tablero inicial
     // agrega en todos (ex cerrados )el tablero inicial 
    	while (!open->isEmpty()) { // mientras existan nodos por visitar
        	State *e = open->pop()->data;
			//e->print_act();
			cout << closed->size << endl;
			closed->add(e); // deberia obtener el mejor estado
        	if (e->isSol()) {
            	cout << "Encontramos la solucion\n" << endl;
				e->print();
				cout << "El numero de pasos es: " << e->steps << endl;
				break;
				 // termina el programa (deberia liberar memoria)
        	}

        
        	// expandir el estado e --> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        	State *e_up = e->up();  // si genera estado invalido, genera nullptr
        	if (e_up!=nullptr && !closed->contains(e_up)) { // si no esta en todos
            	open->push(e_up);
       		}        
    
        	State *e_down = e->down();  // si genera estado invalido, genera nullptr
         	if (e_down!=nullptr && !closed->contains(e_down)) {
           		open->push(e_down);
        	}

        	State *e_left = e->left();  // si genera estado invalido, genera nullptr
        	if (e_left!=nullptr && !closed->contains(e_left)) {
                open->push(e_left);
           }        

            State *e_right = e->right();  // si genera estado invalido, genera nullptr
            if (e_right!=nullptr && !closed->contains(e_right)) {
                open->push(e_right);
            }
    }
    

}