template <typename T>
string_map<T>::string_map()
    : _raiz(nullptr), _size(0){}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // Borro el arbol actual
    _borrar();

    // Si tengo algo que copiar...
    if (d._raiz != nullptr) {
        // Creo una nueva raiz
        _raiz = new Nodo();

        // Copio los nodos de d
        _copy_from(d._raiz, _raiz);
    }

    // Copio el size
    _size = d._size;

    return *this;
}


template <class T>
void string_map<T>::_copy_from(const Nodo* d, Nodo* h) {
    // Copio la definicion, si la hay
    if (d->definicion) {
        h->definicion = new T(*d->definicion);
    }

    // Copio los siguientes
    for(int i = 0; i < d->siguientes.size(); i++) {
        Nodo* d_sig_i = d->siguientes[i];

        // Si el i-ésimo siguiente de d es null, continuo
        if (d_sig_i == nullptr) {
            continue;
        }

        // Como el siguiente no es null, entonces tengo que
        // copiarlo al correspondiente en h.

        // Si no está creado, lo creo
        if(h->siguientes[i] == nullptr) {
            h->siguientes[i] = new Nodo();
        }

        // Sigo copiando
        _copy_from(d_sig_i, h->siguientes[i]);
    }
}

template <typename T>
string_map<T>::~string_map(){
    _borrar();
}

template <class T>
void string_map<T>::_borrar() {
    // Borro todos los nodos
    _borrar_siguientes(_raiz);

    // Reseteo el size y la raiz
    _size = 0;
    _raiz = nullptr;
}

template <class T>
void string_map<T>::_borrar_siguientes(Nodo* n) {
    // Si el nodo es null, no tengo que borrar nada
    if (n == nullptr) {
        return;
    }

    // Borro a los hijos y sus siguientes
    for (Nodo* s : n->siguientes) {
        _borrar_siguientes(s);
    }

    // Borro la definición de n si tiene
    if (n->definicion != nullptr) {
        _borrar_def(n);
    }
    // Borro a n
    delete n;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // Si ya está definido, retorno su definición
    if (count(clave)) {
        return at(clave);
    }

    // Si no está definido, le defino el valor por defecto.
    return _define_default(clave);
}

template <class T>
T& string_map<T>::_define_default(const string& clave) {
    // Supongo que la clave no está definida

    // Si no hay raiz, la creo
    if (_raiz == nullptr) {
        _raiz = new Nodo();
    }

    Nodo* actual = _raiz;
    for(char c : clave) {
        // Si no tengo siguiente, lo creo
        if (actual->siguientes[int(c)] == nullptr) {
            actual->siguientes[int(c)] = new Nodo();
        }

        actual = actual->siguientes[int(c)];
    }

    // Estoy parado en el nodo que va a tener la definición.
    // Le asigno la nueva definición
    actual->definicion = new T();

    // Incremento el size
    _size++;

    return *(actual->definicion);
}

template<class T>
void string_map<T>::_borrar_def(Nodo* &n) {
    // La borro
    delete(n->definicion);

    // La dejo en null
    n->definicion = nullptr;
}



template <class T>
bool string_map<T>::_contains(const string& clave) const {
    // Si no tengo raiz, nada va a estar contenido
    if (_raiz == nullptr) {
        return false;
    }
    Nodo* actual = _raiz;
    // Recorro los caracteres de la palabra
    for(char c : clave) {
        actual = actual->siguientes[int(c)];
        if (actual == nullptr) {
            return false;
        }
    }

    return actual->definicion != nullptr;
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    return _contains(clave)? 1 : 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // Como ya se que está definido, simplemente recorro hasta que lo encuentro
    Nodo* actual = _raiz;
    for(char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // Como ya se que está definido, simplemente recorro hasta que lo encuentro
    Nodo* actual = _raiz;
    for(char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *actual->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // Supongo que la clave está definida.
    // Eso implica que actual nunca es nullptr.

    // Busco la clave guardandome cual es el ultimo nodo que
    // no se debería eliminar.
    // Este es aquel que tiene mas de una arista o tiene definición.
    Nodo* actual = _raiz;
    Nodo* ultimo = nullptr;
    int indice_ultimo = -1;
    for(int i = 0; i < clave.size(); i++) {
        if(_tiene_aristas(actual) || actual->definicion != nullptr) {
            ultimo = actual;
            indice_ultimo = i;
        }
        actual = actual->siguientes[int(clave[i])];
    }

    // Estoy parado en el nodo que contiene el significado de la clave.
    // Borro su definición
    _borrar_def(actual);

    // Decremento el size
    _size--;

    // Si tiene aristas, no tengo que borrar el camino hacia el.
    if (_tiene_aristas(actual)) {
        return;
    }

    // Borro el camino de nodos hacia la clave a partir del siguiente al último nodo.
    // Se que no hay ningún null en el camino hasta que termino.
    actual = ultimo->siguientes[int(clave[indice_ultimo])];
    for (int i = indice_ultimo+1; i < clave.size(); i++) {
        // Guardo el actual para no perderlo
        Nodo* tmp = actual;
        // Actualizo el actual
        actual = actual->siguientes[int(clave[i])];
        // Se que los nodos no tienen definición, entonces
        // los borro sin más.
        delete(tmp);
    }
}

template <class T>
bool string_map<T>::_tiene_aristas(const Nodo* n) {
    return _aristas(n) > 0;
}

template <class T>
int string_map<T>::_aristas(const Nodo* n) {
    int aristas = 0;
    for (Nodo* sig : n->siguientes) {
        if(sig != nullptr) {
            aristas++;
        }
    }
    return aristas;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return size() == 0;
}
