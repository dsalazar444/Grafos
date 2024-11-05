#include "UnionFind.h"
UnionFind::UnionFind(int cantNodos)
{
    //Asignamos el tamaño a los vectores rango y padre
    rango.resize(cantNodos);
    padre.resize(cantNodos);
    int i=0;
    while(i<cantNodos)//inicialmente cada nodo es su propio padre
    {
        padre[i]=i;
        i++;
    }
}
int UnionFind::encontrarPadre(int nodo)
{
    if(padre[nodo]!=nodo) //si el nodo no es su propio padre
    {
        padre[nodo]=encontrarPadre(padre[nodo]);//le reestablecemos como padre el nodo que nos retorne la llamada recursiva de la funcion (cuando Padre[nodo]==nodo) y al hacer .pop(), actualizamos el padre de los nodos en la lista de recursividad
    }
    return padre[nodo];
}

void UnionFind::unirConj(int nodo1, int nodo2)
{
    int raizNodo1= encontrarPadre(nodo1); //la raiz del nodo será el padre de este
    int raizNodo2= encontrarPadre(nodo2);
    if(raizNodo1 != raizNodo2) //si los nodos tienen padres diferentes, es decir estan en conjuntos diferentes
    {
        if(rango[raizNodo1] > rango[raizNodo2]) //si el conjunto del nodo1 es más alto que el de nodo2
        {
            padre[raizNodo2]=raizNodo1; //el padre de raizNodo2 (y por ende todos los "hijos" de este, será el padre de nodo1, es decir, raizNodo1, aquí estamos uniendo el conjunto menor al mayor
        }else if(rango[raizNodo1] < rango[raizNodo2])
        {
            padre[raizNodo1]=raizNodo2;
        }else
        {
            padre[raizNodo2]=raizNodo1; //si ambos tienen misma "altura" y son diferentes, unimos a cualquiera de los conjuntos al otro, y el que unimos le aumentamos el rango
            rango[raizNodo1]++;
        }
    }
}

