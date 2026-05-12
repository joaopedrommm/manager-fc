#pragma once
#include <stdexcept>
#include <functional>
using namespace std;

// Classe template que implementa uma Lista Ligada genérica
// Template, logo pode armazenar qualquer tipo de dado

template <typename T>
class LinkedList {
private:
    // Classe interna que representa cada nó
    class Node {
    public:
        T     data;
        Node* next;

        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head; // Ponteiro para o primeiro nó
    Node* tail; // Ponteiro para o último nó
    int   sz; // Tamanho da lista

public:
    // Construtor
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    // Destrutor
    ~LinkedList() {
        Node* atual = head;
        while (atual) {
            Node* prox = atual->next;
            delete atual;
            atual = prox;
        }
    }

    // Adiciona um elemento no fim da lista
    void pushBack(const T& val) {
        Node* novo = new Node(val);
        if (tail) tail->next = novo;
        tail = novo;
        if (!head) head = novo;
        sz++;
    }

    // Adiciona um elemento no início da lista
    void pushFront(const T& val) {
        Node* novo = new Node(val);
        novo->next = head;
        head = novo;
        if (!tail) tail = novo;
        sz++;
    }

    // Acessa o elemento da posição i
    const T& get(int i) const {
        if (i < 0 || i >= sz) throw out_of_range("Indice fora do intervalo");
        Node* atual = head;
        for (int j = 0; j < i; j++) atual = atual->next;
        return atual->data;
    }

    // Lê os elementos de forma consecutiva
    void forEach(function<void(const T&)> func) const {
        Node* atual = head;
        while (atual) {
            func(atual->data);
            atual = atual->next;
        }
    }

    // Checa se a lista é vazia
    bool empty() const { return sz == 0; }
    // Retorna o tamanho da lista
    int  size()  const { return sz; }
};