#include "Puzzle.h"

/// Aqui se implementan los cuerpo de las funciones

// Dado el nombre de dominio Puzzle (classe) defino la funcion Puzzle
Puzzle::Puzzle(string filename){
	ifstream file(filename);

    if (!file.is_open()) { // Comprueba si se puede abrir un archivo
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

    file.close(); //Se cierra el archivo

    int **board;
    board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }
    file.open(filename); // Se vuelve a abrir el archivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> board[i][j]; // Se copia en el tablero el valor del archivo
        }
    } 
    file.close();

    act_stat = new State(n, nullptr, board); //Se crea el estado
	act_stat->steps = 0; //Se establece en 0 los pasos
	act_stat->setWeight(act_stat->board); //Se calcula el peso del estado
	act_stat->getId();// Se obtienen los ids del estado
	open = new Heap(100); // Se crea un heap con 100 espacios inicialmente
	closed= new Stack(); //Se crea el Stack

}

// Destructor de un Puzzle
Puzzle::~Puzzle(){
	delete act_stat;
	delete open;
	delete closed;
}

// Resuelve el puzzle
void Puzzle::solve() {
	if(act_stat->isSol()){
		cout << "La configuracion entregada no es solucionable" << endl;
		exit(0);
	}
	open->push(act_stat); // agrega en abiertos el tablero inicial
     // agrega en todos (ex cerrados )el tablero inicial 
    	while (!open->isEmpty()) { // mientras existan nodos por visitar
        	State *e = open->pop();
			//e->print_act();
			//cout << closed->size << endl;
			closed->add(e); // deberia obtener el mejor estado
        	if (e->isSol()) {
            	cout << "Encontramos la solucion\n" << endl;
				e->print(); //Se imprime la solución
				cout << "El numero de pasos es: " << e->steps << endl;
				break;
        	}
        	
        	State *e_up = e->up();  // si genera estado invalido, genera nullptr
        	if (e_up!=nullptr && !closed->contains(e_up)) { // si el estado no es invalido y no se ha revisado
            	open->push(e_up); //se guarda el movimiento hacia arriba
       		}        
    
        	State *e_down = e->down();  // si genera estado invalido, genera nullptr
         	if (e_down!=nullptr && !closed->contains(e_down)) { // si el estado no es invalido y no se ha revisado
           		open->push(e_down); //se guarda el movimiento hacia abajo
        	}

        	State *e_left = e->left();  // si genera estado invalido, genera nullptr
        	if (e_left!=nullptr && !closed->contains(e_left)) { // si el estado no es invalido y no se ha revisado
                open->push(e_left); //se guarda el movimiento hacia la izquierda
           }        

            State *e_right = e->right();  // si genera estado invalido, genera nullptr
            if (e_right!=nullptr && !closed->contains(e_right)) { // si el estado no es invalido y no se ha revisado
                open->push(e_right); //se guarda el movimiento hacia la derecha
            }
    }
    

}

