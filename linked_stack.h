//! Copyright [2020] <Leonardo Rocha>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {
//! ...
template<typename T>
class LinkedStack {
 public:
    //! ...
    LinkedStack();
    //! ...
    ~LinkedStack();
    //! ...
    void clear();  // limpa pilha
    //! ...
    void push(const T& data);  // empilha
    //! ...
    T pop();  // desempilha
    //! ...
    T& top() const;  // dado no topo
    //! ...
    bool empty() const;  // pilha vazia
    //! ...
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
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
        Node* next_;
    };

    Node* head;  // nodo-topo
    std::size_t size_;  // tamanho
};

}   // namespace structures
#endif
// Destrutor
template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}
// Construtor
template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    head = nullptr;
    size_ = 0;
}
// Empty
template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);
}
// Size
template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
// Push
template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *node;
    node = new Node(data, head);
    head = node;
    size_++;
}
// Clear
template<typename T>
void structures::LinkedStack<T>::clear() {
    Node *n1, *n2 = head;
    while (n2) {
        n1 = n2;
        n2 = n2->next();
        delete n1;
    }
    head = nullptr;
    size_ = 0;
}
// Top
template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) throw std::out_of_range("pilha vazia");
    return head->data();
}
// Pop
template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) throw std::out_of_range("pilha vazia");
    Node *b = head;
    T data = b->data();
    head = b->next();
    delete(b);
    size_--;
    return data;
}

