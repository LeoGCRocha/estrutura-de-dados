// Copyright [2019] <COLOQUE SEU NOME AQUI...>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif


template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    ArrayStack(DEFAULT_SIZE);
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) throw std::out_of_range("pilha cheia");
    contents[++top_] = data;
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    // removendo o primeiro elemento da pilha
    if (empty()) throw std::out_of_range("pilha vazia");
    return contents[top_--];
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty()) throw std::out_of_range("pilha vazia");
    return contents[top_];  // verificar se funciona
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;  // marcando posicao do topo para posicao inicial da pilha
}

template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;  // tamanho atual da pilha
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;  // tamanho maximo que a pilha pode alcançar
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;  //! verificando se tem elementos
}

template<typename T>
bool structures::ArrayStack<T>::full() {
    return top_ == (max_size_ - 1);
}
