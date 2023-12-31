#include "string_map.h"

template<typename T>
int string_map<T>::cantidadHijos(string_map::Nodo* padre) {
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        if (padre->siguientes[i] != nullptr)
            j++;
    }
    return j;
}

template<typename T>
typename string_map<T>::Nodo *string_map<T>::buscar(const string &clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); ++i) {
        actual = actual->siguientes[int(clave[i])];
    }
    return actual;
}

template<typename T>
typename string_map<T>::Nodo *string_map<T>::padre(string_map::Nodo* hijo, const string &clave) {
    Nodo* inicio = raiz;
    Nodo* padre = nullptr;
    int i = 0;
    while(inicio != hijo){
        padre = inicio;
        inicio = inicio->siguientes[int(clave[i])];
        i++;
    }
    return padre;
}

template<typename T>
string_map<T>::string_map() {
    raiz = nullptr;
    _size = 0;
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    //Eliminar lo que haya quedado de antes:
    for(string s : _claves){
        erase(s);
        _claves.erase(s);
    }
    //Copia la data del diccionario d
    raiz = d.raiz;
    for(string s : d._claves){
        pair<string, T> par = make_pair(s,d.at(s));
        insert(par);
        _claves.insert(s);
    }

    _size = d._size;
    return *this;
}

template<typename T>
string_map<T>::~string_map() {
    //Eliminar lo que haya quedado de antes:
    while(_claves.size()!=0){
        erase(*_claves.begin());
    }
    delete raiz;
    raiz = nullptr;
    _size = 0;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &valor) {
    if (empty()) {
        Nodo *n = new Nodo();
        raiz = n;
    }
    Nodo* actual = raiz;
    for (int i = 0; i < valor.first.size(); i++) {
        if (actual->siguientes[int(valor.first[i])] == nullptr) {
            Nodo* nuevo = new Nodo();
            actual->siguientes[int(valor.first[i])] = nuevo;
            actual = nuevo;
        } else {
            actual = actual->siguientes[int(valor.first[i])];
        }
    }
    if(actual->definicion==nullptr){
        T* def = new T(valor.second);
        actual->definicion = def;
    } else {
        *actual->definicion = valor.second;
    }
    _size++;
    _claves.insert(valor.first);

}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    // COMPLETAR
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    if (empty()) {
        return 0;
    } else {
        Nodo* actual = raiz;
        for (int i = 0; i < clave.size(); i++) {
            if (actual->siguientes[int(clave[i])] == nullptr) {
                return 0;
            } else {
                actual = actual->siguientes[int(clave[i])];
            }
        }
        return actual->definicion != nullptr;
    }
}

//Pre: la clave está definida.
template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

//Pre: la clave está definida.
template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo* actual = raiz;
    for (int i = 0; i < clave.size(); i++) {
        actual = actual->siguientes[int(clave[i])];
    }
    return *(actual->definicion);
}

//Pre: la clave está definida.
template<typename T>
void string_map<T>::erase(const string &clave) {
    Nodo* actual = raiz;

    Nodo* buscarClave = buscar(clave);
    delete buscarClave->definicion;
    buscarClave->definicion = nullptr;
    int indiceUltimoNodo = 0;

    for (int i = 0; i < clave.size(); ++i) {
        if (cantidadHijos(actual) > 1 || actual->definicion != nullptr)
            indiceUltimoNodo = i;
        actual = actual->siguientes[int(clave[i])];
    }

    for (int i = clave.size()-1; i >= indiceUltimoNodo ; --i) {
        Nodo* daddy = padre(actual, clave);
        if(cantidadHijos(actual) == 0 && actual->definicion == nullptr){
            delete actual;
            daddy->siguientes[int(clave[i])] = nullptr;
        }
        actual = daddy;
    }
    _size--;
    _claves.erase(clave);
}

template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}
