#include "Heap.h"

//Constructor
Heap::Heap(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->arr =  new State *[capacity];
}
//Destructor
Heap::~Heap() {
    delete [] arr;
}

// Min heap  --> raiz es el menor
void Heap::push(State *data) {
    if (size == capacity) {
        State **arr_tmp = new State *[capacity*2];
        for(int i=0; i<capacity; i++) {
            arr_tmp[i] = arr[i];
        }
        delete [] arr;
        arr = arr_tmp;
        capacity *= 2;
    }
    arr[size] = data;
    size++;
    int i = size-1;
    while(i != 0 && arr[i]->weight < arr[(i-1)/2]->weight) { // min heap
        State *temp = arr[i]; // realizamos el  swap
        arr[i] = arr[(i-1)/2];
        arr[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

// Operación de extraer un elemento
State *Heap::pop() {
    if (size == 0) {
        return nullptr;
    }
    State *data = arr[0]; // retornamos la raiz
    arr[0] = arr[size-1]; // ponemos el ultimo elemento en la raiz
    size--; // disminuimos el tamaño
    int i = 0;
    while(2*i+1 < size) {
        int left = 2*i+1;
        int right = 2*i+2;
        int min = left;
        if (right < size && arr[right]->weight < arr[left]->weight) {
            min = right;
        }
        if (arr[i]->weight < arr[min]->weight) {
            break; // ya esta ordenado
        }
        State *temp = arr[i]; // si no cuple orden entonces hacemos el swap
        arr[i] = arr[min];
        arr[min] = temp;
        i = min;
    }
    return data;
}

//Verifica si el heap es vacio
bool Heap::isEmpty() {
	return size == 0;
}