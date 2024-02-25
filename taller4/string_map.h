#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <iostream>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo(): siguientes(256, nullptr),
                definicion(nullptr) {}

    };

    Nodo* _raiz;
    int _size;

    // Retorna si la clave pertenece al mapa.
    bool _contains(const string &clave) const;

    // Define una clave nueva (creando los nodos intermedios)
    // y retorna una referencia a la copia de su definición
    // creada en el mapa.
    // Esta clave tiene por definición el valor por defecto de T.
    // (i.e el que retorna el constructor por defecto)
    T& _define_default(const string &clave);

    // Borra todos los nodos
    void _borrar();

    // Borra todos los nodos siguientes y sus siguientes
    void _borrar_siguientes(Nodo* n);

    // Copia los nodos recorriendo desde el nodo d y copiando al nodo h.
    // Supone que h no es null.
    // Supone que de h en adelante no hay definiciones (sino, hay leaks).
    void _copy_from(const Nodo* d, Nodo* h);

    // Dice la cantidad de aristas (nodos siguientes no null) que tiene.
    // Supone que n no es null.
    int _aristas(const Nodo* n);

    // Dice si un nodo tiene aristas.
    bool _tiene_aristas(const Nodo* n);

    // Borra la definición de un nodo
    // y la setea en nullptr.
    void _borrar_def(Nodo* &n);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
