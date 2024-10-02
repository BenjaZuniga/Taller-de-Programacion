#include "State.h"

int main() {
    int size=2;
    int **board;
    board = new int*[size];
    for(int i=0; i<size; i++) {
        board[i] = new int[size];
        for(int j=0; j<size; j++) {
            board[i][j] = i*2+j;
        }
    }
    int **board1;
    board1 = new int*[size];
    for(int i=0; i<size; i++) {
        board1[i] = new int[size];
        for(int j=0; j<size; j++) {
            board1[i][j] = i+j*2;
        }
    }
    State *s = new State(size, nullptr, board);
    State *s1 = new State(size, s, board1);
    s1->print();

    delete s;
    delete s1;

    return 0;
}