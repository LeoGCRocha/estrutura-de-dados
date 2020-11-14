/ Copyright [2020] <Leonardo Rocha>

#include <stdexcept>

namespace structures {

//! LinkedQueue
template<typename T>
class LinkedQueue {
 public:
    //! construtor
    LinkedQueue();

    //! destrutor
    ~LinkedQueue();

    //! limpar
    void clear();

    //! enfileirar
    void enqueue(const T& data);

    //! desenfileirar
    T dequeue();

    //! primeiro dado
    T& front() const;

    //! último dado
    T& back() const;

    //! fila vazia
    bool empty() const;

    //! tamanho
    std::size_t size() const;

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
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures
// Construtor
template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {  //
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}
// Destrutor
template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}
// Clear
template<typename T>
void structures::LinkedQueue<T>::clear() {  // funcionando
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
// Empty
template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size_ == 0;
}
// Size
template<typename T>
std::size_t  structures::LinkedQueue<T>::size() const {
    return size_;
}
// Ultimo
template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) throw std::out_of_range("fila vazia");
    return tail->data();
}
// Front
template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) throw std::out_of_range("fila vazia");
    return head->data();
}
// Enqueue
template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {  // ou problema aqui
    Node *b = new Node(data, nullptr);
    if (empty()) {
        head = b;
    } else {
        tail->next(b);
    }
    tail = b;
    size_++;
}
// Dequeue
template<typename T>
T structures::LinkedQueue<T>::dequeue() {  // problema aq
    if (empty()) throw std::out_of_range("fila vazia");
    Node *b = head;
    T data = b->data();
    head = b->next();
    if (size() == 1) tail = nullptr;
    size_--;
    delete b;
    return data;
}

