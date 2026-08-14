#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET DON
// Cac thao tac: khoi tao, tao node, them dau, them cuoi,
// them sau node, tim kiem, sua, xoa dau, xoa cuoi,
// xoa theo gia tri, duyet, xoa toan bo.
// ============================================================

struct Node
{
    int info;
    Node *next;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(Node *&head)
{
    head = nullptr;
}

// ------------------------------------------------------------
// 2. Tao Node
// ------------------------------------------------------------
Node* createNode(int x)
{
    Node *p = new Node;
    p->info = x;
    p->next = nullptr;
    return p;
}

// ------------------------------------------------------------
// 3. Duyet danh sach
// ------------------------------------------------------------
void output(Node *head)
{
    Node *p = head;

    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->next;
    }

    cout << endl;
}

// ------------------------------------------------------------
// 4. Dem so Node
// ------------------------------------------------------------
int countNode(Node *head)
{
    int count = 0;

    for (Node *p = head; p != nullptr; p = p->next)
        count++;

    return count;
}

// ------------------------------------------------------------
// 5. Tim Node co gia tri x
// ------------------------------------------------------------
Node* search(Node *head, int x)
{
    Node *p = head;

    while (p != nullptr && p->info != x)
        p = p->next;

    return p;
}

// ------------------------------------------------------------
// 6. Them vao dau
// ------------------------------------------------------------
void addHead(Node *&head, int x)
{
    Node *p = createNode(x);

    p->next = head;
    head = p;
}

// ------------------------------------------------------------
// 7. Them vao cuoi
// ------------------------------------------------------------
void addTail(Node *&head, int x)
{
    Node *p = createNode(x);

    if (head == nullptr)
    {
        head = p;
        return;
    }

    Node *q = head;

    while (q->next != nullptr)
        q = q->next;

    q->next = p;
}

// ------------------------------------------------------------
// 8. Them sau Node co gia tri x
// ------------------------------------------------------------
bool addAfter(Node *head, int x, int value)
{
    Node *q = search(head, value);

    if (q == nullptr)
        return false;

    Node *p = createNode(x);

    p->next = q->next;
    q->next = p;

    return true;
}

// ------------------------------------------------------------
// 9. Sua Node co gia tri cu thanh gia tri moi
// ------------------------------------------------------------
bool update(Node *head, int oldValue, int newValue)
{
    Node *p = search(head, oldValue);

    if (p == nullptr)
        return false;

    p->info = newValue;
    return true;
}

// ------------------------------------------------------------
// 10. Xoa dau
// ------------------------------------------------------------
bool deleteHead(Node *&head)
{
    if (head == nullptr)
        return false;

    Node *p = head;
    head = head->next;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 11. Xoa cuoi
// ------------------------------------------------------------
bool deleteTail(Node *&head)
{
    if (head == nullptr)
        return false;

    // Chi co 1 Node
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return true;
    }

    Node *prev = nullptr;
    Node *tail = head;

    while (tail->next != nullptr)
    {
        prev = tail;
        tail = tail->next;
    }

    prev->next = nullptr;
    delete tail;

    return true;
}

// ------------------------------------------------------------
// 12. Xoa Node dau tien co gia tri x
// ------------------------------------------------------------
bool deleteX(Node *&head, int x)
{
    if (head == nullptr)
        return false;

    // Xoa head
    if (head->info == x)
        return deleteHead(head);

    Node *prev = head;
    Node *p = head->next;

    while (p != nullptr && p->info != x)
    {
        prev = p;
        p = p->next;
    }

    if (p == nullptr)
        return false;

    prev->next = p->next;
    delete p;

    return true;
}

// ------------------------------------------------------------
// 13. Xoa tat ca Node co gia tri x
// ------------------------------------------------------------
int deleteAllX(Node *&head, int x)
{
    int count = 0;

    while (head != nullptr && head->info == x)
    {
        deleteHead(head);
        count++;
    }

    if (head == nullptr)
        return count;

    Node *prev = head;
    Node *p = head->next;

    while (p != nullptr)
    {
        if (p->info == x)
        {
            prev->next = p->next;
            delete p;
            p = prev->next;
            count++;
        }
        else
        {
            prev = p;
            p = p->next;
        }
    }

    return count;
}

// ------------------------------------------------------------
// 14. Xoa toan bo danh sach
// ------------------------------------------------------------
void clear(Node *&head)
{
    while (head != nullptr)
        deleteHead(head);
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    Node *head;
    init(head);

    // Tao danh sach
    addTail(head, 10);
    addTail(head, 20);
    addTail(head, 30);
    addTail(head, 40);

    cout << "Danh sach ban dau: ";
    output(head);

    // Them dau
    addHead(head, 5);

    // Them cuoi
    addTail(head, 50);

    // Them sau Node 20
    addAfter(head, 25, 20);

    // Sua
    update(head, 30, 35);

    cout << "Sau them/sua:      ";
    output(head);

    // Tim kiem
    Node *p = search(head, 25);
    if (p != nullptr)
        cout << "Tim thay: " << p->info << endl;

    // Xoa dau
    deleteHead(head);

    // Xoa cuoi
    deleteTail(head);

    // Xoa Node co gia tri 25
    deleteX(head, 25);

    cout << "Sau khi xoa:       ";
    output(head);

    cout << "So Node: " << countNode(head) << endl;

    // Xoa toan bo
    clear(head);

    cout << "Sau clear:         ";
    output(head);

    return 0;
}