#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        /**
         * Completar con lo que sea necesario...
         **/

        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v): valor(v), izq(NULL), der(NULL){}
            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;
        };

        // Puntero a la raíz de nuestro árbol.
        Nodo* _raiz;
        // Cardinal del conjunto
        unsigned _cardinal;

        // Busca el nodo con la clave especificada, guardando el recorrido.
        Conjunto<T>::Nodo* _buscar_con_pila(const T& clave, Conjunto::Nodo* actual, stack<Conjunto<T>::Nodo*> &recorrido) const;

        // Busca el nodo con la clave especificada
        Conjunto<T>::Nodo* _buscar(const T& clave, Conjunto::Nodo* actual) const;

        void _remover_nodo(Conjunto::Nodo* &n, stack<Conjunto::Nodo*> recorrido);
        // Devuelve un vector con los hijos
        vector<Conjunto<T>::Nodo*> _hijos(Conjunto<T>::Nodo* &n);

        // El inmediato sucesor es el mas chico de los mas grandes que n.
        Conjunto<T>::Nodo* _inmediato_sucesor(Conjunto<T>::Nodo* &n);

        // Recorre los hijos del lado izquierdo hasta encontrar el nodo mas chico
        // (el que no tenga hijo izquierdo)
        Conjunto<T>::Nodo* _minimo_desde(Conjunto<T>::Nodo* n) const;

        // Devuelve el nodo con el maximo elemento
        Conjunto<T>::Nodo* _maximo_desde(Conjunto<T>::Nodo* n) const;

        void _destruir(Conjunto<T>::Nodo* n);

        void print(std::ostream& out, const std::string& prefix, const Conjunto::Nodo* n, bool isLeft) const;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
