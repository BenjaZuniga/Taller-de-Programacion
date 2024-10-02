#include "State.h"

// Constructor de la clase State
State::State(int size, State *parent, int **board) {
    this->size = size;
    this->board = new int*[size];
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            this->board[i][j] = board[i][j];
			if (board[i][j] == 0) {
				this->i0 = i;
				this->j0 = j;
			}
        }
    }
	this->id1 = 0;
	this->id2 = 0;
	this->id3 = 0;
	this->steps = 0;
    this->parent = parent;
}

// Destructor de la clase State
State::~State() {
    int size=0;
    for(int i=0; i<this->size; i++) {
        delete [] board[i];
    }
    delete [] board;
}

// Comprueba si dos estados son iguales
bool State::equals(State *s) {
	if(this->id1 != s->id1 || this->id2 != s->id2 || this->id3 != s->id3){
		return false;
	}
	return true;
}
//genera el id de un estado
void State::getId(){
	if(this->size < 4){
		for(int i=0; i<this->size; i++) {
			for(int j=0; j<this->size; j++) {
				id1 = id1*10 + this->board[i][j];
			}
		}
	}else if(this->size == 4){
		for(int i=0; i<size; i++) {
			for(int j=0; j<this->size; j++) {
				if(i<2){ //revisar
					id1 = id1*10 + this->board[i][j];
				}else{ //revisar
					id2 = id2*10 + this->board[i][j];
				}
			}
		}
	}else{
		int k = 1;
		for(int i=0; i<size; i++) {
			for(int j=0; j<this->size; j++) {
				if(k< 9){ //revisar
					id1 = id1*10 + this->board[i][j];
				}else if(k< 17){ //revisar
					id2 = id2*10 + this->board[i][j];
				}else{
					id3 = id3*10 + this->board[i][j];
				}
				k++;
			}
		}
	}
}

// Print de un estado más los padres
void State::print() {
	int cont = 0;
    if (parent != nullptr) {
        parent->print();
    }
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
	std::cout << "\n--------------\n" <<std::endl;
}

// Print de un estado
void State::print_act() {
	for(int i=0; i<this->size; i++) {
		for(int j=0; j<this->size; j++) {
			std::cout << this->board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n--------------\n" <<std::endl;;
}

// Calcula el peso del estado (cantidad de piezas en lugar incorrecto + ~pasos faltantes)
void State::setWeight(int **board){
	missingSteps = 0;
	fails = 0;
	for(int i=0; i<this->size; i++) {
		for(int j=0; j<this->size; j++) {
			if (board[i][j] != (i*size+j+1)%(size*size)) {
				int opt_i = getOptX(board[i][j]);
				int opt_j = getOptY(board[i][j]);
				this->fails++;
				missingSteps += abs(i-opt_i) + abs(j-opt_j); //Calcula la distancia de manhattan
				if(board[i][j] != 0){
					linearConflict(opt_i, opt_j, i, j); //Si el valor de la posicion no es 0 se calculan los conflictos lineales
				}
			}	
		}
	}
	if(size == 5){
		this->weight = steps*1.5 + fails*0.4 + missingSteps*1.5;
	}else if(size == 4){
		this->weight = steps*1.1 + fails*0.4 + missingSteps*1.2;
	}else if (size <= 3){
		this->weight = steps     + fails     + missingSteps ;
	}
}

// Obtiene la fila de la pieza val en el estado solucion
int State::getOptX(int val){
	if(val == 0){
		return size-1;
	}else if(val%size == 0){
		return (val/size)-1;
	}
	return (val)/size;
}

// Obtiene la columna de la pieza val en el estado solucion
int State::getOptY(int val){
	if(val == 0){
		return size-1;
	}else if(val%size == 0){
		return size-1;
	}
	return (val%size)-1;
}

// Calcula la cantidad de conflictos lineales
void State::linearConflict(int opt_i, int opt_j, int i, int j){
	if(opt_i<i){
		for(int k=0; k<i; k++){
			int opt_i2 = getOptX(board[k][j]);
			if(opt_i < opt_i2 ){
				missingSteps+=2;
			}
		}
	}
	if(opt_i>i){
		for(int k=i+1; k<size; k++){
			int opt_i2 = getOptX(board[k][j]);
			if(opt_i >= opt_i2){
				missingSteps+=2;
			}
		}
	}
	if(opt_j<j){
		for(int k=0; k<j; k++){
			int opt_j2 = getOptY(board[i][k]);
			if(opt_j <= opt_j2){
				missingSteps+=2;
			}
		}
	}
	if(opt_j>j){
		for(int k=j+1; k<size; k++){
			int opt_j3 = getOptY(board[i][k]);
			if(opt_j >= opt_j3){
				missingSteps+=2;
			}
		}
	}
}

// Comprueba si el estado es la solucion
bool State::isSol() {
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            if (this->board[i][j] != (i*this->size+j+1)%(size*size) ) {
                return false; // si alguna pieza no esta en su lugar retorna falso
            }
        }
    }
    return true; // si todas las piezas estan en su lugar retorna verdadero
}

// Comprueba si el estado es solucionable
bool State::isSolvable() {
	int inv = 0;
	int arr[(size*size)-1];
	int k = 0;
	for(int i=0; i<this->size; i++) {
		for(int j=0; j<this->size; j++) {
			if(this->board[i][j] != 0){
				arr[k] = this->board[i][j];
				k++;
			}
		}
	}
	for(int i=0; i<(size*size)-1; i++) {
		for(int j=i+1; j<(size*size)-1; j++) {
			if (arr[i] > arr[j]) {
				inv++;
			}
		}
	}
	
	if((inv - size)%2==0){
		return false;
	}else{
		return true;
	
	};
	
}

// Genera un movimiento del 0 hacia arriba
State * State::up() {
  if (i0!=0) { // si no esta en la primera fila entonces puedo subir el 0 sino se retorna nullptr
    State *new_state = new State(this->size, this, this->board); // se crea un nuevo estado igual al padre
    new_state->board = new int*[size]; // se crea un nuevo tablero
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size]; // se crea una nueva fila
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j]; // se copia el tablero del padre
        }
    }
    new_state->board[i0][j0]=board[i0-1][j0]; // se mueve el numero arriba del 0 hacia abajo
    new_state->board[i0-1][j0]=0; // se mueve el 0 arriba
    new_state->i0--; // se actualiza la posicion del 0
	new_state->steps = this->steps + 1; // se actualiza la cantidad de pasos
	new_state->setWeight(new_state->board); // se calcula el peso del nuevo estado
	new_state->getId(); // se genera el id del nuevo estado
    return new_state; // se retorna el nuevo estado
  }
  return(nullptr);
}

// Genera un movimiento del 0 hacia abajo
State * State::down() {
  if (i0!=size-1) { // si no esta en la ultima fila entonces puedo bajar el 0 sino se retorna nullptr
    State *new_state = new State(this->size, this, this->board); // se crea un nuevo estado igual al padre
    new_state->board = new int*[size]; // se crea un nuevo tablero
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size]; // se crea una nueva fila
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j]; // se copia el tablero del padre
        }
    }
    new_state->board[i0][j0]=board[i0+1][j0]; // se mueve el numero abajo del 0 hacia arriba
    new_state->board[i0+1][j0]=0; // se mueve el 0 abajo
    new_state->i0++; // se actualiza la posicion del 0
	new_state->steps = this->steps + 1; // se actualiza la cantidad de pasos
	new_state->setWeight(new_state->board); // se calcula el peso del nuevo estado
	new_state->getId(); // se genera el id del nuevo estado
    return new_state; // se retorna el nuevo estado
  }
  return(nullptr);
}

// Genera un movimiento del 0 hacia la izquierda
State * State::left() {
  if (j0!=0) { // si no esta en la primera columna entonces puedo mover a la izquirda el 0 sino se retorna nullptr
    State *new_state = new State(this->size, this, this->board); // se crea un nuevo estado igual al padre
    new_state->board = new int*[size]; // se crea un nuevo tablero
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size]; // se crea una nueva fila
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j]; // se copia el tablero del padre
        }
    }
    new_state->board[i0][j0]=board[i0][j0-1]; // se mueve el numero a la izquierda del 0 hacia la derecha
    new_state->board[i0][j0-1]=0; // se mueve el 0 a la izquierda
    new_state->j0--; // se actualiza la posicion del 0
	new_state->steps = this->steps + 1; // se actualiza la cantidad de pasos
	new_state->setWeight(new_state->board); // se calcula el peso del nuevo estado
	new_state->getId(); // se genera el id del nuevo estado
    return new_state; // se retorna el nuevo estado
  }
  return(nullptr);
}

// Genera un movimiento del 0 hacia la derecha
State * State::right() {
  if (j0!=size-1) { // si no esta en la ultima columa entonces puedo mover a la derecha el 0 sino se retorna nullptr
    State *new_state = new State(this->size, this, this->board); // se crea un nuevo estado igual al padre
    new_state->board = new int*[size]; // se crea un nuevo tablero
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size]; // se crea una nueva fila
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j]; // se copia el tablero del padre
        }
    }
    new_state->board[i0][j0]=board[i0][j0+1]; // se mueve el numero a la derecha del 0 hacia la izquierda
    new_state->board[i0][j0+1]=0; // se mueve el 0 a la derecha
    new_state->j0++; // se actualiza la posicion del 0
	new_state->steps = this->steps + 1; // se actualiza la cantidad de pasos
	new_state->setWeight(new_state->board); // se calcula el peso del nuevo estado
	new_state->getId(); // se genera el id del nuevo estado
    return new_state; // se retorna el nuevo estado
  }
  return(nullptr);
}
