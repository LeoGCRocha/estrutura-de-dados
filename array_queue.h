// Copyright [2020] Leonardo Gideão Costa Rocha
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif
// construtor vazio
template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    ArrayQueue(DEFAULT_SIZE);
}
// construtor com parametro de tamanho
template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    begin_ = -1;
    end_ = -1;
    size_ = 0;
    contents = new T[max_size_];
}
// destrutor
template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}
// metodo limpar fila
template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_ = -1;
    begin_ = -1;
    size_ = 0;
}
// metodo verificar se esta vazia
template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;
}
// metodo verificar se esta cheia
template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}
// retornar tamanho atual
template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}
// retornar tamanho maximo da fila
template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}
// retonar ultimo elemento da lista
template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) throw std::out_of_range("fila vazia");
    return contents[end_];
}
// adicionando elemento na lista
template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) throw std::out_of_range("fila cheia");
    size_++;
    contents[++end_%max_size()] = data;
}
// removendo elemento da fila
template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) throw std::out_of_range("fila vazia");
    size_--;
    return contents[++begin_%max_size()];
}

