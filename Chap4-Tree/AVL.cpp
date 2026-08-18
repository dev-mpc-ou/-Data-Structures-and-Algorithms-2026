#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

/*
    CAY AVL - CAY NHI PHAN TIM KIEM TU CAN BANG

    Bao gom:
    - Them
    - Tim kiem
    - Xoa
    - NLR, LNR, LRN de quy
    - NLR, LNR, LRN khong de quy
    - BFS Queue DSLK
    - BFS Queue mang vong
    - BFS Queue mang tinh tien
    - Dem node nguyen to
    - 4 truong hop can bang: LL, RR, LR, RL
*/

struct Node {
    int key;
    int height;
    Node *left, *right;
};

int getHeight(Node *root) {
    if (root == nullptr)
        return 0;

    return root->height;
}

int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int x) {
    Node *p = new Node;

    p->key = x;
    p->height = 1;
    p->left = nullptr;
    p->right = nullptr;

    return p;
}

void init(Node* &root) {
    root = nullptr;
}

// ============================================================
// BALANCE FACTOR
// ============================================================

int getBalance(Node *root) {
    if (root == nullptr)
        return 0;

    return getHeight(root->left) - getHeight(root->right);
}

void updateHeight(Node *root) {
    if (root != nullptr)
        root->height =
            1 + maxValue(getHeight(root->left),
                         getHeight(root->right));
}

// ============================================================
// QUAY PHAI
// LL
// ============================================================

Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// ============================================================
// QUAY TRAI
// RR
// ============================================================

Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// ============================================================
// 1. THEM NODE AVL
// ============================================================

Node* insertNode(Node *root, int x) {
    // Them nhu BST
    if (root == nullptr)
        return createNode(x);

    if (x < root->key)
        root->left = insertNode(root->left, x);
    else
        root->right = insertNode(root->right, x);

    updateHeight(root);

    int balance = getBalance(root);

    // LL
    if (balance > 1 && x < root->left->key)
        return rotateRight(root);

    // RR
    if (balance < -1 && x >= root->right->key)
        return rotateLeft(root);

    // LR
    if (balance > 1 && x >= root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if (balance < -1 && x < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// ============================================================
// 2. TIM KIEM
// ============================================================

Node* searchNode(Node *root, int x) {
    if (root == nullptr)
        return nullptr;

    if (root->key == x)
        return root;

    if (x < root->key)
        return searchNode(root->left, x);

    return searchNode(root->right, x);
}

// ============================================================
// TIM NODE NHO NHAT
// ============================================================

Node* findMin(Node *root) {
    while (root != nullptr && root->left != nullptr)
        root = root->left;

    return root;
}

// ============================================================
// 3. XOA NODE AVL
// ============================================================

Node* deleteNode(Node *root, int x) {
    if (root == nullptr)
        return nullptr;

    if (x < root->key) {
        root->left = deleteNode(root->left, x);
    }
    else if (x > root->key) {
        root->right = deleteNode(root->right, x);
    }
    else {
        // 0 hoac 1 con
        if (root->left == nullptr ||
            root->right == nullptr) {

            Node *child =
                (root->left != nullptr)
                ? root->left
                : root->right;

            if (child == nullptr) {
                delete root;
                return nullptr;
            }
            else {
                Node *old = root;
                root = child;
                delete old;
            }
        }
        else {
            // 2 con:
            // lay node nho nhat ben cay con phai
            Node *temp = findMin(root->right);

            root->key = temp->key;

            root->right =
                deleteNode(root->right, temp->key);
        }
    }

    updateHeight(root);

    int balance = getBalance(root);

    // LL
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rotateRight(root);

    // LR
    if (balance > 1 &&
        getBalance(root->left) < 0) {

        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RR
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return rotateLeft(root);

    // RL
    if (balance < -1 &&
        getBalance(root->right) > 0) {

        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// ============================================================
// 4. DUYET DE QUY
// ============================================================

void NLR(Node *root) {
    if (root == nullptr)
        return;

    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node *root) {
    if (root == nullptr)
        return;

    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

void LRN(Node *root) {
    if (root == nullptr)
        return;

    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

// ============================================================
// 5. DUYET KHONG DE QUY
// ============================================================

void NLR_Iterative(Node *root) {
    if (root == nullptr)
        return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node *p = st.top();
        st.pop();

        cout << p->key << " ";

        if (p->right != nullptr)
            st.push(p->right);

        if (p->left != nullptr)
            st.push(p->left);
    }
}

void LNR_Iterative(Node *root) {
    stack<Node*> st;
    Node *p = root;

    while (p != nullptr || !st.empty()) {
        while (p != nullptr) {
            st.push(p);
            p = p->left;
        }

        p = st.top();
        st.pop();

        cout << p->key << " ";

        p = p->right;
    }
}

void LRN_Iterative(Node *root) {
    if (root == nullptr)
        return;

    stack<Node*> st1, st2;

    st1.push(root);

    while (!st1.empty()) {
        Node *p = st1.top();
        st1.pop();

        st2.push(p);

        if (p->left != nullptr)
            st1.push(p->left);

        if (p->right != nullptr)
            st1.push(p->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->key << " ";
        st2.pop();
    }
}

// ============================================================
// 6. QUEUE DSLK
// ============================================================

struct QNode {
    Node *data;
    QNode *next;
};

struct QueueList {
    QNode *front;
    QNode *rear;
};

void initQueueList(QueueList &q) {
    q.front = nullptr;
    q.rear = nullptr;
}

bool emptyQueueList(QueueList q) {
    return q.front == nullptr;
}

void enqueueList(QueueList &q, Node *p) {
    QNode *newNode = new QNode;

    newNode->data = p;
    newNode->next = nullptr;

    if (q.rear == nullptr) {
        q.front = q.rear = newNode;
    }
    else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

Node* dequeueList(QueueList &q) {
    if (emptyQueueList(q))
        return nullptr;

    QNode *temp = q.front;
    Node *p = temp->data;

    q.front = q.front->next;

    if (q.front == nullptr)
        q.rear = nullptr;

    delete temp;
    return p;
}

void BFS_QueueList(Node *root) {
    if (root == nullptr)
        return;

    QueueList q;
    initQueueList(q);

    enqueueList(q, root);

    while (!emptyQueueList(q)) {
        Node *p = dequeueList(q);

        cout << p->key << " ";

        if (p->left != nullptr)
            enqueueList(q, p->left);

        if (p->right != nullptr)
            enqueueList(q, p->right);
    }
}

// ============================================================
// 7. QUEUE DAC - VONG
// ============================================================

#define MAX 100

struct QueueCircular {
    Node* a[MAX];
    int front;
    int rear;
    int count;
};

void initQueueCircular(QueueCircular &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool emptyQueueCircular(QueueCircular q) {
    return q.count == 0;
}

bool fullQueueCircular(QueueCircular q) {
    return q.count == MAX;
}

void enqueueCircular(QueueCircular &q, Node *p) {
    if (fullQueueCircular(q)) {
        cout << "\nQueue vong bi tran!\n";
        return;
    }

    q.rear = (q.rear + 1) % MAX;
    q.a[q.rear] = p;
    q.count++;
}

Node* dequeueCircular(QueueCircular &q) {
    if (emptyQueueCircular(q))
        return nullptr;

    Node *p = q.a[q.front];

    q.front = (q.front + 1) % MAX;
    q.count--;

    return p;
}

void BFS_QueueCircular(Node *root) {
    if (root == nullptr)
        return;

    QueueCircular q;
    initQueueCircular(q);

    enqueueCircular(q, root);

    while (!emptyQueueCircular(q)) {
        Node *p = dequeueCircular(q);

        cout << p->key << " ";

        if (p->left != nullptr)
            enqueueCircular(q, p->left);

        if (p->right != nullptr)
            enqueueCircular(q, p->right);
    }
}

// ============================================================
// 8. QUEUE DAC - TINH TIEN
// ============================================================

struct QueueShift {
    Node* a[MAX];
    int n;
};

void initQueueShift(QueueShift &q) {
    q.n = 0;
}

bool emptyQueueShift(QueueShift q) {
    return q.n == 0;
}

bool fullQueueShift(QueueShift q) {
    return q.n == MAX;
}

void enqueueShift(QueueShift &q, Node *p) {
    if (fullQueueShift(q)) {
        cout << "\nQueue tinh tien bi tran!\n";
        return;
    }

    q.a[q.n++] = p;
}

Node* dequeueShift(QueueShift &q) {
    if (emptyQueueShift(q))
        return nullptr;

    Node *p = q.a[0];

    for (int i = 1; i < q.n; i++)
        q.a[i - 1] = q.a[i];

    q.n--;

    return p;
}

void BFS_QueueShift(Node *root) {
    if (root == nullptr)
        return;

    QueueShift q;
    initQueueShift(q);

    enqueueShift(q, root);

    while (!emptyQueueShift(q)) {
        Node *p = dequeueShift(q);

        cout << p->key << " ";

        if (p->left != nullptr)
            enqueueShift(q, p->left);

        if (p->right != nullptr)
            enqueueShift(q, p->right);
    }
}

// ============================================================
// 9. DEM NODE NGUYEN TO
// ============================================================

bool isPrime(int n) {
    if (n < 2)
        return false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int countPrime(Node *root) {
    if (root == nullptr)
        return 0;

    return (isPrime(root->key) ? 1 : 0)
         + countPrime(root->left)
         + countPrime(root->right);
}

// ============================================================
// GIAI PHONG CAY
// ============================================================

void clearTree(Node* &root) {
    if (root == nullptr)
        return;

    clearTree(root->left);
    clearTree(root->right);

    delete root;
    root = nullptr;
}

// ============================================================
// MENU
// ============================================================

void menu() {
    cout << "\n========================================\n";
    cout << "       CAY AVL - TU CAN BANG\n";
    cout << "========================================\n";
    cout << "1. Them node\n";
    cout << "2. Tim kiem node\n";
    cout << "3. Xoa node\n";
    cout << "4. NLR - De quy\n";
    cout << "5. LNR - De quy\n";
    cout << "6. LRN - De quy\n";
    cout << "7. NLR - Khong de quy\n";
    cout << "8. LNR - Khong de quy\n";
    cout << "9. LRN - Khong de quy\n";
    cout << "10. BFS - Queue DSLK\n";
    cout << "11. BFS - Queue mang vong\n";
    cout << "12. BFS - Queue mang tinh tien\n";
    cout << "13. Dem node nguyen to\n";
    cout << "14. Xem Balance Factor cua cac node\n";
    cout << "15. Xuat tat ca cac kieu duyet\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
}

void printBalance(Node *root) {
    if (root == nullptr)
        return;

    printBalance(root->left);

    cout << "Node " << root->key
         << " | Height = " << root->height
         << " | BF = " << getBalance(root) << "\n";

    printBalance(root->right);
}

int main() {
    Node *root;
    init(root);

    int choice, x;

    do {
        menu();
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Nhap gia tri x: ";
            cin >> x;

            root = insertNode(root, x);

            cout << "Them thanh cong va da tu can bang!\n";
            break;

        case 2: {
            cout << "Nhap gia tri can tim: ";
            cin >> x;

            Node *p = searchNode(root, x);

            if (p != nullptr)
                cout << "Tim thay node " << x << ".\n";
            else
                cout << "Khong tim thay node " << x << ".\n";
            break;
        }

        case 3:
            cout << "Nhap gia tri can xoa: ";
            cin >> x;

            if (searchNode(root, x) != nullptr) {
                root = deleteNode(root, x);
                cout << "Xoa thanh cong va da tu can bang!\n";
            }
            else {
                cout << "Khong tim thay node can xoa.\n";
            }
            break;

        case 4:
            cout << "NLR: ";
            NLR(root);
            cout << "\n";
            break;

        case 5:
            cout << "LNR: ";
            LNR(root);
            cout << "\n";
            break;

        case 6:
            cout << "LRN: ";
            LRN(root);
            cout << "\n";
            break;

        case 7:
            cout << "NLR khong de quy: ";
            NLR_Iterative(root);
            cout << "\n";
            break;

        case 8:
            cout << "LNR khong de quy: ";
            LNR_Iterative(root);
            cout << "\n";
            break;

        case 9:
            cout << "LRN khong de quy: ";
            LRN_Iterative(root);
            cout << "\n";
            break;

        case 10:
            cout << "BFS - Queue DSLK: ";
            BFS_QueueList(root);
            cout << "\n";
            break;

        case 11:
            cout << "BFS - Queue mang vong: ";
            BFS_QueueCircular(root);
            cout << "\n";
            break;

        case 12:
            cout << "BFS - Queue mang tinh tien: ";
            BFS_QueueShift(root);
            cout << "\n";
            break;

        case 13:
            cout << "So node chua gia tri nguyen to: "
                 << countPrime(root) << "\n";
            break;

        case 14:
            if (root == nullptr)
                cout << "Cay rong!\n";
            else
                printBalance(root);
            break;

        case 15:
            cout << "NLR de quy:        ";
            NLR(root);
            cout << "\n";

            cout << "LNR de quy:        ";
            LNR(root);
            cout << "\n";

            cout << "LRN de quy:        ";
            LRN(root);
            cout << "\n";

            cout << "NLR khong de quy:  ";
            NLR_Iterative(root);
            cout << "\n";

            cout << "LNR khong de quy:  ";
            LNR_Iterative(root);
            cout << "\n";

            cout << "LRN khong de quy:  ";
            LRN_Iterative(root);
            cout << "\n";

            cout << "BFS Queue DSLK:    ";
            BFS_QueueList(root);
            cout << "\n";

            cout << "BFS Queue vong:    ";
            BFS_QueueCircular(root);
            cout << "\n";

            cout << "BFS Queue tinh tien:";
            BFS_QueueShift(root);
            cout << "\n";
            break;

        case 0:
            cout << "Ket thuc!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    clearTree(root);

    return 0;
}
