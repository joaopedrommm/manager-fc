#pragma once
#include <stdexcept>
#include <functional>

// =============================================================================
// LinkedList.h  —  Lista encadeada simples genérica (template).
//
// CONCEITO DE ESTRUTURA DE DADOS: Lista Encadeada
//   Ao contrário de um array, a lista encadeada não precisa de memória
//   contígua. Cada elemento (nó) guarda o dado e um ponteiro para o próximo.
//   Vantagem: inserção no final em O(1), sem realocação de memória.
//
// CONCEITO C++: TEMPLATE
//   O parâmetro <T> torna a estrutura genérica — funciona com int, string,
//   ponteiros para objetos, etc.
//
// USO NO MANAGER FC:
//   Guardar o histórico de partidas disputadas durante a temporada.
// =============================================================================

template <typename T>
class LinkedList {
private:
    // --- Nó interno da lista ---
    struct Node {
        T     data;   // o dado armazenado
        Node* next;   // ponteiro para o próximo nó

        // Construtor do nó
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head; // primeiro nó da lista
    Node* tail; // último nó (mantido para inserção O(1) no final)
    int   sz;   // tamanho atual da lista

public:
    // --- Construtor ---
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    // --- Destrutor: percorre a lista e libera cada nó ---
    ~LinkedList() {
        Node* atual = head;
        while (atual) {
            Node* prox = atual->next;
            delete atual;
            atual = prox;
        }
    }

    // -------------------------------------------------------------------------
    // pushBack: insere um novo elemento no FINAL da lista — O(1)
    // -------------------------------------------------------------------------
    void pushBack(const T& val) {
        Node* novo = new Node(val);
        if (tail) tail->next = novo;
        tail = novo;
        if (!head) head = novo;
        sz++;
    }

    // -------------------------------------------------------------------------
    // pushFront: insere um novo elemento no INÍCIO da lista — O(1)
    // -------------------------------------------------------------------------
    void pushFront(const T& val) {
        Node* novo = new Node(val);
        novo->next = head;
        head = novo;
        if (!tail) tail = novo;
        sz++;
    }

    // -------------------------------------------------------------------------
    // get: acessa o elemento na posição i — O(n)
    // -------------------------------------------------------------------------
    const T& get(int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Indice fora do intervalo");
        Node* atual = head;
        for (int j = 0; j < i; j++) atual = atual->next;
        return atual->data;
    }

    // -------------------------------------------------------------------------
    // forEach: percorre toda a lista aplicando uma função em cada elemento
    // Útil para exibir o histórico sem expor o ponteiro interno.
    // -------------------------------------------------------------------------
    void forEach(std::function<void(const T&)> func) const {
        Node* atual = head;
        while (atual) {
            func(atual->data);
            atual = atual->next;
        }
    }

    // --- Consultas ---
    bool empty() const { return sz == 0; }
    int  size()  const { return sz; }
};
