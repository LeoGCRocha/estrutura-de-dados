// Copyright [2020] <Leonardo Rocha...>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size t
#include <stdexcept>  // C++ Exceptions


namespace structures {

template<typename T>
//! Class ArrayList
class ArrayList {
 public:
    //! construtor
    ArrayList();
    //! construtor com parametros
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();
    //! metodo limpar lista
    void clear();
    //! adicionando no inicio
    void push_back(const T& data);
    //! adicionando no final
    void push_front(const T& data);
    //! adicionando na posição
    void insert(const T& data, std::size_t index);
    //! adicionando em posição aleatoria
    void insert_sorted(const T& data);  // CONTINUAR DAQUI
    //! removendo em uma posição
    T pop(std::size_t index);
    //! removendo do inicio
    T pop_back();
    //! removendo do final
    T pop_front();
    //! removendo dado
    void remove(const T& data);
    //! lista cheia
    bool full() const;
    //! lista vazia
    bool empty() const;
    //! lista contem
    bool contains(const T& data) const;
    //! procurando posição de um valor
    std::size_t find(const T& data) const;
    //! tamanho atual da lista
    std::size_t size() const;
    //! tamanho maximo da lista
    std::size_t max_size() const;
    //! valor na posição
    T& at(std::size_t index);
    //! operator
    T& operator[](std::size_t index);
    //! na posição
    const T& at(std::size_t index) const;
    //! operator
    const T& operator[](std::size_t index) const;
    //! mover para frente
    void move_front(std::size_t index);
     //! mover para tras
    void move_back(std::size_t index);

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int end_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures
#endif
// Construtor sem argumentos
template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}
// Construtor com argumentos
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
    end_ = -1;
}
// Destrutor
template<typename T>
structures::ArrayList<T>::~ArrayList() {
  delete [] contents;
}
// Metodo size
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}
// Metodo :maxSize():
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}
// Metodo void:clear():
template<typename T>
void structures::ArrayList<T>::clear() {
    end_ = -1;
    size_ = 0;
}
// Metodo bool:empty()
template<typename T>
bool structures::ArrayList<T>::empty() const {
  return (size_ == 0);
}
// Metodo bool:full()
template<typename T>
bool structures::ArrayList<T>::full() const {
  return (size_ == max_size_);
}
// Metodo push_back
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    move_front(0);
    contents[0] = data;
    size_++;
}
// Metodo push_front
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    contents[end_++] = data;
    size_++;
}
// Insert em uma posição
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
     if (full()) throw std::out_of_range("lista cheia");
     if (index<0 || index>end_) throw std::out_of_range("posicao invalida");
     move_front(index);
     contents[index] = data;
     size_++;
}
// Deslocando p/ frente
template<typename T>
void structures::ArrayList<T>::move_front(std::size_t index) {
    if (index<0 || index>end_) throw std::out_of_range("posição invalida");
    for (int i = end_+1; i > index; i--) contents[i] = contents[i-1];
    end_++;
}
// Deslocando p/ tras
template<typename T>
void structures::ArrayList<T>::move_back(std::size_t index) {
    if (index<0 || index>end_) throw std::out_of_range("posição invalida");
    for (int i = index; i < end_; i++) contents[index] = contents[index+1];
    end_--;
}
// Removendo do inicio
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    T aux = contents[0];
    move_back(0);
    size_--;
    return aux;
}
// Removendo do fim
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    end_--;
    size_--;
    return contents[end_+1];
}
// Remover dado
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    pop(find(data));
}
// Removendo na posição
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index<0 || index>end_) throw std::out_of_range("posicao invalida");
    T aux = contents[index];
    move_back(index);
    size_--;
    return aux;
}
// Procurando dado
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    if (empty()) throw std::out_of_range("lista vazia");
    for (int i = 0; i < end_; i++) {
        if (contents[i] == data) return i;
    }
    return -1;
}
// Contem dado
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    return find(data) != -1;
}
// Metdo At
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) if (empty()) throw std::out_of_range("lista vazia");
    if (index<0 || index>end_) throw std::out_of_range("posicao invalida");
    return contents[index];
}
// Metodo Operator
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}
// Insert sorted
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    for (int i = 0; i < end_; i++) {
        if (data < contents[i]) {
            insert(data , i);
            break;
        }
    }
}
