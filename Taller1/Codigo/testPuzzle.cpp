#include "Puzzle.h"

int main() {
    Puzzle *p = new Puzzle("testPuzzle.txt");

    p->solve();
    
    return 0;
}