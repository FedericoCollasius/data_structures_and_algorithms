#include "Lista.h"

Lista::Nodo::Nodo(const int &elem) : prev_(nullptr), next_(nullptr), val_(elem) {};

Lista::Lista() {
    head_ = nullptr;
    tail_ = nullptr;
    tam_ = 0;
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* temp = head_;
    while(head_ != nullptr){
        temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    head_= nullptr;
    tail_=nullptr;
    tam_ = 0;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo* temp = head_;
    while(head_ != nullptr){
        temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    tam_ = 0;

    tam_ = aCopiar.longitud();
    if (tam_ > 0) {
        head_ = new Nodo(aCopiar.head_->val_);
        Nodo *proximo = aCopiar.head_->next_;
        Nodo *actual = head_;
        while (proximo != nullptr) {
            actual->next_ = new Nodo(proximo->val_);
            (actual->next_)->prev_ = actual;
            actual = actual->next_;
            proximo = proximo->next_;
        }
        tail_ = actual;
    } else {
        head_ = nullptr;
        tail_ = nullptr;
    }
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nodoAdelante = new Nodo(elem);
    if(tam_ != 0) {
        head_->prev_ = nodoAdelante;
        nodoAdelante->next_ = head_;
    } else {
        nodoAdelante->next_ = nullptr;
        tail_ = nodoAdelante;
    }
    head_ = nodoAdelante;
    tam_++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nodoDetras = new Nodo(elem);
    if(tam_ != 0) {
        tail_->next_= nodoDetras;
        nodoDetras->prev_ = tail_;
    } else {
        nodoDetras->prev_ = nullptr;
        head_ = nodoDetras;
    }
    tail_ = nodoDetras;
    tam_++;
}

void Lista::eliminar(Nat i) {
    assert(i < tam_ && tam_ != 0);
    Nodo *eliminar = head_;
    int pos = 0;
    bool encontro = false;
    int tamOrig = tam_;
    while (!encontro) {
        if (pos == i) {                 //encuentro la posicion
            if (eliminar == head_) {                // Caso: elimino es el primero de la lista
                head_ = eliminar->next_;                // head ahora apunta al siguiente nodo(el 2do)
                if (head_ != nullptr)                   // Caso: head apunta a algo
                    eliminar->next_->prev_ = nullptr;       //el 2do nodo apunta a nullptr ahora
            }
            else                                    // Caso: elimino esta en el medio de la lista o al final
            {
                eliminar->prev_->next_ = eliminar->next_; // la flecha derecha del anterior nodo apunta al que le sigo del que elimino
                if(eliminar->next_ != nullptr)            // si el que le sigue a eliminar no es nullptr
                    eliminar->next_->prev_ = eliminar->prev_;   //la flecha izq del que le sigue a eliminar apunta al anterior de eliminar
                else
                    tail_ = eliminar->prev_;                    // si es el nullptr entonces estamos con el ultimo elemento asi que hay que actualizar
            }
            tam_--;
        }
        if(tamOrig != tam_){
            encontro = true;
            delete eliminar;
        } else {
            eliminar = eliminar->next_;
            pos++;
        }
    }
}
int Lista::longitud() const {
    return tam_;
}

const int& Lista::iesimo(Nat i) const {
    assert(i < tam_ && tam_!=0);
    Nodo* actual = head_;
    int pos = 0;
    bool encontro = false;
    while(!encontro){
        if(pos == i){
            encontro = true;
        } else {
            actual = actual->next_;
            pos++;
        }
    }
    return actual->val_;
}

int& Lista::iesimo(Nat i) {
    assert(i < tam_ && tam_!=0);
    Nodo* actual = head_;
    int pos = 0;
    bool encontro = false;
    while(!encontro){
        if(pos == i){
            encontro = true;
        } else {
            actual = actual->next_;
            pos++;
        }
    }
    return actual->val_;
}

void Lista::mostrar(ostream& os) {
    Nodo* actual = head_;
    os << "[" << actual->val_ << ",";
    actual = actual->next_;
    while(actual != nullptr){
        if(actual->next_==nullptr)
            os << " " << actual->val_;
        else
            os << " " << actual->val_ <<",";
        actual = actual->next_;
    }
    os << "]";
}
