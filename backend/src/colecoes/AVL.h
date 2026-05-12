#pragma once
#include <functional>

// Classe template para implementar uma Árvore genérica
// Template, logo pode ser usada para qualquer tipo de dado

template <typename T>
class AVL {
private:
    // Classe interna que representa um nó da árvore
    class Node {
    public:
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int sz;
    std::function<int(const T&, const T&)> cmp;

    // Altura de um nó
    int height(Node* n) const {
        return n ? n->height : 0;
    }

    // Calcula a diferença de altura entre a sub-árvore esquerda e direita
    int balanceFactor(Node* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // Atualiza a altura do nó com base nas alturas dos seus dois filhos
    void updateHeight(Node* n) {
        if (!n) return;
        int lh = height(n->left);
        int rh = height(n->right);
        n->height = 1 + (lh > rh ? lh : rh);
    }

    // Rotação para direita
    Node* rotateRight(Node* y) {
        Node* x  = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left  = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Rotação para esquerda
    Node* rotateLeft(Node* x) {
        Node* y  = x->right;
        Node* T2 = y->left;
        y->left  = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Balanceamento do nó se ele tiver desbalanceado
    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1 && balanceFactor(n->left) >= 0)
            return rotateRight(n);
        if (bf > 1 && balanceFactor(n->left) < 0) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1 && balanceFactor(n->right) <= 0)
            return rotateLeft(n);
        if (bf < -1 && balanceFactor(n->right) > 0) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    // Insere um novo nó na árvore (usa da recursão para encontrar a posição correta)
    Node* insert(Node* n, const T& val) {
        if (!n) { sz++; return new Node(val); }
        int c = cmp(val, n->data);
        if (c < 0)      n->left  = insert(n->left,  val);
        else if (c > 0) n->right = insert(n->right, val);
        else            n->data  = val;
        return balance(n);
    }

    // Encontra o nó com o menor valor a partir de um nó dado
    Node* minNode(Node* n) {
        return n->left ? minNode(n->left) : n;
    }

    // Remove um nó da árvore e rebalanceia, se necessário
    Node* remove(Node* n, const T& val) {
        if (!n) return nullptr;
        int c = cmp(val, n->data);
        if      (c < 0) n->left  = remove(n->left,  val);
        else if (c > 0) n->right = remove(n->right, val);
        else {
            if (!n->left || !n->right) {
                Node* tmp = n->left ? n->left : n->right;
                delete n;
                sz--;
                return tmp;
            }
            Node* successor = minNode(n->right);
            n->data  = successor->data;
            n->right = remove(n->right, successor->data);
        }
        return balance(n);
    }

    // Percurso in-order (direita, centro, esquerda)
    void inorderDesc(Node* n, std::function<void(const T&)> visit) const {
        if (!n) return;
        inorderDesc(n->right, visit);
        visit(n->data);
        inorderDesc(n->left, visit);
    }

    // Destrói a árvore para liberar memória
    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    AVL(std::function<int(const T&, const T&)> comparador)
        : root(nullptr), sz(0), cmp(comparador) {}

    ~AVL() { destroy(root); }

    void insert(const T& val)   { root = insert(root, val); }
    void remove(const T& val)   { root = remove(root, val); }
    int  size()  const          { return sz; }
    bool empty() const          { return sz == 0; }

    void forEach(std::function<void(const T&)> visit) const {
        inorderDesc(root, visit);
    }
};