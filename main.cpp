#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <limits>
#include <algorithm>
#include "UnionFind.h"
using namespace std;

//------------------------------------------------------------METODOS PUNTO1------------------------------------------------------------------------
int verificarEntrada() //FUNCION PARA VERIFICAR ENTRADA INVALIDA
{
    int n;
    while(cin.fail()) //mientras que la entrada sea invalida
    {
        cin.clear(); //limpiamos el estado de cin (es decir, que ya no sea failbit, porque en este estado cin no admite ninguna otra entrada, incluso si es válida, hasta que se cambie su estado)
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpiamos el buffer de la ultima entrada(le pasamos para que descarte una cantidad de elementos que será el tamaño máximo del buffer, o que descarte hasta el salto de linea), porque cin no toma entradas invalida, sino que las deja en el buffer, entonces cada que se ejecuta, este se encuentra siempre con el mismo valor, haciendo que se quede en un bucle infinito
        cout<<"Ingrese una cantidad valida (numero entero positivo): "<<endl;
        cin >> n;
    }
    return n;
}

vector<int> obtenerAdyacentesNoDirigida(int cantAdy)
{
    vector<int> nodosAdy(cantAdy);
    /*
     *al definirlo fuera de llenarLista, este es como un vector auxiliar, que en cada iteración cambia de valores pues solo existe dentro de esta
     *función (es como cuando creamos y definimos una var en un ciclo, esta fuera de él no existe)
     */
    for(int i=0; i<nodosAdy.size();i++) //si me dicen 0, nunca entrará
    {
        int nodoIns;
        cout<<"    Ingrese nodo adyacente #"<<i<<endl;
        cin>>nodoIns;
        if(cin.fail()){nodoIns=verificarEntrada();} //si la entrada es invalida, llamamos a función
        nodosAdy[i]=nodoIns;
    }
    return nodosAdy;
}

void llenarListaNoDirigida(vector<vector<int>>& listaAdyacencia)
/*
 *debemos pasar la lista por referencia, para que los cambios que hagamos afecten a la original(creada en el main) y no a una copia, pues si no al
 *imprimir el grafo en el main este esstará vacio porque en realidd no le hemos hecho cambios a él sino a otras copias
 */
{
    for(int i=0; i<listaAdyacencia.size();i++)
    {
        int cantAdy;
        cout<<"Ingrese la cantidad (numero entero positivo) de nodos adyacentes al nodo #"<<i<<endl;
        cin>>cantAdy;
        if(cin.fail()){cantAdy=verificarEntrada();} //si la entrada es invalida, llamamos a función
        if(cantAdy>0){listaAdyacencia[i]=obtenerAdyacentesNoDirigida(cantAdy);} //agregamos vector sii el usuario ingresa un número entero positivo
    }
}
void imprimirGrafoNoDirigido(vector<vector<int>>& listaAdyacencia)
{
    cout << "Lista de adyacencia del grafo:" << endl;
    for (int i = 0; i < listaAdyacencia.size(); i++) {
        cout << "Nodo " << i << ": ";
        for (int ady : listaAdyacencia[i]) {
            cout << ady << " ";
        }
        cout << endl;
    }

}


bool recDetectarCiclo(int actual, int padre, vector<bool>& visitados, vector<vector<int>>& listaAdyacencia)
{
    visitados[actual] = true;
    //en la posición equivalente al nodo actual,guardaremos un true, para marcarlo como "visitado"
    //recorremos nodos adyacentes usando DFS
    for (int ady: listaAdyacencia[actual]) //usamos el for-each para recorrer la Lista de adyacencia del nodo ACTUAL
    {
        if (!visitados[ady])
        //si ese nodo no está visitado, retornara un false (porque es un array de booleanos, que se guardan con el valor false por default), pero lo negamos para que sea un true y entre
        {
            recDetectarCiclo(ady, actual, visitados, listaAdyacencia);
            /*
             *recorremos el grafo llamando recursivamente la función, y pasando ahora como actual a cualesquier nodo adyacente que tenga este,
             *esto lo hacemos con todos los adyacentes, recoriendo el grafo a profundidad antes de devolvernos.
             */
        }else if (ady != padre)
        {
            return true;
            /*
         *cuando estamos recorriendo el grafo y encontramos un nodo, el cual tiene un adyacente que ya fue visitado, pero ese adyacente es diferente
         *al padre, hay un ciclo (porque si es el padre solo indica el camino de "regreso" a este, ya que es un grafo no dirigido), pues al ser el
         *adyacente de actual, y estar visitado, indica que usando otro camino llegamos a él, y si seguimos nuestra ruta (DFS), volveremos a llegar a él,
         *digamos que ese nodo es C, entonces cuando lleguemos a C, nos podremos devolver por dos o más rutas (la que nos lleva a actual, o desde la que lo
         *marcamos como visitado), y una de esa nos llevará hasta actual,que nos llevará hasta C, y así sucesivaente, llevandonos a un bucle.
         */
        }
    }
    return false;
}
void detectarCiclo(int actual, vector<vector<int>>& listaAdyacencia)
{
    vector<bool> visitados(listaAdyacencia.size());
    /*
     *Creamos un array de tipo booleano que almacenará qué nodos hemos visitado, guardando en la posición correspondiente al nodo (es decir, si es
     *el nodo #3, se guardará en la posicion 3 del array de visitados) false si no ha sido visitado, y true si sí lo ha sido. Todos en un principio
     *se inicializarán con false.
     */
    if(recDetectarCiclo(actual, -1,visitados,listaAdyacencia))
        /*
         *llamamos la función recursiva pasandole un nodo inicial,que como no tiene padre, este dato lo pasamos como -1, y lo ue nos retorne esta
         *funci+on se evalua en el condicional
         */
    {
        cout<<"el grafo tiene ciclos"<<endl;//si recDetectarCiclo retorna un true, imprimimos que el grafo tiene ciclos
    }else
    {
        cout<<"el grafo no tiene ciclos"<<endl;//si recDetectarCiclo retorna un false, imprimimos que el no grafo tiene ciclos
    }
}
//------------------------------------------------------------METODOS PUNTO2------------------------------------------------------------------------
// Definición del tipo de datos para nuestro grafo

using Grafo = unordered_map<int, vector<pair<int, int>>>;

// Dijkstra función

unordered_map<int, int>dijkstra(const Grafo &grafo, int inicio) {

    // Creacoin del diccionario de distancias
    unordered_map<int, int> distancia;
    for(const auto & nodo : grafo) {
        distancia[nodo.first] = INT_MAX;
    }
    // inicialización desde cero
    distancia[inicio]= 0;


    // hacemos uso de priority queue para recopilar el nodo con la menor distacia conodifa

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pendiente;
    pendiente.push({0, inicio});


    // El while nos ayudará a pasar los nodos mientras hayan pendinetes
    while(!pendiente.empty()) {
        int distancia_actual= pendiente.top().first;
        int nodo_actual= pendiente.top().second;
        pendiente.pop();

        // con el if verificaremos si la distancia actual es mayor que la bucscada
        if(distancia_actual> distancia[nodo_actual]) continue;

        // con el for haremos una busqueda de nodos adyacentes

        for(const auto &adyacente : grafo.at(nodo_actual)) {
            int nodo_vecino= adyacente.first;
            int peso_arista= adyacente.second;

            int distancia_potencial= distancia[nodo_actual]+ peso_arista;

            // con el if actulizaremos las distancias para los caminos mas corto

            if(distancia_potencial< distancia[nodo_vecino]) {
                distancia[nodo_vecino]= distancia_potencial;
                pendiente.push({distancia_potencial, nodo_vecino});
            }
        }
    }

    return distancia;
}

//------------------------------------------------------------METODOS PUNTO3------------------------------------------------------------------------
//Creamos estructura de una arista de grafo ponderado
struct Arista
{
    //atributos
    int nodo1, nodo2, peso;
    //metodo para imprimir vector de aristas
    static void imprimirAristas(vector<Arista> &aristas)
    {
        cout<<"Aristas en el grafo: "<<endl;
        for(Arista &arista : aristas)
        {
            cout<<" ( "<<arista.nodo1<<" - "<<arista.nodo2<<" ) : "<<arista.peso<<endl;
        }
    }
};

//Función para ordenar aristas por peso de forma ascendente
void ordenarAscendente(vector<Arista> &aristas, int cantNodos) //como no retorna un valor, las modificaciones que le hagamos al vector deben ser
//hechas en este directamente, no en una copia, por eso debemos usar &.
{
    //usamos el metodo sort para ordenar el vector con aristas, que toma 3 parametros, donde inicia (primer elemento), donde termina (donde finaliza) y en base a qué se ordena, en nuestro
    //caso usamos una función lamda, que toma dos valores constantes, nodo1 y nodo2, y retorna el de menor peso (recordemos que el peso es un atributo
    //de Arista) de tal forma que se agregue de forma ascendente
    std::sort(aristas.begin(),aristas.end(),[](const Arista &nodo1, const Arista &nodo2)
    {
       return nodo1.peso < nodo2.peso;
    });
}
vector<Arista> algoritmoKruskal(vector<Arista> aristas, int tamano)
{
    //Creamos objeto tipo UnionFind y llamamos al constructor
    UnionFind unionf(tamano);
    vector<Arista> aristasAGM;
    int pesoMin=0;
    for(Arista &arista : aristas)
    {
        int nodo1=arista.nodo1;
        int nodo2=arista.nodo2; //recordemos que arista es un estructura con parametros nodo1,nodo2, peso, entonces acpa necesitamos, de la misma arista, sus dos nodos
        if(unionf.encontrarPadre(nodo1) != unionf.encontrarPadre(nodo2)) //obtenemos los padres de ambos nodos
        {
            unionf.unirConj(nodo1,nodo2); //si tenemos dos nodos en una arista, y estos tienen diferentes padres, unimos los conjuntos, de tal forma que quede 1
            aristasAGM.push_back(arista); //añadimos arista al AGM, pues ya la unimos
            pesoMin += arista.peso; //vamos sumando (acumulando) el peso de cada arista para obtener el peso minimo del AGM
        }
    }
    cout<<"El peso total del AGM es "<<pesoMin<<endl;
    return aristasAGM;
}
int main()
{
    //--------------------------------------------------------------------EJERCICIO 1--------------------------------------------------------------
    int cantNodos;
    cout << "Digite la cantidad de nodos del grafo: " << endl;
    cin >> cantNodos;
    if(cin.fail()) {cantNodos=verificarEntrada();} //si la entrada es invalida, llamamos a función

    vector<vector<int>> listaAdyacencia(cantNodos); //creamos la lista de adyacencia
    llenarListaNoDirigida(listaAdyacencia); //Llamamos función para llenar la lista de adyacencia
    imprimirGrafoNoDirigido(listaAdyacencia); //Imprimimos lista
    detectarCiclo(0,listaAdyacencia); //Buscamos si lista tiene ciclo

    //--------------------------------------------------------------------EJERCICIO 2--------------------------------------------------------------
    // CReación y deifnición de nuestro grafo
    Grafo grafoPunto2= {
        {1, {{2, 4}, {3, 1}}},
        {2, {{3, 2}, {4, 5}}},
        {3, {{4, 8}}},
        {4, {}}
    };

    // Calculamos las distancias desde el nodo de inicio
    int inicio= 1;
    unordered_map<int, int> distancias= dijkstra(grafoPunto2, inicio);

    // con ayuda del for imprimiremos las distancias
    for(const auto &distancia : distancias) {
        cout<< "La distancia del nodo "<< inicio << " al nodo " << distancia.first<< " es " <<distancia.second<< endl;
    }
    //--------------------------------------------------------------------EJERCICIO 3--------------------------------------------------------------
    //Creamos vector con aristas del grafo
    cout<<"Ejemplos AGM"<<endl;
    cout<<"Ejemplo 1: "<<endl;
    vector<Arista> grafo1={
        {1, 3, 3},
        {1, 2, 4},
        {2, 4, 2},
        {3, 4, 5}};
    ordenarAscendente(grafo1,grafo1.size());//Ordenamos el vector antes de aplicarle kruskal
    //Llamamos a algoritmoKruskal para encontrar AGM
    vector<Arista> AGM1= algoritmoKruskal(grafo1,4);
    Arista::imprimirAristas(AGM1);

    //EJEMPLO 2
    cout<<"Ejemplo 2: "<<endl;
    vector<Arista> grafo2 = {
        {1, 2, 4},
        {1, 3, 3},
        {2, 4, 2},
        {3, 4, 5}
    };
    ordenarAscendente(grafo2, grafo2.size());
    vector<Arista> AGM2= algoritmoKruskal(grafo2,5);
    Arista::imprimirAristas(AGM2);
    //EJEMPLO 3
    cout<<"Ejemplo 3: "<<endl;
    vector<Arista> grafo3 = {
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 7},
        {3, 4, 3},
        {3, 5, 5},
        {4, 5, 6}
    };
    ordenarAscendente(grafo3, grafo3.size());
    vector<Arista> AGM3= algoritmoKruskal(grafo3,7);
    Arista::imprimirAristas(AGM3);

    return 0;
}
