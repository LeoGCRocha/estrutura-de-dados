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
    void insert_sorted(const T& data);
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

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures
#endif

// Construtor
template<typename T>
structures::ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}
// Destrutor
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}
// Construtor com atributos
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}
// Metodo limpar lista
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}
// Verificar se lista esta cheia
template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}
// Verificar se lista esta vazia
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}
// Retorna tamanho atual da lista
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}
// Retorna o tamanho maximo da lista
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}
// At, Operator, Const at, Const operator
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    } else {
        return contents[index];
    }
}
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}
template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
// Find
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size_;
}
// Contains
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    if (empty()) return false;  // !!!
    for (int i = 0; i < size_; i++) {
        if (data == contents[i]) return true;
    }
    return false;
}
// Pop front
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) throw std::out_of_range("lista vazia");
    return contents[--size_];
}
//  Pop X
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("lista vazia");
    if (index >= size_) {
        throw std::out_of_range("posicao invalida");
    }
    T aux = contents[index];  // estava antes do if !!!
    for (int i = index; i < size_ - 1; i++) {  // estava 'i--'
        contents[i] = contents[i+1];
    }
    size_--;
    return aux;
}
// Pop front
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) throw std::out_of_range("lista vazia");
    return pop(0);
}
// Push front
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    for (int i = size_; i > 0; i--) {  // estava 'size_ - 1' !!!
        contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}
// Push back
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    contents[size_++] = data;
}
// Insert
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) throw std::out_of_range("lista cheia");
    if (index > size_) {
        throw std::out_of_range("posicao invalida");
    }
    for (std::size_t i = size_; i > index; i--) {
        contents[i] = contents[i-1];
    }
    contents[index] = data;
    size_++;
}
// Insert sorted
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) throw std::out_of_range("lista cheia");
    int cont = size_ - 1;
    while (cont >= 0 && (contents[cont] > data)) {  
        contents[cont + 1] = contents[cont];
        cont--;
    }
    contents[cont + 1] = data;
    size_++;
}
// Removendo um elemento
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (!contains(data)) return;
    int i = find(data);
    int j;
    for (j = i; j < size_ - 1; j++) {
        contents[j] = contents[j + 1];
    }
    size_--;
}
