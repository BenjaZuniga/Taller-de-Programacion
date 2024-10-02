#include "Simplex.h"

using namespace std;

/*
    Metodo: Constructor
    Descripcion: este metodo permite iniciar un Simplex, recibiendo
        el nombre de un archivo, el cual contendra los datos necesarios
        para la creacion de el Simplex.
    Parametros:
        -filename: nombre del archivo que contendra los datos.
    Retorno: El objeto creado.
*/
Simplex::Simplex(string fileName)
{
    string line;
    fstream txtStream(fileName);
    stringstream charStream;
    string stringNumber;

    if (!txtStream.is_open())
    {
        throw invalid_argument("El archivo ingresado no existe.");
    }

    getline(txtStream, line);
    charStream << line;
    getline(charStream, stringNumber, ' ');
    this->m1 = stoi(stringNumber);
    getline(charStream, stringNumber, ' ');
    this->m2 = stoi(stringNumber);
    getline(charStream, stringNumber, ' ');
    this->m3 = stoi(stringNumber);

    while (getline(txtStream, line))
    {
        charStream.clear();
        charStream << line;
        vector<float> function;
        while (getline(charStream, stringNumber, ' '))
        {
            function.push_back(stof(stringNumber));
        }
        this->a.push_back(function);
    }
    this->n = a[0].size() - 1;
    this->m = m1 + m2 + m3;
    if (m != (int)a.size() - 1)
    {
        throw invalid_argument("El numero de restricciones ingresados no coincide con la matriz dada.");
    }

    for (int i = 1; i <= m; i++)
    {
        if (a[i][0] < 0.0 || (int)a[i].size() != n + 1)
        {
            // Error al crear el Simplex, ya que no se permiten
            // constantes negativas para las restricciones, o el
            // numero de columnas no coincide para todas las filas.
            throw invalid_argument("La matriz ingresada no es valida.");
        }
    }

    vector<float> function;
    for (int i = 0; i <= n; i++)
    {
        function.push_back(0.0);
    }

    this->a.push_back(function);
    this->initialA = a;
    this->isSolved = false;
    txtStream.close();
	this->greedySolution = vector<float>(n,0.0);
}

/*
    Metodo: Constructor
    Descripcion: este metodo permite iniciar un Simplex, recibiendo
        los datos necesarios para la creacion de este.
    Parametros:
        -a: Matriz con los valores que acompanian a la funcion a maximizar
            y a las restricciones del problema a resolver.
        -m1: numero de restricciones de tipo 1 (<=)
        -m2: numero de restricciones de tipo 2 (>=)
        -m3: numero de restricciones de tipo 3 (==)
    Retorno: El objeto creado.
*/
Simplex::Simplex(vector<vector<float>> a, int m1, int m2, int m3)
{
    int m = m1 + m2 + m3;
    for (int i = 1; i <= m; i++)
    {
        if (a[i][0] < 0.0)
        {
            // Error al crear el Simplex, ya que no se permiten
            // constantes negativas para las restricciones.
            throw invalid_argument("La matriz ingresada no es valida.");
        }
    }

    this->initialA = a;
    this->a = a;
    this->m1 = m1;
    this->m2 = m2;
    this->m3 = m3;
    this->m = m;
    this->n = a[0].size() - 1;
    this->isSolved = false;
	
}

/*
    Descripcion: este metodo permite eliminar el objeto.
    Parametros: no posee.
    Retorno: no posee.
*/
Simplex::~Simplex()
{
}

/*
    Descripcion: este metodo permite resolver el problema de programacion
        lineal invocando al metodo de simplex.
    Parametros: No posee.
    Retorno: 
       -Si encuntra solucion: Arreglo con el valor maximizado y los 
        valores de los parametros de la funcion a maximizar.
       -Si NO encuntra solucion: Arreglo vacio.

*/
vector<float> Simplex::solve()
{
    icase = simplx();
    isSolved = true;
    if (icase != 0)
    {
        vector<float> emptyVector;
        return emptyVector; // No hay solucion
    }



    vector<float> parameters(n + 1, 0.0);
    parameters[0] = a[0][0];
    for (int i = 0; i < m; i++)
    {
        if (iposv[i] < n)
        {
            parameters[iposv[i] + 1] = a[i + 1][0];
        }
    }
    solution = parameters;

    return parameters;
}

/*
	Descripcion: este metodo permite obtener el valor de icase.
	Parametros: No posee.
	Retorno: Valor de icase.
*/
int Simplex::getIcase(){
	return icase;
}
/*
    Descripcion: este metodo permite obtener la mejor solucion
        encontrada por el metodo de Branch and Bound.
    Parametros: No posee.
    Retorno: Arreglo con el valor maximizado y los 
        valores de los parametros de la funcion a maximizar.
*/
vector<float> Simplex::getSolution(){
    return solution;
}

/*
	Descripcion: este metodo permite obtener la solucion
		encontrada por el metodo greedy.
	Parametros: No posee.
	Retorno: Arreglo con el valor maximizado y los 
		valores de los parametros de la funcion a maximizar.
*/
vector<float> Simplex::getGreedySolution(){
	return greedySolution;
}

/*
    Descripcion: este metodo resuelve el problema de maximizacion
        dado la funcion y las restricciones dadas en la creacion
        del objeto, todo mediante el metodo simplex.
    Parametros: No posee.
    Retorno:
        - 0: Fue posible resolver el problema.
        - 1: No existe un limite para la funcion a maximizar.
        - -1: No existe solucion que cumpla con las restricciones dadas.
*/
int Simplex::simplx()
{
    int i, ip, is, k, kh, kp, nl1;
    float q1, bmax;
    vector<int> l1;
    vector<int> l3;
    nl1 = n;
    izrov.clear();
    iposv.clear();
    for (k = 0; k < n; k++)
    {
        l1.push_back(k);
        izrov.push_back(k);
    }
    for (i = 0; i < m; i++)
    {
        iposv.push_back(n + i);
    }

    if (m2 + m3)
    {
        for (i = 0; i < m2; i++)
        {
            l3.push_back(1);
        }
        for (k = 0; k < n + 1; k++)
        {
            q1 = 0.0;
            for (i = m1; i < m; i++)
            {
                q1 += a[i + 1][k];
            }
            a[m + 1][k] = -q1;
        }
        for (;;)
        {
            maxValue(m + 1, l1, nl1, 0, &kp, &bmax);
            if (bmax <= EPS && a[m + 1][0] < -EPS)
            {
                return -1; // icase -1
            }
            else if (bmax <= EPS && a[m + 1][0] <= EPS)
            {
                for (ip = m1 + m2; ip < m; ip++)
                {
                    if (iposv[ip] == ip + n)
                    {
                        maxValue(ip, l1, nl1, 1, &kp, &bmax);
                        if (bmax > EPS)
                        {
                            goto one;
                        }
                    }
                }
                for (i = m1; i < m1 + m2; i++)
                {
                    if (l3[i - m1] == 1)
                    {
                        for (k = 0; k < n + 1; k++)
                        {
                            a[i + 1][k] = -a[i + 1][k];
                        }
                    }
                }
                break;
            }
            locatePivot(&ip, kp);
            if (ip == -1)
            {
                return -1; // icase -1
            }
        one:
            exchangeParameters(m + 1, n, ip, kp);
            if (iposv[ip] >= (n + m1 + m2))
            {
                for (k = 0; k < nl1; k++)
                {
                    if (l1[k] == kp)
                    {
                        break;
                    }
                }
                --nl1;
                for (is = k; is < nl1; is++)
                {
                    l1[is] = l1[is + 1];
                }
            }
            else
            {
                kh = iposv[ip] - m1 - n;
                if (kh >= 0 && l3[kh])
                {
                    l3[kh] = 0;
                    ++a[m + 1][kp + 1];
                    for (i = 0; i < m + 2; i++)
                    {
                        a[i][kp + 1] = -a[i][kp + 1];
                    }
                }
            }
            is = izrov[kp];
            izrov[kp] = iposv[ip];
            iposv[ip] = is;
        }
    }

    for (;;)
    {
        maxValue(0, l1, nl1, 0, &kp, &bmax);
        if (bmax <= EPS)
        {
            return 0; // icase = 0
        }
        locatePivot(&ip, kp);
        if (ip == -1)
        {
            return 1; // icase  = 1
        }
        exchangeParameters(m, n, ip, kp);
        is = izrov[kp];
        izrov[kp] = iposv[ip];
        iposv[ip] = is;
    }
}

/*
    Descripcion: este metodo calcula el valor mayor de los elementos
        de la fila mm, cuyo indice esta en el vector ll dado (corrido en 1 posicion
        ya que el primer elemento corresponde a una constante y los valores se
        estan guardando en base a los parametros x1, x2 ...), guardando el valor
        en bmax y el indice en kp, esto considerando el valor absoluto del valor
        si se entrega iabf distinto de 0, en otro caso se toma el valor tal cual.
    Parametros:
        -mm: fila a revisar de la matriz.
        -ll: vector con las posciones de la columna a revisar en la matriz.
        -nll: largo del vector ll
        -iabf: valor que indica si se desea calcular con el valor absoluto o no.
        -kp: direccion donde se guardara la posicion del elemento con mayor valor.
        -bmax: direccion donde se guardara el valor maximo encontrado.
    Retorno: No posee.
*/
void Simplex::maxValue(int mm, vector<int> ll, int nll, int iabf, int *kp, float *bmax)
{
    int k;
    float test;

    if (nll <= 0)
    {
        *bmax = 0.0;
    }
    else
    {
        *kp = ll[0];
        *bmax = a[mm][*kp + 1];
        for (k = 1; k < nll; k++)
        {
            if (iabf == 0)
            {
                test = a[mm][ll[k] + 1] - (*bmax);
            }
            else
            {
                test = fabs(a[mm][ll[k] + 1]) - fabs(*bmax);
            }

            if (test > 0.0)
            {
                *bmax = a[mm][ll[k] + 1];
                *kp = ll[k];
            }
        }
    }
}

/*
    Descripcion: este metodo encuentra la fila en donde se
        encuentra el elemento que sirve como pivote.
    Parametros:
        -ip: direccion donde se guardara la fila del elemento pivote.
        -kp: numero de la columna en donde encontrar el pivote.
    Retorno: No posee.
*/
void Simplex::locatePivot(int *ip, int kp)
{

    int k, i;
    float qp, q0, q, q1;

    kp = kp + 1;
    *ip = -1;
    for (i = 0; i < m; i++)
    {
        if (a[i + 1][kp] < -EPS)
        {
            break;
        }
    }

    if (i + 1 > m)
    {
        return;
    }

    q1 = -a[i + 1][0] / a[i + 1][kp];
    *ip = i;
    for (i = *ip + 1; i < m; i++)
    {
        if (a[i + 1][kp] < -EPS)
        {
            q = -a[i + 1][0] / a[i + 1][kp];
            if (q < q1)
            {
                *ip = i;
                q1 = q;
            }
            else if (q == q1)
            {
                qp = -1;
                q0 = -1;
                for (k = 0; k < n; k++)
                {
                    qp = -a[*ip + 1][k + 1] / a[*ip + 1][kp];
                    q0 = -a[i + 1][k + 1] / a[i + 1][kp];
                    if (q0 != qp)
                    {
                        break;
                    }
                }
                if (q0 < qp)
                {
                    *ip = i;
                }
            }
        }
    }
}

/*
    Descripcion: este metodo realiza operaciones matriciales, para
        intercambiar un parametro perteneciente a la restricciones m3
        con los parametros restantes.
    Parametros:
        -i1: numero de filas a explorar.
        -k1: numero de columnas a explorar.
        -ip: numero de la fila del pivote.
        -kp: numero de la columna del pivote.
    Retorno: No posee.
*/
void Simplex::exchangeParameters(int i1, int k1, int ip, int kp)
{
    int kk, ii;
    float piv;

    piv = 1.0 / a[ip + 1][kp + 1];
    for (ii = 0; ii < i1 + 1; ii++)
    {
        if (ii - 1 != ip)
        {
            a[ii][kp + 1] *= piv;
            for (kk = 0; kk < k1 + 1; kk++)
            {
                if (kk - 1 != kp)
                {
                    a[ii][kk] -= a[ip + 1][kk] * a[ii][kp + 1];
                }
            }
        }
    }

    for (kk = 0; kk < k1 + 1; kk++)
    {
        if (kk - 1 != kp)
        {
            a[ip + 1][kk] *= -piv;
        }
    }

    a[ip + 1][kp + 1] = piv;
}

/*
    Descripcion: este metodo calcula el valor absoluto de un
        valor dado.
    Parametros:
        -x: valor a calcular el valor absoluto
    Retorno: valor absoluto de x.
*/
float Simplex::fabs(float x)
{
    if (x < 0.0)
    {
        return x * -1.0;
    }

    return x;
}

/*
    Descripcion: este metodo permite insertar una restriccion
        a la matriz que representa el problema.
    Parametros:
        -b: valor constante de la restriccion.
        -var: variable/parametro a la que se agrega la restriccion
        -type: tipo de la restriccion, este puede ser:
            .1: var <= b
            .2: var >= b
            .3: var == b
    Retorno: No posee.
*/
void Simplex::insertConstraint(float b, int var, int type)
{
    if (var == 0 || var > n || b < 0.0)
    {
        return;
    }

    vector<float> constraint(n + 1, 0.0);
    constraint[0] = b;
    constraint[var] = -1.0;

    switch (type)
    {
    case 1: // var <= b
        this->initialA.insert(this->initialA.begin() + m1 + 1, constraint);
        m1++;
        break;
    case 2: // var >= b
        this->initialA.insert(this->initialA.begin() + m1 + m2 + 1, constraint);
        m2++;
        break;
    case 3: // var == b
        this->initialA.insert(this->initialA.begin() + m + 1, constraint);
        m3++;
        break;
    default:
        return;
        break;
    }
    m++;
    isSolved = false;
    a = initialA;
    solution.clear();
}


/*
    Descripcion: este metodo permite copiar el objeto con sus
        respectivos valores.
    Parametros: No tiene.
    Retorno: El objeto creado con los valores
        del objeto copiado.
*/
Simplex Simplex::copy()
{
    Simplex s = Simplex(initialA, m1, m2, m3);
	s.m = m1 + m2 + m3;
	s.n = n;
	s.initialA = this->initialA;
    s.izrov = this->izrov;
    s.iposv = this->iposv;
    s.isSolved = this->isSolved;
    s.icase = this->icase;
    s.a = this->a;
	s.greedySolution = this->greedySolution;
    s.solution = this->solution;
    return s;
}


/*
    Descripcion: este metodo permite imprimir la matriz
        que representa al problema.
    Parametros: No tiene.
    Retorno: No tiene.
*/
void Simplex::printProblemMatrix()
{
    for (size_t i = 0; i < initialA.size(); i++)
    {
        for (size_t j = 0; j < initialA[0].size(); j++)
        {
            string aij = to_string(initialA[i][j]);
            aij = aij.substr(0, aij.find(".") + 3);
            aij.insert(aij.begin(), 10 - aij.length(), ' ');
            cout << aij;
        }
        cout << endl;
    }
}

/*
    Descripcion: este metodo permite imprimir la matriz solucion,
        esto si es que fue resuelto en problema.
    Parametros: No tiene.
    Retorno: No tiene.
*/
void Simplex::printSolution()
{
    if (isSolved)
    {
        int nm1m2;
        if (icase == 1)
        {
            cout << "No existe limite para la funcion a maximizar." << endl;
        }
        else if (icase == -1)
        {
            cout << "No hay solucion que cumpla con las restricciones." << endl;
        }
        else
        {
            nm1m2 = n + m1 + m2;
            string txt[nm1m2];
            for (int i = 0; i < n; i++)
            {
                txt[i] = "x" + to_string(i + 1);
            }
            for (int i = n; i < nm1m2; i++)
            {
                txt[i] = "y" + to_string(i + 1 - n);
            }

            cout << string(11, ' ');
            for (int i = 0; i < n; i++)
            {
                if (izrov[i] < nm1m2)
                {
                    txt[izrov[i]].insert(txt[izrov[i]].begin(), 10 - txt[izrov[i]].length(), ' ');
                    cout << txt[izrov[i]];
                }
            }

            cout << endl;
            for (int i = 0; i < m + 1; i++)
            {
                if (i == 0 || iposv[i - 1] < nm1m2)
                {
                    if (i > 0)
                    {
                        cout << txt[iposv[i - 1]];
                    }
                    else
                    {
                        cout << "  ";
                    }

                    string ai0 = to_string(a[i][0]);
                    ai0 = ai0.substr(0, ai0.find(".") + 3);
                    ai0.insert(ai0.begin(), 10 - ai0.length(), ' ');
                    cout << ai0;
                    for (int j = 1; j < n + 1; j++)
                    {
                        if (izrov[j - 1] < nm1m2)
                        {
                            string aij = to_string(a[i][j]);
                            aij = aij.substr(0, aij.find(".") + 3);
                            aij.insert(aij.begin(), 10 - aij.length(), ' ');
                            cout << aij;
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
    else
    {
        cout << "No esta resuelto." << endl;
    }
}


/*
	Descripcion: este metodo permite resolver el problema de programacion
		lineal metiante metodo de branch and bound.
	Parametros: No posee.
	Retorno: 
	   -Si encuntra solucion: Arreglo con el valor maximizado y los 
		valores de los parametros de la funcion a maximizar.
	   -Si NO encuntra solucion: Arreglo vacio.

*/

vector<float> Simplex::solveWithBranchandBound() {

    Simplex simplex = this->copy();
    vector<Simplex> simplexLive;
    vector<float> solution = simplex.solve();
    simplex.setSolution(solution);
    simplexLive.push_back(simplex);

	solution = vector<float>(n+1,0.0);

    vector<float> zsSups; // Vector para almacenar las cotas superiores de los problemas restantes
    zsSups.push_back(solution[0]);

    set<vector<float>> evaluatedSolutions;  // Conjunto para almacenar soluciones parciales evaluadas

    while (!simplexLive.empty()) {

        int bestIndex = getGreaterZIndex(zsSups); // Obtener el indice del problema con mayor cota superior
        Simplex simplexAct = simplexLive[bestIndex]; // Obtener el problema con mayor cota superior
        simplexLive.erase(simplexLive.begin() + bestIndex); // Eliminar el problema seleccionado
        zsSups.erase(zsSups.begin() + bestIndex); // Eliminar la cota superior del problema seleccionado


        vector<float> solutionVector = simplexAct.getSolution(); // Obtener la solucion del problema seleccionado

		if (solutionVector.empty() || simplexAct.getIcase() != 0) {
            continue;
        }

		if(solutionVector[0] > solution[0]){
			solution = solutionVector; // Actualizar la mejor solucion encontrada
		} 

		int check = 0;
		
        // Verificar si esta configuración de valores enteros ya ha sido evaluada
        for(auto sol : evaluatedSolutions) {
			if(equalsSolutions(sol, solutionVector)){
				check = 1;
				break;
			}
		}

		if (check == 1) {
			continue;
		}

        // Agregar la configuración actual al conjunto de soluciones evaluadas
        evaluatedSolutions.insert(solutionVector);

        float solutionSup = solutionVector[0];
        float solutionInf = 0.0;
        for (int i = 1; i < solutionVector.size(); i++) {
            solutionInf += (int)solutionVector[i] * simplexAct.initialA[0][i]; // Calcular la cota inferior de la solucion
        }

		

        if (solutionSup == solutionInf) { // Si la cota superior es igual a la cota inferior, no se puede mejorar
            return solutionVector;
        }

        vector<float> varAndIndex = findMoreFractionaryVar(solutionVector); // Encontrar la variable con mayor parte fraccionaria
        int index = varAndIndex[1];
        float var = varAndIndex[0];

		// Crear dos problemas nuevos con las restricciones de la variable con mayor parte fraccionaria
        Simplex simplex1 = simplex.copy(); 
        Simplex simplex2 = simplex.copy();
        simplex1.insertConstraint((int)var + 1, index, 2); 
        simplex2.insertConstraint((int)var, index, 1);

		// Resolver los problemas creados
        vector<float> solution1 = simplex1.solve();
        vector<float> solution2 = simplex2.solve();

        if (solution1[0] >= solutionInf ) { // Si la cota superior de la solucion 1 es mayor o igual a la cota inferior
            simplex1.setSolution(solution1); // Guardar la solucion
            simplexLive.push_back(simplex1); // Agregar el problema a los problemas restantes
            zsSups.push_back(solution1[0]); // Agregar la cota superior al vector de cotas superiores
        }
        if (solution2[0] >= solutionInf) { // Si la cota superior de la solucion 2 es mayor o igual a la cota inferior
            simplex2.setSolution(solution2); // Guardar la solucion
            simplexLive.push_back(simplex2); // Agregar el problema a los problemas restantes
            zsSups.push_back(solution2[0]); // Agregar la cota superior al vector de cotas superiores
        }
    }

	//Si no se encontro solucion optima

	float solutionAux = 0.0;

	float capacity = initialA[1][0];
	float actualCapacity = 0.0;


	// Se relaja la solucion encontrada para obtener una solucion factible
    for (int i = 1; i < solution.size(); i++) {
        solutionAux += (int)solution[i] * initialA[0][i];
		solution[i] = (int)solution[i];
		actualCapacity += initialA[1][i] * -solution[i];
    }

	// Se agrega un item que quepa en la mochila a la solucion
	for(int i = 1; i < solution.size(); i++){
		if(actualCapacity - initialA[1][i] < capacity && solution[i] == 0){
			solution[i] = solution[i] + 1;
			solutionAux += initialA[0][i];
			break;
		}
	}

	solution[0] = solutionAux;
	return solution;
}

/*
	Descripcion: este metodo permite encontrar la variable con mayor parte fraccionaria de la solucion.
	Parametros: 
		-solution: solucion a evaluar.
	Retorno: 
		-Arreglo con la variable con mayor parte fraccionaria y su indice.
*/
vector<float> Simplex::findMoreFractionaryVar(vector<float> solution){
	vector<float> varAndIndex(2);
	float lesserFractionaryPart = 1.0;
	for(int i = 1; i < solution.size(); i++){
		float fractionaryPart = solution[i] - (int)solution[i];
		fractionaryPart = fractionaryPart - 0.5;
		if(fractionaryPart < 0){
			fractionaryPart = fractionaryPart * -1;
		}
		if(fractionaryPart < lesserFractionaryPart){
			varAndIndex[0] = solution[i];
			varAndIndex[1] = i;
			lesserFractionaryPart = fractionaryPart;
		}
	}
	return varAndIndex;
}

/*
	Descripcion: este metodo permite obtener el indice de la mayor cota superior de los problemas restantes.
	Parametros: 
		-zs: cotas de los problemas restantes a evaluar.
	Retorno: 
		-Indice del mayor valor del vector.
*/
int Simplex::getGreaterZIndex(vector<float> zs){
	float greaterZ = zs[0];
	int index = 0;
	for(int i = 1; i < zs.size(); i++){
		if(zs[i] > greaterZ){
			index = i;
		}
	}
	return index;
}

/*
	Descripcion: este metodo permite establecer la solucion del problema.
	Parametros: 
		-solution: solucion a establecer.
	Retorno: No posee.
*/
void Simplex::setSolution(vector<float> solution){
	this->solution = solution;
}

/*
	Descripcion: este metodo permite resolver el problema de programacion
		lineal mediante un metodo greedy.
	Parametros: No posee.
	Retorno: No posee.
*/
void Simplex::greedySolve(){
	float capacity = initialA[1][0];
	float actualCapacity = 0.0;
	vector<float> solution(n,0.0);

	vector<bool> taken(n,false);

	int loops = 0;

	while(actualCapacity < capacity && loops < n){
		int bestIndex = 0;
		float bestValue = 0.0;
		
		for(int i = 1; i < n+1; i++){
			if(initialA[0][i] + initialA[1][i] > bestValue && actualCapacity - initialA[1][i] < capacity && !taken[i]){
				bestValue = initialA[1][i] + initialA[0][i];
				bestIndex = i;
			}
		}

		if(bestIndex != 0){
			solution[bestIndex] = 1.0;
			solution[0] = solution[0] + initialA[0][bestIndex];
		
			taken[bestIndex] = true;
			actualCapacity = actualCapacity - initialA[1][bestIndex];
		}

		loops++;
	}

	this->greedySolution = solution;
}

/*
	Descripcion: este metodo permite comparar dos soluciones.
	Parametros: 
		-s1: solucion 1.
		-s2: solucion 2.
	Retorno: 
		-True si son iguales, False en otro caso.
*/
bool Simplex::equalsSolutions(vector<float> s1, vector<float> s2){
	if(s1.size() != s2.size()){
		return false;
	}
	for(int i = 0; i < s1.size(); i++){
		if(s1[i] != s2[i]){
			return false;
		}
	}
	return true;
}

/*
	Descripcion: este metodo permite encontrar la variable seleccionada con menor valor en la solucion.
	Parametros: 
		-solution: vector con la solución.
	Retorno:
		-Indice de la variable con menos valor en la solución.
*/
int Simplex::findPricelessSelectedVar(vector<float> solution){
	float value = 100000.0;
	int index = 0;
	for(int i = 1; i < solution.size(); i++){
		if(initialA[0][i] < value && solution[i] == 1){
			value = initialA[0][i];
			index = i;
		}
	}
	return index;
}