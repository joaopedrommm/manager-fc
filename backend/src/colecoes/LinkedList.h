#pragma once
#include <stdexcept>
#include <functional>

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T     data;
        Node* next;

        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int   sz;

public:
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    ~LinkedList() {
        Node* atual = head;
        while (atual) {
            Node* prox = atual->next;
            delete atual;
            atual = prox;
        }
    }

    void pushBack(const T& val) {
        Node* novo = new Node(val);
        if (tail) tail->next = novo;
        tail = novo;
        if (!head) head = novo;
        sz++;
    }

    void pushFront(const T& val) {
        Node* novo = new Node(val);
        novo->next = head;
        head = novo;
        if (!tail) tail = novo;
        sz++;
    }

    const T& get(int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Indice fora do intervalo");
        Node* atual = head;
        for (int j = 0; j < i; j++) atual = atual->next;
        return atual->data;
    }

    void forEach(std::function<void(const T&)> func) const {
        Node* atual = head;
        while (atual) {
            func(atual->data);
            atual = atual->next;
        }
    }

    bool empty() const { return sz == 0; }
    int  size()  const { return sz; }
};