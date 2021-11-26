#include "Node.h"

template<typename T>
class Stack {
private:
    Node<T> *top;
public:
    Stack();

    void push(T data);  // apilar
    T pop();            // desapilar
    T peek();           // ver tope
    bool isEmpty() { return top == nullptr; };
};

template<typename T>
Stack<T>::Stack() {
    top = nullptr;
}

template<typename T>
void Stack<T>::push(T data) {
    auto *newNode = new Node<T>(data, top);
    top = newNode;
}

template<typename T>
T Stack<T>::pop() {
    if (top == nullptr)
        throw 404;

    T toReturn = top->getData();
    auto toDelete = top;
    top = top->getNext();
    delete toDelete;
    return toReturn;
}

template<typename T>
T Stack<T>::peek() {
    if (top == nullptr)
        throw 404;
    return top->getData();
}

