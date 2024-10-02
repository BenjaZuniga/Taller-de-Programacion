#include "Heap.h"

int main() {
    int size=3;
    int **board;
    board = new int*[size];
    for(int i=0; i<size; i++) {
        board[i] = new int[size];
        for(int j=0; j<size; j++) {
            board[i][j] = i*2+j;
        }
    }
    State *s = new State(size,nullptr, board);

    Heap *h = new Heap(2);
    for(int i=0; i<20; i++) {
        h->push(s);
    }

    for(int i=0; i<20; i++) {
        h->pop()->print_act();
    }
}