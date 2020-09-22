//! Copyright [2020] <Copyright ...>

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

//! ...
template<typename T>
class ArrayList {
 public:
    //! ...
    ArrayList();
    //! ...
    explicit ArrayList(std::size_t max_size);
    //! ...
    ~ArrayList();

    //! ...
    void clear();
    //! ...
    void push_back(const T& data);
    //! ...
    void push_front(const T& data);
    //! ...
    void insert(const T& data, std::size_t index);
    //! ...
    void set_size(std::size_t size);
    //! ...
    void insert_sorted(const T& data);
    //! ...
    T pop(std::size_t index);
    //! ...
    T pop_back();
    //! ...
    T pop_front();
    //! ...
    void remove(const T& data);
    //! ...
    bool full() const;
    //! ...
    bool empty() const;
    //! ...
    bool contains(const T& data) const;
    //! ...
    std::size_t find(const T& data) const;
    //! ...
    std::size_t size() const;
    //! ...
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};
//-------------------------------------

//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();

    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
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
// set size
template<typename T>
void structures::ArrayList<T>::set_size(std::size_t size) {
    size_ = size;
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
    while (cont >= 0 && (contents[cont] > data)) {  // !!!
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
// Inicio: Metodos ArrayListString
// Metodo DESTRUTOR
structures::ArrayListString::~ArrayListString() {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        delete [] ArrayList::operator[](i);
    }
}
// Metodo CLEAR
void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        delete [] ArrayList::operator[](i);
    }
    ArrayList::set_size(0);
}
// INSERT
void structures::ArrayListString::insert(const char *data, std::size_t index) {
    if (ArrayList::full()) throw std::out_of_range("Lista cheia.");
    int tamanhoString = strlen(data) + 1;
    char *newdata = new char[tamanhoString];
    snprintf(newdata, tamanhoString, "%s", data);
    newdata[tamanhoString-1] = '\0';
    ArrayList::insert(newdata, index);
}
// PUSH FRONT
void structures::ArrayListString::push_front(const char *data) {
    if (ArrayList::full()) throw std::out_of_range("Lista cheia.");
    int tamanhoString = strlen(data) + 1;
    char *newdata = new char[tamanhoString];
    snprintf(newdata, tamanhoString, "%s", data);
    newdata[tamanhoString-1] = '\0';
    ArrayList::push_front(newdata);
}
// PUSH BACK
void structures::ArrayListString::push_back(const char *data) {
    if (ArrayList::full()) throw std::out_of_range("Lista cheia.");
    int tamanhoString = strlen(data) + 1;
    char *newdata = new char[tamanhoString];
    snprintf(newdata, tamanhoString, "%s", data);
    newdata[tamanhoString-1] = '\0';
    ArrayList::push_back(newdata);
}
// POP
char * structures::ArrayListString::pop(std::size_t index) {
    if (index >= ArrayList::size()) {
        throw std::out_of_range("posição invalida.");
    } else if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    char *point = operator[](index);
    // delete [] ArrayList::operator[](index);
    ArrayList::pop(index);
    return point;
}
// POP BACK
char * structures::ArrayListString::pop_back() {
    char *point = this->pop(ArrayList::size()-1);
    return point;
}
/// POP FRONT
char * structures::ArrayListString::pop_front() {
    char *point = this->pop(0);
    return point;
}
// CONTAIINS
bool structures::ArrayListString::contains(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return true;
        }
    }
    return false;
}
// FIND
std::size_t structures::ArrayListString::find(const char *data) {
    for (std::size_t i = 0; i < ArrayList::size(); i++) {
        if (!strcmp(ArrayList::at(i), data)) {
            return i;
        }
    }
    return ArrayList::size();
}
// INSERT SORTED
void structures::ArrayListString::insert_sorted(const char *data) {
    int cont = ArrayList::size() - 1;
    while (cont >= 0 && (strcmp(ArrayList::at(cont), data) > 0)) {
        cont--;
    }
    this->insert(data, cont+1);
}
// REMOVE
void structures::ArrayListString::remove(const char *data) {
    int pos = this->find(data);
    this->pop(pos);
}
