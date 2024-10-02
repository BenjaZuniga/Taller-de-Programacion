#include "Stack.h"

int main() {
    int size=2;
    int **board1;
    board1 = new int*[size];
    for(int i=0; i<size; i++) {
        board1[i] = new int[size];
        for(int j=0; j<size; j++) {
            board1[i][j] = i+j*2;
        }
    }
    Stack *s = new Stack();
    State *s1 = new State(size,nullptr,board1);
    s->add(s1);
    std::cout << s->contains(s1) << std::endl;
}

