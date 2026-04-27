#pragma once
#include <functional>

// -----------------------------------------------------------------------
// Árvore AVL genérica
// Recebe um comparador customizável para definir a ordenação
// Uso no Manager FC: ordenar times pela regra do Brasileirao
// -----------------------------------------------------------------------
template <typename T>
class AVL {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int sz;
    std::function<int(const T&, const T&)> cmp;
    // cmp(a, b): retorna < 0 se a < b, 0 se iguais, > 0 se a > b

    // ---- Utilitários internos ----

    int height(Node* n) const {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node* n) {
        if (!n) return;
        int lh = height(n->left);
        int rh = height(n->right);
        n->height = 1 + (lh > rh ? lh : rh);
    }

    // ---- Rotações ----

    Node* rotateRight(Node* y) {
        Node* x  = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left  = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y  = x->right;
        Node* T2 = y->left;
        y->left  = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        // Caso esquerda-esquerda
        if (bf > 1 && balanceFactor(n->left) >= 0)
            return rotateRight(n);

        // Caso esquerda-direita
        if (bf > 1 && balanceFactor(n->left) < 0) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        // Caso direita-direita
        if (bf < -1 && balanceFactor(n->right) <= 0)
            return rotateLeft(n);

        // Caso direita-esquerda
        if (bf < -1 && balanceFactor(n->right) > 0) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }

        return n;
    }

    // ---- Inserção ----

    Node* insert(Node* n, const T& val) {
        if (!n) { sz++; return new Node(val); }

        int c = cmp(val, n->data);
        if (c < 0)      n->left  = insert(n->left,  val);
        else if (c > 0) n->right = insert(n->right, val);
        else            n->data  = val; // atualiza se já existe (mesmo time)

        return balance(n);
    }

    // ---- Remoção ----

    Node* minNode(Node* n) {
        return n->left ? minNode(n->left) : n;
    }

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

    // ---- Percurso em ordem (do maior para o menor = decrescente) ----

    void inorderDesc(Node* n, std::function<void(const T&)> visit) const {
        if (!n) return;
        inorderDesc(n->right, visit);
        visit(n->data);
        inorderDesc(n->left, visit);
    }

    // ---- Destruição ----

    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    // Construtor: recebe o comparador
    AVL(std::function<int(const T&, const T&)> comparador)
        : root(nullptr), sz(0), cmp(comparador) {}

    ~AVL() { destroy(root); }

    void insert(const T& val)   { root = insert(root, val); }
    void remove(const T& val)   { root = remove(root, val); }
    int  size()  const          { return sz; }
    bool empty() const          { return sz == 0; }

    // Percorre do maior para o menor (classificacao do 1o ao último)
    void forEach(std::function<void(const T&)> visit) const {
        inorderDesc(root, visit);
    }
};