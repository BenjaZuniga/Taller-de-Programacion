#include "StackNode.h"

int main() {
    int size=5;
    int **board;
    board = new int*[size];
    for(int i=0; i<size; i++) {
        board[i] = new int[size];
        for(int j=0; j<size; j++) {
            board[i][j] = i*2+j;
        }
    }
    State *s = new State(size,nullptr,board);
    s->getId();


    StackNode *sN = new StackNode(s);

    for(int i=0; i<3; i++) {
        std::cout << sN->ids[i] << std::endl;
    }
    delete sN;
    return 0;


}