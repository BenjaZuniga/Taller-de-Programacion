#include "Clique.h"

/*
	* Constructor de la clase Clique
	* Descripción: Este constructor recibe un string con el nombre del archivo que contiene el grafo
	* El constructor se encarga de leer el archivo y llenar la matriz de adyacencia
	* Además, se llena el vector de vecinos totales
	* Parámetros: 
		- filename: El nombre del archivo que contiene el grafo
	* Retorno: void
*/
Clique::Clique(string filename) {
    ifstream file(filename);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> size;
    adyacency = vector<vector<int>>(size, vector<int>(size,0));
    totalNeighbours = vector<int>(size);
    int i = 0;

    while(getline(file, line)) {
        iss = istringstream(line);
        int j = 0;
        iss >> i >> j;
        adyacency[i][j] = 1;
        adyacency[j][i] = 1;
        iss.clear();
    }
    file.close();

    for(int i = 0; i < size; i++) {
        int contNeighbours = 0; // Contador de vecinos
        vector<int> neighs = vector<int>();
        for(int j = 0; j < size; j++) { // Se cuentan los vecinos de cada vértice del grafo
            if(adyacency[i][j] == 1) {
                contNeighbours++;
            }
        }
        totalNeighbours[i] = contNeighbours; // Se guarda el total de vecinos de un vértice n en la posición n del vector de vecinos totales
    }
}


/*
    * Método getSize
    * Descripción: Este método retorna el tamaño del grafo
    * Parámetros: 
        - void
    * Retorno: 
        - size: El tamaño del grafo
*/
int Clique::getSize() {
    return size;
}

/*
    * Método getMaxClique
    * Descripción: Este método retorna la clique máxima
    * Parámetros: 
        - void
    * Retorno: 
        - maxClique: La clique máxima
*/
set<int> Clique::getMaxClique() {
    return maxClique;
}

/*
    * Método setTotalNeighbours
    * Descripción: Este método recibe un vértice y la cantidad de vecinos que tiene
    * Parámetros: 
        - vertex: El vértice al que se le quiere actualizar los vecinos
        - totalNeighbours: La cantidad de vecinos que tiene el vértice
    * Retorno: 
        - void
*/
void Clique::setTotalNeighbours(int vertex, int totalNeighbours) {
    this->totalNeighbours[vertex] = totalNeighbours;
}
/*
	* Método printMaxClique
	* Descripción: Este método imprime el clique máximo
	* Parámetros: 
		- void
	* Retorno: 
		- void
*/
void Clique::printMaxClique() {
    for(auto i : maxClique) {
        cout << i << " ";
    }
    cout << endl;
}

/*
	* Método setPivotNeighbours
	* Descripción: Este método recibe un vértice y llena el vector de vecinos del vértice con más conexiones
	* Parámetros: 
		- pivot: El vértice al que se le quiere encontrar los vecinos
	* Retorno: 
		- void
*/
void Clique::setVertexMoreConectedNeighbours(int vertex) {
    vector<int> neighboursVertexMoreConected = vector<int>(totalNeighbours[vertex]);
    for(int i = 0; i < size; i++) {
        if(adyacency[vertex][i] == 1) {
            neighboursVertexMoreConected.push_back(i);
        }
    }
    this->neighboursVertexMoreConected = neighboursVertexMoreConected;
}

/*
	* Método findVertexMoreConected
	* Descripción: Este método encuentra el vértice con más conexiones
	* Parámetros: 
		- void
	* Retorno: 
		- vertexMoreConected: El vértice con más conexiones
*/
int Clique::findVertexMoreConected() {
    int vertexMoreConected = 0;
    int maxNeighbours = totalNeighbours[0];
    for(int i = 0; i < size; i++) {
        if(totalNeighbours[i] > maxNeighbours) {
            maxNeighbours = totalNeighbours[i];
            vertexMoreConected = i;
        }
    }
    return vertexMoreConected;
}

/*
	* Método newTotalNeighbours
	* Descripción: Este método actualiza el vector de vecinos totales
	* según cuantas conexiones tiene cada vecinos de un vértice con 
    * los vecinos del vértice con más conexiones
	* Parámetros: 
		- pivot: El vértice al que se le quiere actualizar los vecinos
	* Retorno: 
		- void
*/
void Clique::newTotalNeighbours(int vertex){
    for(int i = 0;i<neighboursVertexMoreConected.size();i++){
        int vertex2 = neighboursVertexMoreConected[i];
        int cont = 0;
        if(vertex2 == vertex){
            continue;
        }
        for(int j = 0;j<size;j++){
            if(this->adyacency[vertex][j] == 1){
                for(int k = 0;k<neighboursVertexMoreConected.size();k++){
                    if(neighboursVertexMoreConected[k] == j){
                        cont++;
                    }
                }
            }
        }
        cont*= 2;
        this->totalNeighbours[vertex]+= cont;       
    }
	this->totalNeighbours[vertex] = 99999;
}

/*
	* Método getOptimalPivot
	* Descripción: Este método recibe un conjunto de vértices P y X, 
	* los une y encuentra el vértice dentro de P unión X con más conexiones 
	* con el conjunto P intersectado con los vecinos del vértice
	* Parámetros: 
		- P: El conjunto de vértices posibles a formar un clique
		- X: El conjunto de vértices ya revisados
	* Retorno: 
		- pivot: El vértice con más conexiones con el conjunto P intersectado con los vecinos del vértice
*/
int Clique::getOptimalPivot(set<int> *P, set<int> *X) {
    int max = 0;
    int pivot = 0;
    set<int> *PuX = new set<int>(*P);
    set<int> *PintVu = new set<int>();
    for(auto i : *X) { // P unión X
        PuX->insert(i);
    }
    for(auto i : *PuX) { // Se revisa cada vértice en P unión X
        int cont = 0;
        for(int j = 0; j<size; j++) {
            if(adyacency[i][j] == 1) { // Si el vértice tiene un vecino que también está en el conjunto P se aumenta el contador
                cont++;
            }
        }
        if(cont > max) { // Si el contador es mayor al máximo actual se actualiza el máximo y se guarda el vértice
            max = cont;
            pivot = i;
        }
    }
    return pivot;
}

/*
	* Método BK
	* Descripción: Este método recibe un conjunto de vértices R, P y X
	* y encuentra el clique máximo del grafo
	* Parámetros: 
		- R: El conjunto de vértices que forman el clique actual
		- P: El conjunto de vértices posibles a formar un clique
		- X: El conjunto de vértices ya revisados
	* Retorno: 
		- void

*/
void Clique::BK(set<int> *R,set<int> *P, set<int> *X) {
    if(R->size() > maxClique.size()) {
        maxClique = *R; // Si el clique actual es mayor al clique máximo se actualiza el clique máximo
    }
    if (P->empty() && X->empty()) {
        return; // Si P y X están vacíos se termina la recursión
    }

    set<int> *P_new= new set<int>(*P); // Se copia P
    set<int> *X_new= new set<int>(*X); // Se copia X

    set<int> *P_iter = new set<int>(*P); // Se copia P para iterar
    int u = getOptimalPivot(P_iter, X_new); // Se obtiene el pivote óptimo

    for(auto v : *P_iter) {
        if(adyacency[u][v] == 1) {
            continue; // Si el vértice no es adyacente al pivote no es necesario revisarlo
        }

        set<int> *R1 = new set<int>(*R); // Se copia R
        R1->insert(v); // Se agrega el vértice al clique actual
        
        set<int> *P1 = new set<int>; // Se crea un nuevo conjunto P
        for(int i : *P_new) { 
            if(adyacency[v][i] == 1) {
                P1->insert(i); // Se llena el nuevo conjunto P con los vértices en P intersectados con los vecinos del vértice
            }
        }

        set<int> *X1 = new set<int>; // Se crea un nuevo conjunto X
        for(auto i : *X_new) {
            if(adyacency[v][i] == 1) {
                X1->insert(i); // Se llena el nuevo conjunto X con los vértices en X intersectados con los vecinos del vértice
            }
        }
        if(R1->size() + P1->size() > maxClique.size()) { // Si el clique actual más el nuevo conjunto P es mayor al clique máximo se llama a la recursión
            BK(R1, P1, X1);
        }

        P_new->erase(v); // Se elimina el vértice v de P
        X_new->insert(v);  // Se agrega el vértice v a X
        delete(P1); // Se libera la memoria de los conjuntos creados
        delete(R1); 
        delete(X1);

        
    }
    

}

