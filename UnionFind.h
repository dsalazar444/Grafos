#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <vector>;
using namespace std;

class UnionFind {
private:
    vector<int> padre, rango;//ATRIBUTOS
    //Padre es un vector que guarda el padre de cada nodo
    //Rango es un vector que guarda la altura del árbol de cada conjunto
public:
    UnionFind(int cantNodos);
    int encontrarPadre(int nodo);
    void unirConj(int nodo1, int nodo2);

};



#endif //UNIONFIND_H
