#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET DON
// Cac thao tac: khoi tao, tao node, them dau, them cuoi,
// them sau node, tim kiem, sua, xoa dau, xoa cuoi,
// xoa theo gia tri, duyet, xoa toan bo.
//
// Su dung struct SinglyLinkedList de quan ly head va tail,
// giup viec truyen tham so de dang hon.
// ============================================================

struct Node
{
    int info;
    Node *next;
};

// Quan ly danh sach lien ket don
struct SinglyLinkedList
{
    Node *head;
    Node *tail;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(SinglyLinkedList &l)
{
    l.head = nullptr;
    l.tail = nullptr;
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
void output(const SinglyLinkedList &l)
{
    Node *p = l.head;

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
int countNode(const SinglyLinkedList &l)
{
    int count = 0;

    for (Node *p = l.head; p != nullptr; p = p->next)
        count++;

    return count;
}

// ------------------------------------------------------------
// 5. Tim Node co gia tri x
// ------------------------------------------------------------
Node* search(const SinglyLinkedList &l, int x)
{
    Node *p = l.head;

    while (p != nullptr && p->info != x)
        p = p->next;

    return p;
}

// ------------------------------------------------------------
// 6. Them vao dau
// ------------------------------------------------------------
void addHead(SinglyLinkedList &l, int x)
{
    Node *p = createNode(x);

    p->next = l.head;
    l.head = p;

    if (l.tail == nullptr)
        l.tail = p;
}

// ------------------------------------------------------------
// 7. Them vao cuoi
// ------------------------------------------------------------
void addTail(SinglyLinkedList &l, int x)
{
    Node *p = createNode(x);

    if (l.tail == nullptr)
    {
        l.head = p;
        l.tail = p;
        return;
    }

    l.tail->next = p;
    l.tail = p;
}

// ------------------------------------------------------------
// 8. Them sau Node co gia tri x
// ------------------------------------------------------------
bool addAfter(SinglyLinkedList &l, int x, int value)
{
    Node *q = search(l, value);

    if (q == nullptr)
        return false;

    Node *p = createNode(x);

    p->next = q->next;
    q->next = p;

    // Neu them sau tail thi cap nhat tail
    if (q == l.tail)
        l.tail = p;

    return true;
}

// ------------------------------------------------------------
// 9. Sua Node co gia tri cu thanh gia tri moi
// ------------------------------------------------------------
bool update(const SinglyLinkedList &l, int oldValue, int newValue)
{
    Node *p = search(l, oldValue);

    if (p == nullptr)
        return false;

    p->info = newValue;
    return true;
}

// ------------------------------------------------------------
// 10. Xoa dau
// ------------------------------------------------------------
bool deleteHead(SinglyLinkedList &l)
{
    if (l.head == nullptr)
        return false;

    Node *p = l.head;
    l.head = l.head->next;

    if (l.head == nullptr)
        l.tail = nullptr;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 11. Xoa cuoi
// ------------------------------------------------------------
bool deleteTail(SinglyLinkedList &l)
{
    if (l.head == nullptr)
        return false;

    // Chi co 1 Node
    if (l.head == l.tail)
    {
        delete l.head;
        l.head = nullptr;
        l.tail = nullptr;
        return true;
    }

    Node *prev = nullptr;
    Node *p = l.head;

    while (p->next != nullptr)
    {
        prev = p;
        p = p->next;
    }

    prev->next = nullptr;
    l.tail = prev;
    delete p;

    return true;
}

// ------------------------------------------------------------
// 12. Xoa Node dau tien co gia tri x
// ------------------------------------------------------------
bool deleteX(SinglyLinkedList &l, int x)
{
    if (l.head == nullptr)
        return false;

    // Xoa head
    if (l.head->info == x)
        return deleteHead(l);

    Node *prev = l.head;
    Node *p = l.head->next;

    while (p != nullptr && p->info != x)
    {
        prev = p;
        p = p->next;
    }

    if (p == nullptr)
        return false;

    prev->next = p->next;

    // Neu xoa tail thi cap nhat tail
    if (p == l.tail)
        l.tail = prev;

    delete p;

    return true;
}

// ------------------------------------------------------------
// 13. Xoa tat ca Node co gia tri x
// ------------------------------------------------------------
int deleteAllX(SinglyLinkedList &l, int x)
{
    int count = 0;

    while (l.head != nullptr && l.head->info == x)
    {
        deleteHead(l);
        count++;
    }

    if (l.head == nullptr)
        return count;

    Node *prev = l.head;
    Node *p = l.head->next;

    while (p != nullptr)
    {
        if (p->info == x)
        {
            prev->next = p->next;

            // Neu xoa tail thi cap nhat tail
            if (p == l.tail)
                l.tail = prev;

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
void clear(SinglyLinkedList &l)
{
    while (l.head != nullptr)
        deleteHead(l);
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    SinglyLinkedList l;
    init(l);

    // Tao danh sach
    addTail(l, 10);
    addTail(l, 20);
    addTail(l, 30);
    addTail(l, 40);

    cout << "Danh sach ban dau: ";
    output(l);

    // Them dau
    addHead(l, 5);

    // Them cuoi
    addTail(l, 50);

    // Them sau Node 20
    addAfter(l, 25, 20);

    // Sua
    update(l, 30, 35);

    cout << "Sau them/sua:      ";
    output(l);

    // Tim kiem
    Node *p = search(l, 25);
    if (p != nullptr)
        cout << "Tim thay: " << p->info << endl;

    // Xoa dau
    deleteHead(l);

    // Xoa cuoi
    deleteTail(l);

    // Xoa Node co gia tri 25
    deleteX(l, 25);

    cout << "Sau khi xoa:       ";
    output(l);

    cout << "So Node: " << countNode(l) << endl;

    // Xoa toan bo
    clear(l);

    cout << "Sau clear:         ";
    output(l);

    return 0;
}