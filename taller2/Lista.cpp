#include "Lista.h"
#include "assert.h"

Lista::Lista(): prim(NULL), fin(NULL)    {
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;

}

Lista::~Lista() {
    destruirNodos();
}
void Lista::copiarNodos(const Lista& aCopiar){
    Nodo* actual = aCopiar.prim;
    while (actual!= nullptr){
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
}
void Lista::destruirNodos() {
    Nodo* actual = prim;
    while(actual!= nullptr){
        Nodo* sig = actual->sig;
        delete actual;
        actual = sig;
    }
    prim = nullptr;

}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    destruirNodos();
    copiarNodos(aCopiar);
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem, nullptr, nullptr);
    if(prim == NULL){
        prim = nuevo;
        fin= nuevo;
    }else{
        Nodo* actual = prim;
        nuevo->sig = actual;
        actual->ant= nuevo;
        prim = nuevo;

    }
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    if (prim== nullptr){
        agregarAdelante(elem);

    }
    else{
        Nodo* nuevo = new Nodo(elem, nullptr, fin);
        fin->sig = nuevo;
        fin = nuevo;
        /*Nodo* actual = prim;
        Nodo* nuevo = new Nodo(elem, nullptr, nullptr);

        while(actual->sig!= nullptr ){
            actual = actual->sig;
        }
        actual->sig = nuevo;
        nuevo->ant = actual;*/
    }
}

void Lista::eliminar(Nat i) {
    Nodo* actual = prim;
    Nodo* anterior;
    for (int j = 0; j < i; ++j) {
        anterior = actual;
        actual = actual->sig;
    }
    if (i == 0){
        if (actual->sig!= nullptr){
            prim= actual->sig;
            actual->sig->ant = nullptr;
        }else{
            prim = nullptr;
        }
    }else{
        if(i == longitud()-1){
            anterior = fin->ant;
            anterior->sig = nullptr;
            fin = anterior;
        }else{

            anterior->sig = actual->sig;
            actual->sig->ant = anterior;
        }
    }
    delete actual;

}

int Lista::longitud() const {
    // Completar
    Nodo* actual = prim;
    int c = 0;
    while(actual!= nullptr){
        c++;
        actual= actual->sig;
    }
    return c;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    //assert(actual->valor);
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* actual = prim;
    for (int j = 0; j < i; ++j) {
        actual = actual->sig;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}
