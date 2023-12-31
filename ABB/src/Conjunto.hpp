
#include "Conjunto.h"

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) {
    valor = v;
    izq = nullptr;
    der = ;
}

template<class T>
Conjunto<T>::Conjunto() {
    raiz_ = nullptr;
    cardinal_ = 0;
}

template<class T>
Conjunto<T>::~Conjunto() {

}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    bool res = false;
    Nodo *actual = this->raiz_;
    while (actual != nullptr && !res) {
        if (actual->valor == clave)
            res = true;
        else if (actual->valor < clave)
            actual = actual->der;
        else
            actual = actual->izq;

    }
    return res;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    if(!pertenece(clave)) {
        Nodo *anterior = nullptr;
        Nodo *actual = this->raiz_;
        while (actual != nullptr && actual->valor != clave) {
            anterior = actual;
            if (actual->valor < clave)
                actual = actual->der;
            else
                actual = actual->izq;
        }
        if (actual == nullptr) {
            Nodo *nuevaClave = new Nodo(clave);
            if (anterior == nullptr)
                this->raiz_ = nuevaClave;
            else if (anterior->valor < clave)
                anterior->der = nuevaClave;
            else
                anterior->izq = nuevaClave;
        }
        cardinal_++;
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    if (pertenece(clave)) { // me fijo si está.
        Nodo *anterior = nullptr; // busco al elemento.
        Nodo *actual = this->raiz_;
        while (actual != nullptr && actual->valor != clave) {
            anterior = actual;
            if (actual->valor < clave)
                actual = actual->der;
            else
                actual = actual->izq;
        }
        // Encuentro la clave
        if (actual->der == nullptr && actual->izq == nullptr) {// Caso 1: la clave es una hoja.
            if (anterior != nullptr) {
                if (anterior->der != nullptr &&
                    anterior->der->valor == clave) // Me fijo cual de los hijos es el que tiene la clave y elimino ese.
                    anterior->der = nullptr;
                else {
                    if (anterior->izq != nullptr && anterior->izq->valor == clave)
                        anterior->izq = nullptr;
                }
            }
            delete actual;
        } else {
            if (actual->der == nullptr && actual->izq != nullptr ||
                actual->der == nullptr && actual->izq != nullptr) {// Caso 2: la clave tiene un hijo.
                if (anterior != nullptr) {
                    if (anterior->der != nullptr && anterior->der->valor == clave)
                        anterior->der = actual->izq;
                    else
                        anterior->izq = actual->izq;
                    delete actual;
                } else {
                    if (actual->izq == nullptr && actual->der != nullptr) {
                        if (anterior->der != nullptr && anterior->der->valor == clave)
                            anterior->der = actual->der;
                        else
                            anterior->izq = actual->der;
                        delete actual;
                    }
                }
            } else { // Caso3: la clave tiene 2 hijos.
                Nodo *padreInmSuc = actual;
                Nodo *inmSuc = actual->der;
                while (inmSuc->izq != nullptr) {    //busco suc Inm
                    padreInmSuc = inmSuc;
                    inmSuc = inmSuc->izq;
                }
                if (padreInmSuc != actual)
                    padreInmSuc->izq = inmSuc->der;
                else
                    padreInmSuc->der = inmSuc->der;
                actual->valor = inmSuc->valor;
                delete inmSuc;
            }
        }
        cardinal_--;
    }
}

template<class T>
//Pre: clave está en el conjunto y hay un siguiente.
const T &Conjunto<T>::siguiente(const T &clave) { //Uso inorder
    Nodo *anterior = nullptr; // busco al elemento.
    Nodo *actual = this->raiz_;
    while (actual != nullptr && actual->valor != clave) {
        anterior = actual;
        if (actual->valor < clave)
            actual = actual->der;
        else
            actual = actual->izq;
    }
    if (actual->der != nullptr) {  //Caso A: el nodo actual tiene arbol derecho ->devuelvo el minimo en ese arbol.
        actual = actual->der;
        while (actual != nullptr) {
            anterior = actual;
            actual = actual->izq;
        }
    } else { //Caso B: el nodo actual no tiene sub arbol derecho
        if ( anterior->der != nullptr && anterior->der->valor == actual->valor) {//Caso B.1: el nodo actual es hijo der ->subo en el arbol hasta llegar a un nodo por su rama izq, y devuelvo ese elemento.
            Nodo* hijoIzq = anterior;
            anterior = nullptr;
            actual = raiz_;
            while (actual->valor != hijoIzq->valor) {
                if (actual->valor < hijoIzq->valor)
                    actual = actual->der;
                else {
                    anterior = actual;
                    actual = actual->izq;
                }
            }
        }
    }//Caso B.2: el nodo actual es hijo izq ->devuelvo el valor del padre.
    return anterior->valor;
}

template<class T>
//Pre: el conjunto no es vacío.
const T &Conjunto<T>::minimo() const {
    Nodo *anterior = nullptr;
    Nodo *actual = this->raiz_;
    while (actual != nullptr) {
        anterior = actual;
        actual = actual->izq;
    }
    return anterior->valor;
}

template<class T>
//Pre: el conjunto no es vacío.
const T &Conjunto<T>::maximo() const {
    Nodo *anterior = nullptr;
    Nodo *actual = this->raiz_;
    while (actual != nullptr) {
        anterior = actual;
        actual = actual->der;
    }
    return anterior->valor;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinal_;
}


template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}









/////////////////////////////////////////////////////////





