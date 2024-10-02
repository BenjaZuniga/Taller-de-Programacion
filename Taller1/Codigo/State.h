#include <iostream>
#pragma once

/// vamos a definir la clase State de manera abstracta
class State {
    public:
	    long id1; // Identificador del estado
		long id2; // Identificador del estado
		long id3; // Identificador del estado
        int **board; // Tablero size x size
        int size; // Número de filas y columnas
		int fails; // Cantidad de piezas en lugar incorrecto
		int missingSteps; // Aproximado de pasos faltantes
		int steps; // Pasos para llegar a este estado
		float weight; // Peso del estado

        // Al cargar el archivo busco donde esta el 0
        int i0; // Fila del cero
        int j0; // Columna del cero
        State *parent; // Puntero al padre del estado

        State(int size, State *parent, int **board); // Constructor
        ~State(); // Destructor
		void getId(); // Obtiene el identificador del estado
        bool equals(State *s); // Compara dos estados
        void print(); // Imprime el estado más los padres
		void print_act(); // Imprime el estado actual
		void setWeight(int **board); // Calcula el peso del estado (cantidad de piezas en lugar incorrecto + ~pasos faltantes)
		void linearConflict(int opt_i, int opt_j, int i, int j); // Calcula la cantidad de conflictos lineales
		int getOptX(int val); // Obtiene la fila de la pieza val en el estado solucion
		int getOptY(int val); // Obtiene la columna de la pieza val en el estado solucion
        bool isSol(); // Verifica si es solucion
		bool isSolvable(); // verifica si es solucionable
        State *up(); // Mueve el 0 hacia arriba
        State *down(); // Mueve el 0 hacia abajo
        State *left(); // Mueve el 0 hacia la izquierda
        State *right(); // Mueve el 0 hacia la derecha
		State *get_sol(); // Genera el estado solucion
        
		

};