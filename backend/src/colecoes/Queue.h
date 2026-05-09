#pragma once
#include <stdexcept>

template <typename T>
class Queue {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int sz;

public:
    Queue() : head(nullptr), tail(nullptr), sz(0) {}

    ~Queue() {
        while (!empty()) dequeue();
    }

    void enqueue(const T& val) {
        Node* no = new Node(val);
        if (tail) tail->next = no;
        tail = no;
        if (!head) head = no;
        sz++;
    }

    T dequeue() {
        if (empty()) throw std::runtime_error("Queue vazia");
        T val = head->data;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        sz--;
        return val;
    }

    T& front() {
        if (empty()) throw std::runtime_error("Queue vazia");
        return head->data;
    }

    bool empty() const { return sz == 0; }
    int size()   const { return sz; }
};