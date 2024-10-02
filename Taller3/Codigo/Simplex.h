#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#define EPS 1.0e-6

using namespace std;

/*
    Descripcion de la clase Simplex:
    Esta clase representa un solucionador de problemas de optimizacion
    lineal con variables reales [x1,....,xn]., mediante el metodo Simplex. 
    este busca maximizar una funcion con restricciones asociadas.
*/
class Simplex
{
private:
    int m; // Numero de restricciones
    int n; // Numero de variables
    bool isSolved;
    int icase;
    vector<int> izrov;
    vector<int> iposv;
    vector<float> solution;
	vector<float> greedySolution;

    vector<vector<float>> initialA; // Matriz del problema.
    vector<vector<float>> a; // Matriz en donde se genera la solucion.
    int m1; // numero de restricciones <=
    int m2; // ... >=
    int m3; // igualdad
    int simplx();
    void maxValue(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void locatePivot(int *ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);
    float fabs(float x);

public:

    // Constructores de la clase Simplex
    Simplex(std::string file_name);
    Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3);

    // Destructor de la clase Simplex
    ~Simplex();

    // Getters de la clase Simplex
	int getIcase();
    vector<float> getSolution();
	vector<float> getGreedySolution();

	// Setters de la clase Simplex
	void setSolution(vector<float> bestSolution);

    // Metodos de la clase Simplex
    vector<float> solve(); // el retorno es [Z, x1, x2, ..., xn]
    void insertConstraint(float b, int var, int type);
    Simplex copy();
    void printProblemMatrix();
    void printSolution();
    void greedySolve();
	vector<float> solveWithBranchandBound();
	vector<float> findMoreFractionaryVar(vector<float> solution);
	int getGreaterZIndex(vector<float> zs);
	bool equalsSolutions(vector<float> s1, vector<float> s2);
	int findPricelessSelectedVar(vector<float> solution);

};


