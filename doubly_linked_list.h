  //! Copyright [2020] <Leonardo Gideão Costa Rocha>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

//! ...
template<typename T>
class DoublyLinkedList {
 public:
    //! ...
    DoublyLinkedList();  // construtor padrão
    //! ...
    ~DoublyLinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // insere no fim
    //! ...
    void push_front(const T& data);  // insere no início
    //! ...
    void insert(const T& data, std::size_t index);  // insere na posição
    //! ...
    void insert_sorted(const T& data);  // insere em ordem
    //! ...
    T pop(std::size_t index);  // retira da posição
    //! ...
    T pop_back();  // retira do fim
    //! ...
    T pop_front();  // retira do início
    //! ...
    void remove(const T& data);  // retira específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    //! ...
    const T& at(std::size_t index) const;  // getter constante a um elemento
    //! ...
    std::size_t find(const T& data) const;  // posição de um dado
    //! ...
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}
        T& data() {  // getter: dado
            return data_;
        }
        const T& data() const {  // getter const: dado
            return data_;
        }
        Node* prev() {  // getter: anterior
            return prev_;
        }
        const Node* prev() const {  // getter const: anterior
            return prev_;
        }
        void prev(Node* node) {  // setter: anterior
            prev_ = node;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures
#endif

//! Construtor
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {  //
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}
//! Destrutor
template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}
//! Empty
template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}
//! Size
template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
//! Clear
template<typename T>
void structures::DoublyLinkedList<T>::clear() {  // funcionando
    Node *at, *ant;
    at = head;
    while (at) {
        ant = at;
        at = at->next();
        delete(ant);
    }
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}
//! Push Back
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node *b = new Node(data, tail, nullptr);
    if (empty()) {
        head = b;
    } else {
        tail->next(b);
    }
    tail = b;
    size_++;
}
//! Push Front
template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *b = new Node(data, nullptr, head);
    if (empty()) tail = b;
    else
        head->prev(b);
    head = b;
    size_++;
}
//! Pop Front
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *b = head;
    T data = b->data();
    if (size() == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next();
        head->prev(nullptr);  //  Definindo o anterior como nulo.
    }
    delete b;
    size_--;
    return data;
}
//! Insert
template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size()) throw std::out_of_range("posicao invalida");
    Node *t = head;
    for (int i = 0; i < index; i++) {
        t = t->next();
    }
    Node *p = new Node(data, t->prev(), t);
    t->prev()->next(p);
    t->prev(t);
    size_++;
}
//! Insert sorted
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node *b = head;
    int i = 0;
    while (b) {
        if (b->data() >= data) break;
        b = b->next();
        i++;
    }
    if (i == 0) {
        push_front(data);
    } else if (i == size()) {
        push_back(data);
    } else {
        insert(data, i);
    }
}
//! Pop Back
template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *b = tail;
    T data = b->data();
    if (size() == 1) {
        head = tail = nullptr;
    } else {
        tail = tail->prev();
        tail->next(nullptr);
    }
    size_--;
    delete b;
    return data;
}
//! At 1
template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size()) throw std::out_of_range("posicao invalida");
    Node *b = head;
    for (int i = 0; i < index; i++) {
        b = b->next();
    }
    return b->data();
}
//! At 2
template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    Node *b = head;
    for (int i = 0; i < index; i++) {
        b = b->next();
    }
    return b->data();
}
//! Find
template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *b = head;
    for (int i = 0; i < size(); i++) {
        if (b->data() == data) {
            return i;
        } else {
            b = b->next();
        }
    }
    return size();
}
//! Pop
template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size()) throw std::out_of_range("posicao invalida");
    Node *b = head;
    for (int i = 0; i < index; i++) {
        b = b->next();
    }
    T data = b->data();
    b->prev()->next(b->next());
    b->next()->prev(b->prev());
    delete b;
    size_--;
    return data;
}
//! Contains
template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    if (empty()) throw std::out_of_range("lita vazia");
    Node *b = head;
    while (b) {
        if (b->data() == data) return true;
        b = b->next();
    }
    return false;
}
//! Remove
template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty()) throw std::out_of_range("lista vazia");
    int pos = find(data);
    if (pos < size()) pop(pos);
}
