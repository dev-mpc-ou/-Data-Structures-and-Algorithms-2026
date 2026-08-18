#include <iostream>
using namespace std;

const int M = 7;

struct Node
{
    int data;
    Node* next;
};

int hashFunc(int key)
{
    int h = key % M;
    if (h < 0) h += M;
    return h;
}

Node* createNode(int x)
{
    Node* p = new Node;
    p->data = x;
    p->next = nullptr;
    return p;
}

void initHashTable(Node* heads[])
{
    for (int i = 0; i < M; i++)
        heads[i] = nullptr;
}

void addTail(Node*& head, int x)
{
    Node* p = createNode(x);

    if (head == nullptr)
    {
        head = p;
        return;
    }

    Node* q = head;
    while (q->next != nullptr)
        q = q->next;

    q->next = p;
}

bool searchList(Node* head, int x)
{
    while (head != nullptr)
    {
        if (head->data == x)
            return true;

        head = head->next;
    }

    return false;
}

void outputHashTable(Node* heads[])
{
    cout << "\n=== SEPARATE CHAINING ===\n";

    for (int i = 0; i < M; i++)
    {
        cout << "Bucket [" << i << "]: ";

        if (heads[i] == nullptr)
        {
            cout << "NULL\n";
            continue;
        }

        Node* p = heads[i];

        while (p != nullptr)
        {
            cout << p->data;

            if (p->next != nullptr)
                cout << " -> ";

            p = p->next;
        }

        cout << endl;
    }
}

void deleteList(Node*& head)
{
    while (head != nullptr)
    {
        Node* p = head;
        head = head->next;
        delete p;
    }
}

int main()
{
    Node* heads[M];
    initHashTable(heads);

    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << " SEPARATE CHAINING\n";
        cout << "==============================\n";
        cout << "1. Them phan tu\n";
        cout << "2. Xuat bang\n";
        cout << "3. Tim kiem\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x;
            cout << "Nhap x: ";
            cin >> x;

            addTail(heads[hashFunc(x)], x);

            cout << "Da them " << x
                 << " vao Bucket "
                 << hashFunc(x) << endl;
            break;
        }

        case 2:
            outputHashTable(heads);
            break;

        case 3:
        {
            int x;
            cout << "Nhap x can tim: ";
            cin >> x;

            if (searchList(heads[hashFunc(x)], x))
                cout << "Tim thay " << x << endl;
            else
                cout << "Khong tim thay " << x << endl;

            break;
        }

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    for (int i = 0; i < M; i++)
        deleteList(heads[i]);

    return 0;
}
