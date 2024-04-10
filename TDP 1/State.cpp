#include "State.h"

// Constructor de la clase State
State::State(int size, State *parent, int **board) {
    this->size = size;
    this->board = new int*[size];
    for(int i=0; i<size; i++) {
        this->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            //std::cout << "i=" << i << " j=" << j << " board[i][j]=" << board[i][j] << std::endl;
            this->board[i][j] = board[i][j];
			if (board[i][j] == 0) {
				this->i0 = i;
				this->j0 = j;
			}
        }
    }
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

bool State::equals(State *s) {
	if(this->size != 5){
		if(this->id1 != s->id1){
			return false;
		}
		return true;
	}else{
		if(this->id1 != s->id1 || this->id2 != s->id2){
			return false;
		}
		return true;
	}
}

void State::getId(){
	id1 = 0;
	id2 = 0;
	if(this->size <= 4){
		for(int i=0; i<this->size; i++) {
			for(int j=0; j<this->size; j++) {
				id1 = id1*10 + this->board[i][j];
			}
		}
	}else{
		for(int i=0; i<size; i++) {
			for(int j=0; j<this->size; j++) {
				if(i<3 ){
					id1 = id1*10 + this->board[i][j];
				}else{
					id2 = id2*10 + this->board[i][j];
				}
			}
		}
	}
}

// Print de un estado más los padres
void State::print() {
	int cont = 0;
    if (parent != nullptr) {
		parent->steps = this->steps + 1;
        parent->print();
    }
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
	std::cout << "\n----------------\n" <<std::endl;
}

// Print de un estado
void State::print_act() {
	for(int i=0; i<this->size; i++) {
		for(int j=0; j<this->size; j++) {
			std::cout << this->board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n----------------\n" <<std::endl;
}

// Calcula el peso del estado (cantidad de piezas en lugar incorrecto + ~pasos faltantes)
void State::setWeight(int **board){
	missingSteps = 0;
	for(int i=0; i<this->size; i++) {
		for(int j=0; j<this->size; j++) {
			if (board[i][j] != (i*size+j+1)%(size*size)) {
				int opt_i = getOptX(board[i][j]);
				int opt_j = getOptY(board[i][j]);
				this->fails++;
				missingSteps += abs(i-opt_i) + abs(j-opt_j);
				if(board[i][j] != 0){
					linearConflict2(opt_i, opt_j, i, j);
				}
			}	
		}
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
int State::linearConflict(){
	int cont = 0;
	for(int i=0; i<size; i++){
		int max = -1;
		for(int j=0; j<size; j++){
			int val = board[i][j];
			if(val != 0 && getOptX(val) == i){
				if(val > max){
					max = val;
				}else{
					cont++;
				}
			}
		}
	}
	for(int i=0; i<size; i++){
		int max = -1;
		for(int j=0; j<size; j++){
			int val = board[j][i];
			if(val != 0 && getOptY(val) == i){
				if(val > max){
					max = val;
				}else{
					cont++;
				}
			}
		}
	}
	return cont;
}

void State::linearConflict2(int opt_i, int opt_j, int i, int j){
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

bool State::isSol() {
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            if (this->board[i][j] != (i*this->size+j+1)%(size*size) ) {
                return false;
            }
        }
    }
    return true;
}

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

State * State::up() {
  if (i0!=0) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = new State(this->size, this, this->board);
    new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->board[i0][j0]=board[i0-1][j0];
    new_state->board[i0-1][j0]=0;
    new_state->i0--;
	new_state->steps = this->steps + 1;
	new_state->setWeight(new_state->board);
	new_state->getId();
    return new_state;
  }
  return(nullptr);
}

State * State::down() {
  if (i0!=size-1) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = new State(this->size, this, this->board);
    new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->board[i0][j0]=board[i0+1][j0];
    new_state->board[i0+1][j0]=0;
    new_state->i0++;
	new_state->steps = this->steps + 1;
	new_state->setWeight(new_state->board);
	new_state->getId();
    return new_state;
  }
  return(nullptr);
}

State * State::left() {
  if (j0!=0) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = new State(this->size, this, this->board);
    new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->board[i0][j0]=board[i0][j0-1];
    new_state->board[i0][j0-1]=0;
    new_state->j0--;
	new_state->steps = this->steps + 1;
	new_state->setWeight(new_state->board);
	new_state->getId();
    return new_state;
  }
  return(nullptr);
}

State * State::right() {
  if (j0!=size-1) { // si no esta en la primera fila entonces puedo subir el 0
    State *new_state = new State(this->size, this, this->board);
    new_state->board = new int*[size];
    for(int i=0; i<size; i++) {
        new_state->board[i] = new int[size];
        for(int j=0; j<size; j++) {
            new_state->board[i][j] = board[i][j];
        }
    }
    new_state->board[i0][j0]=board[i0][j0+1];
    new_state->board[i0][j0+1]=0;
    new_state->j0++;
	new_state->steps = this->steps + 1;
	new_state->setWeight(new_state->board);
	new_state->getId();
    return new_state;
  }
  return(nullptr);
}



State *State::get_sol(){
	board = new int*[size];
	int cont = 1;
    for(int i=0; i<size; i++) {
        board[i] = new int[size];
        for(int j=0; j<size; j++) {
			if(i == size-1 && j == size-1){
				board[i][j] = 0;
			}
            board[i][j] = cont;
			cont++;
		}
	}
	return new State(size, nullptr, board);
}
