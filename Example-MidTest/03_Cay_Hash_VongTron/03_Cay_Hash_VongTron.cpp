#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// ============================================================
// 1. SO NGUYEN TO
// ============================================================

bool isPrime(int n)
{
    if (n < 2) return false;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}

// ============================================================
// 2. BST
// ============================================================

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int x)
{
    Node* p = new Node;
    p->data = x;
    p->left = p->right = nullptr;
    return p;
}

Node* insertBST(Node* root, int x)
{
    if (root == nullptr)
        return createNode(x);

    if (x < root->data)
        root->left = insertBST(root->left, x);
    else if (x > root->data)
        root->right = insertBST(root->right, x);

    return root;
}

Node* searchBST(Node* root, int x)
{
    if (root == nullptr || root->data == x)
        return root;

    if (x < root->data)
        return searchBST(root->left, x);

    return searchBST(root->right, x);
}

Node* minNode(Node* root)
{
    Node* p = root;

    while (p && p->left != nullptr)
        p = p->left;

    return p;
}

Node* deleteBST(Node* root, int x)
{
    if (root == nullptr)
        return nullptr;

    if (x < root->data)
        root->left = deleteBST(root->left, x);
    else if (x > root->data)
        root->right = deleteBST(root->right, x);
    else
    {
        if (root->left == nullptr)
        {
            Node* p = root->right;
            delete root;
            return p;
        }

        if (root->right == nullptr)
        {
            Node* p = root->left;
            delete root;
            return p;
        }

        Node* p = minNode(root->right);
        root->data = p->data;
        root->right = deleteBST(root->right, p->data);
    }

    return root;
}

void NLR(Node* root)
{
    if (!root) return;

    cout << root->data << ' ';
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node* root)
{
    if (!root) return;

    LNR(root->left);
    cout << root->data << ' ';
    LNR(root->right);
}

void LRN(Node* root)
{
    if (!root) return;

    LRN(root->left);
    LRN(root->right);
    cout << root->data << ' ';
}

// NLR khong de quy
void NLRNonRecursive(Node* root)
{
    if (!root) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty())
    {
        Node* p = st.top();
        st.pop();

        cout << p->data << ' ';

        if (p->right) st.push(p->right);
        if (p->left) st.push(p->left);
    }
}

// LNR khong de quy
void LNRNonRecursive(Node* root)
{
    stack<Node*> st;
    Node* p = root;

    while (p != nullptr || !st.empty())
    {
        while (p != nullptr)
        {
            st.push(p);
            p = p->left;
        }

        p = st.top();
        st.pop();

        cout << p->data << ' ';
        p = p->right;
    }
}

// LRN khong de quy - dung 2 stack
void LRNNonRecursive(Node* root)
{
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        Node* p = s1.top();
        s1.pop();

        s2.push(p);

        if (p->left) s1.push(p->left);
        if (p->right) s1.push(p->right);
    }

    while (!s2.empty())
    {
        cout << s2.top()->data << ' ';
        s2.pop();
    }
}

void BFS(Node* root)
{
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* p = q.front();
        q.pop();

        cout << p->data << ' ';

        if (p->left) q.push(p->left);
        if (p->right) q.push(p->right);
    }
}

int countPrime(Node* root)
{
    if (!root) return 0;

    return (isPrime(root->data) ? 1 : 0)
         + countPrime(root->left)
         + countPrime(root->right);
}

void clearTree(Node*& root)
{
    if (!root) return;

    clearTree(root->left);
    clearTree(root->right);

    delete root;
    root = nullptr;
}

void loadTree(Node*& root, const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Khong mo duoc file!\n";
        return;
    }

    int x;

    while (fin >> x)
        root = insertBST(root, x);

    fin.close();
}

// ============================================================
// 3. HASH - SEPARATE CHAINING
// ============================================================

const int M = 11;

struct HNode
{
    int key;
    HNode* next;
};

HNode* createHNode(int x)
{
    HNode* p = new HNode;
    p->key = x;
    p->next = nullptr;
    return p;
}

int hashFunc(int x)
{
    int h = x % M;
    if (h < 0) h += M;
    return h;
}

void initHash(HNode* heads[])
{
    for (int i = 0; i < M; i++)
        heads[i] = nullptr;
}

void insertHash(HNode* heads[], int x)
{
    int idx = hashFunc(x);
    HNode* p = createHNode(x);

    p->next = heads[idx];
    heads[idx] = p;
}

bool searchHash(HNode* heads[], int x)
{
    HNode* p = heads[hashFunc(x)];

    while (p)
    {
        if (p->key == x) return true;
        p = p->next;
    }

    return false;
}

bool deleteHash(HNode* heads[], int x)
{
    int idx = hashFunc(x);
    HNode* p = heads[idx];
    HNode* prev = nullptr;

    while (p)
    {
        if (p->key == x)
        {
            if (prev) prev->next = p->next;
            else heads[idx] = p->next;

            delete p;
            return true;
        }

        prev = p;
        p = p->next;
    }

    return false;
}

void outputHash(HNode* heads[])
{
    cout << "\n=== SEPARATE CHAINING ===\n";

    for (int i = 0; i < M; i++)
    {
        cout << "[" << i << "]: ";

        HNode* p = heads[i];

        if (!p)
        {
            cout << "NULL";
        }

        while (p)
        {
            cout << p->key;

            if (p->next) cout << " -> ";

            p = p->next;
        }

        cout << '\n';
    }
}

void loadHash(HNode* heads[], const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Khong mo duoc file!\n";
        return;
    }

    int x;

    while (fin >> x)
        insertHash(heads, x);

    fin.close();
}

// ============================================================
// 4. KIEM TRA HOAN VI
// ============================================================

bool isAnagram(const string& a, const string& b)
{
    if (a.length() != b.length())
        return false;

    int count[256] = {};

    for (unsigned char c : a)
        count[c]++;

    for (unsigned char c : b)
        count[c]--;

    for (int i = 0; i < 256; i++)
        if (count[i] != 0)
            return false;

    return true;
}

// ============================================================
// 5. TRO CHOI VONG TRON - LOAI KHI SO DEM LA NGUYEN TO
// ============================================================

struct Player
{
    int id;
    Player* next;
};

Player* createPlayer(int id)
{
    Player* p = new Player;
    p->id = id;
    p->next = nullptr;
    return p;
}

void playCircle(int n)
{
    if (n <= 0)
    {
        cout << "n phai > 0\n";
        return;
    }

    Player* head = nullptr;
    Player* tail = nullptr;

    for (int i = 1; i <= n; i++)
    {
        Player* p = createPlayer(i);

        if (!head)
            head = tail = p;
        else
        {
            tail->next = p;
            tail = p;
        }
    }

    tail->next = head;

    Player* current = head;
    Player* prev = tail;

    int count = 1;

    cout << "\nThu tu bi loai: ";

    while (current->next != current)
    {
        if (isPrime(count))
        {
            cout << current->id << ' ';

            prev->next = current->next;

            Player* del = current;
            current = current->next;

            delete del;

            // Người kế tiếp bắt đầu đếm lại từ 1
            count = 1;
        }
        else
        {
            prev = current;
            current = current->next;
            count++;
        }
    }

    cout << "\nNguoi chien thang: " << current->id << endl;

    delete current;
}

// ============================================================
// MENU BST
// ============================================================

void menuBST(Node*& root)
{
    int choice;

    do
    {
        cout << "\n========== BST ==========\n";
        cout << "1. Them node\n";
        cout << "2. Tim node\n";
        cout << "3. Xoa node\n";
        cout << "4. NLR de quy\n";
        cout << "5. LNR de quy\n";
        cout << "6. LRN de quy\n";
        cout << "7. NLR khong de quy\n";
        cout << "8. LNR khong de quy\n";
        cout << "9. LRN khong de quy\n";
        cout << "10. BFS Queue\n";
        cout << "11. Dem node nguyen to\n";
        cout << "12. Doc tu data_tree.txt\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x; cin >> x;
            root = insertBST(root, x);
            break;
        }

        case 2:
        {
            int x; cin >> x;
            cout << (searchBST(root, x) ? "Tim thay\n" : "Khong tim thay\n");
            break;
        }

        case 3:
        {
            int x; cin >> x;
            root = deleteBST(root, x);
            break;
        }

        case 4: NLR(root); cout << '\n'; break;
        case 5: LNR(root); cout << '\n'; break;
        case 6: LRN(root); cout << '\n'; break;
        case 7: NLRNonRecursive(root); cout << '\n'; break;
        case 8: LNRNonRecursive(root); cout << '\n'; break;
        case 9: LRNNonRecursive(root); cout << '\n'; break;
        case 10: BFS(root); cout << '\n'; break;
        case 11: cout << "So node nguyen to = " << countPrime(root) << '\n'; break;
        case 12: loadTree(root, "data_tree.txt"); break;
        case 0: break;
        default: cout << "Khong hop le!\n";
        }

    } while (choice != 0);
}

// ============================================================
// MENU HASH
// ============================================================

void menuHash()
{
    HNode* heads[M];
    initHash(heads);

    int choice;

    do
    {
        cout << "\n========== HASH SEPARATE CHAINING ==========\n";
        cout << "1. Them\n";
        cout << "2. Xoa\n";
        cout << "3. Tim\n";
        cout << "4. Xuat\n";
        cout << "5. Doc data_hash.txt\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x; cin >> x;
            insertHash(heads, x);
            break;
        }

        case 2:
        {
            int x; cin >> x;
            cout << (deleteHash(heads, x) ? "Da xoa\n" : "Khong tim thay\n");
            break;
        }

        case 3:
        {
            int x; cin >> x;
            cout << (searchHash(heads, x) ? "Tim thay\n" : "Khong tim thay\n");
            break;
        }

        case 4:
            outputHash(heads);
            break;

        case 5:
            loadHash(heads, "data_hash.txt");
            break;

        case 0:
            break;

        default:
            cout << "Khong hop le!\n";
        }

    } while (choice != 0);

    for (int i = 0; i < M; i++)
    {
        HNode* p = heads[i];

        while (p)
        {
            HNode* del = p;
            p = p->next;
            delete del;
        }
    }
}

// ============================================================
// MAIN
// ============================================================

int main()
{
    Node* root = nullptr;

    int choice;

    do
    {
        cout << "\n=========================================\n";
        cout << " ON THI GIUA KY - CAY / HASH / VONG TRON\n";
        cout << "=========================================\n";
        cout << "1. BST\n";
        cout << "2. Hash Separate Chaining\n";
        cout << "3. Kiem tra hoan vi 2 chuoi\n";
        cout << "4. Tro choi vong tron\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            menuBST(root);
            break;

        case 2:
            menuHash();
            break;

        case 3:
        {
            string a, b;

            cout << "Chuoi 1: ";
            cin >> a;

            cout << "Chuoi 2: ";
            cin >> b;

            cout << (isAnagram(a, b)
                ? "La hoan vi\n"
                : "Khong phai hoan vi\n");

            break;
        }

        case 4:
        {
            int n;
            cout << "n = ";
            cin >> n;
            playCircle(n);
            break;
        }

        case 0:
            break;

        default:
            cout << "Khong hop le!\n";
        }

    } while (choice != 0);

    clearTree(root);

    return 0;
}
