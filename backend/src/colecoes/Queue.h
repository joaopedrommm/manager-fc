#pragma once
#include <stdexcept>
using namespace std;

// Classe template que implementa uma Fila genérica
// Template, logo pode armazenar qualquer tipo de dado
template <typename T>
class Queue {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head; // Ponteiro para o primeiro nó
    Node* tail; // Ponteiro para o último nó
    int sz; // Tamanho da fila

public:
    // Construtor
    Queue() : head(nullptr), tail(nullptr), sz(0) {}
    // Destrutor
    ~Queue() {
        while (!empty()) dequeue();
    }
    // Adiciona um elemento
    void enqueue(const T& val) {
        Node* no = new Node(val);
        if (tail) tail->next = no;
        tail = no;
        if (!head) head = no;
        sz++;
    }
    // Remove um elemento e retorna o primeiro elemento
    T dequeue() {
        if (empty()) throw runtime_error("Queue vazia");
        T val = head->data;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        sz--;
        return val;
    }
    // Retorna o primeiro elemento
    T& front() {
        if (empty()) throw runtime_error("Queue vazia");
        return head->data;
    }
    // Checa se a fila é vazia
    bool empty() const { return sz == 0; }
    // Retorna o tamanho da fila
    int size()   const { return sz; }
};