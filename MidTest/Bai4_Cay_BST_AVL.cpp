#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

// ============================================================
// DEMO: BAI 4 - CAY NHI PHAN TIM KIEM (BST) + MO RONG AVL
//
// Phan BST:
// - Them, tim kiem, xoa
// - Duyet de quy: NLR / LNR / LRN
// - Duyet khong de quy: NLR / LNR / LRN
// - BFS: Queue DSLK, Queue mang vong, Queue mang tinh tien
// - Dem node nguyen to
//
// Phan AVL:
// - Them BST + cap nhat height + can bang
// - Tim kiem, xoa + can bang
// - Cac cach duyet (dung lai ham cua BST)
//
// Dung struct BSTree / AVLTree de quan ly goc cay,
// giup truyen tham so de dang hon.
// ============================================================

struct Node
{
    int key;
    int height;
    Node *left, *right;
};

// Quan ly cay BST
struct BSTree
{
    Node *root;
};

// Quan ly cay AVL
struct AVLTree
{
    Node *root;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(BSTree &t)
{
    t.root = nullptr;
}

void init(AVLTree &t)
{
    t.root = nullptr;
}

// ------------------------------------------------------------
// 2. Tao Node
// ------------------------------------------------------------
Node* createNode(int x)
{
    Node *p = new Node;
    p->key = x;
    p->height = 1;
    p->left = p->right = nullptr;
    return p;
}

// ============================================================
// CAY NHI PHAN TIM KIEM (BST)
// ============================================================

// ------------------------------------------------------------
// 3. Them x vao cay (de quy tren Node)
// ------------------------------------------------------------
Node* insertNode(Node *root, int x)
{
    if (root == nullptr)
        return createNode(x);

    if (x < root->key)
        root->left = insertNode(root->left, x);
    else
        root->right = insertNode(root->right, x);

    return root;
}

// Ham goi qua struct BSTree
void insertBST(BSTree &t, int x)
{
    t.root = insertNode(t.root, x);
}

// ------------------------------------------------------------
// 4. Tim node co gia tri x
// ------------------------------------------------------------
Node* searchNode(Node *root, int x)
{
    if (root == nullptr || root->key == x)
        return root;

    if (x < root->key)
        return searchNode(root->left, x);

    return searchNode(root->right, x);
}

Node* searchBST(BSTree &t, int x)
{
    return searchNode(t.root, x);
}

Node* searchAVL(AVLTree &t, int x)
{
    return searchNode(t.root, x);
}

// ------------------------------------------------------------
// 5. Tim node nho nhat
// ------------------------------------------------------------
Node* findMin(Node *root)
{
    while (root && root->left)
        root = root->left;

    return root;
}

// ------------------------------------------------------------
// 6. Xoa x ra khoi cay (de quy tren Node)
// ------------------------------------------------------------
Node* deleteNode(Node *root, int x)
{
    if (root == nullptr)
        return nullptr;

    if (x < root->key)
        root->left = deleteNode(root->left, x);
    else if (x > root->key)
        root->right = deleteNode(root->right, x);
    else
    {
        if (root->left == nullptr)
        {
            Node *p = root->right;
            delete root;
            return p;
        }

        if (root->right == nullptr)
        {
            Node *p = root->left;
            delete root;
            return p;
        }

        Node *p = findMin(root->right);
        root->key = p->key;
        root->right = deleteNode(root->right, p->key);
    }

    return root;
}

// Ham goi qua struct BSTree
void deleteBST(BSTree &t, int x)
{
    t.root = deleteNode(t.root, x);
}

// ============================================================
// DUYET DE QUY: NLR / LNR / LRN
// ============================================================

// ------------------------------------------------------------
// 7. Duyet NLR (Node - Left - Right)
// ------------------------------------------------------------
void NLR(Node *root)
{
    if (!root) return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

// ------------------------------------------------------------
// 8. Duyet LNR (Left - Node - Right)
// ------------------------------------------------------------
void LNR(Node *root)
{
    if (!root) return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

// ------------------------------------------------------------
// 9. Duyet LRN (Left - Right - Node)
// ------------------------------------------------------------
void LRN(Node *root)
{
    if (!root) return;

    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

// ============================================================
// DUYET KHONG DE QUY
// ============================================================

// ------------------------------------------------------------
// 10. NLR khong de quy (dung stack)
// ------------------------------------------------------------
void NLR_Iterative(Node *root)
{
    if (!root) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty())
    {
        Node *p = st.top();
        st.pop();

        cout << p->key << " ";

        if (p->right) st.push(p->right);
        if (p->left) st.push(p->left);
    }
}

// ------------------------------------------------------------
// 11. LNR khong de quy (dung stack)
// ------------------------------------------------------------
void LNR_Iterative(Node *root)
{
    stack<Node*> st;
    Node *p = root;

    while (p || !st.empty())
    {
        while (p)
        {
            st.push(p);
            p = p->left;
        }

        p = st.top();
        st.pop();

        cout << p->key << " ";
        p = p->right;
    }
}

// ------------------------------------------------------------
// 12. LRN khong de quy (dung 2 stack)
// ------------------------------------------------------------
void LRN_Iterative(Node *root)
{
    if (!root) return;

    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty())
    {
        Node *p = st1.top();
        st1.pop();

        st2.push(p);

        if (p->left) st1.push(p->left);
        if (p->right) st1.push(p->right);
    }

    while (!st2.empty())
    {
        cout << st2.top()->key << " ";
        st2.pop();
    }
}

// ============================================================
// BFS - QUEUE DSLK
// ============================================================

struct QNode
{
    Node *data;
    QNode *next;
};

struct QueueList
{
    QNode *front;
    QNode *rear;
};

void initQueue(QueueList &q)
{
    q.front = q.rear = nullptr;
}

bool empty(QueueList q)
{
    return q.front == nullptr;
}

void enqueue(QueueList &q, Node *p)
{
    QNode *x = new QNode{p, nullptr};

    if (!q.rear)
        q.front = q.rear = x;
    else
    {
        q.rear->next = x;
        q.rear = x;
    }
}

Node* dequeue(QueueList &q)
{
    if (empty(q))
        return nullptr;

    QNode *x = q.front;
    Node *p = x->data;

    q.front = q.front->next;

    if (!q.front)
        q.rear = nullptr;

    delete x;
    return p;
}

void BFS_List(Node *root)
{
    if (!root) return;

    QueueList q;
    initQueue(q);
    enqueue(q, root);

    while (!empty(q))
    {
        Node *p = dequeue(q);

        cout << p->key << " ";

        if (p->left) enqueue(q, p->left);
        if (p->right) enqueue(q, p->right);
    }
}

// ============================================================
// BFS - QUEUE MANG VONG
// ============================================================

#define MAX 100

struct QueueCircular
{
    Node *a[MAX];
    int front, rear, count;
};

void initCircular(QueueCircular &q)
{
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool empty(QueueCircular q)
{
    return q.count == 0;
}

bool full(QueueCircular q)
{
    return q.count == MAX;
}

void enqueue(QueueCircular &q, Node *p)
{
    if (full(q))
        return;

    q.rear = (q.rear + 1) % MAX;
    q.a[q.rear] = p;
    q.count++;
}

Node* dequeue(QueueCircular &q)
{
    if (empty(q))
        return nullptr;

    Node *p = q.a[q.front];
    q.front = (q.front + 1) % MAX;
    q.count--;

    return p;
}

void BFS_Circular(Node *root)
{
    if (!root) return;

    QueueCircular q;
    initCircular(q);
    enqueue(q, root);

    while (!empty(q))
    {
        Node *p = dequeue(q);

        cout << p->key << " ";

        if (p->left) enqueue(q, p->left);
        if (p->right) enqueue(q, p->right);
    }
}

// ============================================================
// BFS - QUEUE MANG TINH TIEN
// ============================================================

struct QueueShift
{
    Node *a[MAX];
    int n;
};

void initShift(QueueShift &q)
{
    q.n = 0;
}

bool empty(QueueShift q)
{
    return q.n == 0;
}

bool full(QueueShift q)
{
    return q.n == MAX;
}

void enqueue(QueueShift &q, Node *p)
{
    if (full(q))
        return;

    q.a[q.n++] = p;
}

Node* dequeue(QueueShift &q)
{
    if (empty(q))
        return nullptr;

    Node *p = q.a[0];

    for (int i = 1; i < q.n; i++)
        q.a[i - 1] = q.a[i];

    q.n--;
    return p;
}

void BFS_Shift(Node *root)
{
    if (!root) return;

    QueueShift q;
    initShift(q);
    enqueue(q, root);

    while (!empty(q))
    {
        Node *p = dequeue(q);

        cout << p->key << " ";

        if (p->left) enqueue(q, p->left);
        if (p->right) enqueue(q, p->right);
    }
}

// ============================================================
// DEM SO NODE NGUYEN TO
// ============================================================

// ------------------------------------------------------------
// 13. Kiem tra so nguyen to
// ------------------------------------------------------------
bool isPrime(int x)
{
    if (x < 2)
        return false;

    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;

    return true;
}

// ------------------------------------------------------------
// 14. Dem so node nguyen to trong cay
// ------------------------------------------------------------
int countPrime(Node *root)
{
    if (!root)
        return 0;

    return (isPrime(root->key) ? 1 : 0)
         + countPrime(root->left)
         + countPrime(root->right);
}

// ============================================================
// CAY AVL (TU CAN BANG)
// ============================================================

// ------------------------------------------------------------
// 15. Chieu cao cua cay
// ------------------------------------------------------------
int height(Node *root)
{
    return root ? root->height : 0;
}

// ------------------------------------------------------------
// 16. Cap nhat chieu cao
// ------------------------------------------------------------
void updateHeight(Node *root)
{
    if (root)
        root->height = 1 + max(height(root->left),
                               height(root->right));
}

// ------------------------------------------------------------
// 17. He so can bang
// ------------------------------------------------------------
int balanceFactor(Node *root)
{
    return root ? height(root->left) - height(root->right) : 0;
}

// ------------------------------------------------------------
// 18. Xoay phai / xoay trai
// ------------------------------------------------------------
Node* rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// ------------------------------------------------------------
// 19. Them x vao cay AVL (de quy tren Node)
// ------------------------------------------------------------
Node* avlInsertNode(Node *root, int x)
{
    if (!root)
        return createNode(x);

    if (x < root->key)
        root->left = avlInsertNode(root->left, x);
    else
        root->right = avlInsertNode(root->right, x);

    updateHeight(root);

    int bf = balanceFactor(root);

    // LL
    if (bf > 1 && x < root->left->key)
        return rotateRight(root);

    // RR
    if (bf < -1 && x >= root->right->key)
        return rotateLeft(root);

    // LR
    if (bf > 1 && x >= root->left->key)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if (bf < -1 && x < root->right->key)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Ham goi qua struct AVLTree
void insertAVL(AVLTree &t, int x)
{
    t.root = avlInsertNode(t.root, x);
}

// ------------------------------------------------------------
// 20. Xoa x ra khoi cay AVL (de quy tren Node)
// ------------------------------------------------------------
Node* avlDeleteNode(Node *root, int x)
{
    if (!root)
        return nullptr;

    if (x < root->key)
        root->left = avlDeleteNode(root->left, x);
    else if (x > root->key)
        root->right = avlDeleteNode(root->right, x);
    else
    {
        if (!root->left || !root->right)
        {
            Node *child = root->left ? root->left : root->right;

            if (!child)
            {
                delete root;
                return nullptr;
            }

            Node *old = root;
            root = child;
            delete old;
        }
        else
        {
            Node *p = findMin(root->right);
            root->key = p->key;
            root->right = avlDeleteNode(root->right, p->key);
        }
    }

    updateHeight(root);

    int bf = balanceFactor(root);

    // LL
    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);

    // LR
    if (bf > 1 && balanceFactor(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RR
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // RL
    if (bf < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Ham goi qua struct AVLTree
void deleteAVL(AVLTree &t, int x)
{
    t.root = avlDeleteNode(t.root, x);
}

// ============================================================
// XOA CAY
// ============================================================

// ------------------------------------------------------------
// 21. Xoa toan bo cay (de quy tren Node)
// ------------------------------------------------------------
void clearTree(Node *&root)
{
    if (!root)
        return;

    clearTree(root->left);
    clearTree(root->right);

    delete root;
    root = nullptr;
}

void clear(BSTree &t)
{
    clearTree(t.root);
}

void clear(AVLTree &t)
{
    clearTree(t.root);
}

// ============================================================
// XEM BALANCE FACTOR
// ============================================================

void printBalance(Node *root)
{
    if (!root) return;

    printBalance(root->left);

    cout << "Node " << root->key
         << " | Height = " << root->height
         << " | BF = " << balanceFactor(root) << "\n";

    printBalance(root->right);
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n================ BAI 4 ================\n";
    cout << "1. BST - Them\n";
    cout << "2. BST - Tim kiem\n";
    cout << "3. BST - Xoa\n";
    cout << "4. NLR de quy\n";
    cout << "5. LNR de quy\n";
    cout << "6. LRN de quy\n";
    cout << "7. NLR khong de quy\n";
    cout << "8. LNR khong de quy\n";
    cout << "9. LRN khong de quy\n";
    cout << "10. BFS Queue DSLK\n";
    cout << "11. BFS Queue mang vong\n";
    cout << "12. BFS Queue mang tinh tien\n";
    cout << "13. Dem node nguyen to\n";
    cout << "14. AVL - Them\n";
    cout << "15. AVL - Tim kiem\n";
    cout << "16. AVL - Xoa\n";
    cout << "17. Xem Balance Factor\n";
    cout << "0. Thoat\n";
    cout << "=======================================\n";
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    // Tach rieng 2 cay de tranh nham:
    // BST dung bst, AVL dung avl.
    BSTree bst;
    AVLTree avl;

    init(bst);
    init(avl);

    int choice, x;

    do
    {
        menu();
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        // ==================== BST ====================

        case 1:
            cout << "BST - x = ";
            cin >> x;
            insertBST(bst, x);
            cout << "Da them vao BST.\n";
            break;

        case 2:
            cout << "BST - x = ";
            cin >> x;
            cout << (searchBST(bst, x)
                    ? "Tim thay.\n"
                    : "Khong tim thay.\n");
            break;

        case 3:
            cout << "BST - x = ";
            cin >> x;
            deleteBST(bst, x);
            cout << "Da xu ly xoa BST.\n";
            break;

        case 4:
            cout << "BST NLR: ";
            NLR(bst.root);
            cout << "\n";
            break;

        case 5:
            cout << "BST LNR: ";
            LNR(bst.root);
            cout << "\n";
            break;

        case 6:
            cout << "BST LRN: ";
            LRN(bst.root);
            cout << "\n";
            break;

        case 7:
            cout << "BST NLR khong de quy: ";
            NLR_Iterative(bst.root);
            cout << "\n";
            break;

        case 8:
            cout << "BST LNR khong de quy: ";
            LNR_Iterative(bst.root);
            cout << "\n";
            break;

        case 9:
            cout << "BST LRN khong de quy: ";
            LRN_Iterative(bst.root);
            cout << "\n";
            break;

        case 10:
            cout << "BST BFS Queue DSLK: ";
            BFS_List(bst.root);
            cout << "\n";
            break;

        case 11:
            cout << "BST BFS Queue mang vong: ";
            BFS_Circular(bst.root);
            cout << "\n";
            break;

        case 12:
            cout << "BST BFS Queue mang tinh tien: ";
            BFS_Shift(bst.root);
            cout << "\n";
            break;

        case 13:
            cout << "BST - so node nguyen to = "
                 << countPrime(bst.root) << "\n";
            break;

        // ==================== AVL ====================

        case 14:
            cout << "AVL - x = ";
            cin >> x;
            insertAVL(avl, x);
            cout << "Da them vao AVL va tu can bang.\n";
            break;

        case 15:
            cout << "AVL - x = ";
            cin >> x;
            cout << (searchAVL(avl, x)
                    ? "Tim thay.\n"
                    : "Khong tim thay.\n");
            break;

        case 16:
            cout << "AVL - x = ";
            cin >> x;
            deleteAVL(avl, x);
            cout << "Da xoa AVL va can bang lai.\n";
            break;

        case 17:
            if (avl.root == nullptr)
                cout << "AVL rong.\n";
            else
                printBalance(avl.root);
            break;

        case 0:
            cout << "Ket thuc.\n";
            break;

        default:
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);

    clear(bst);
    clear(avl);

    return 0;
}
