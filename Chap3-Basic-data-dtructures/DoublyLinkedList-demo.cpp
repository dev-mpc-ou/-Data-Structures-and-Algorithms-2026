#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET KEP
// Cac thao tac: khoi tao, tao node, them dau, them cuoi,
// them sau node, them truoc node, tim kiem, sua,
// xoa dau, xoa cuoi, xoa theo gia tri, duyet 2 chieu,
// xoa toan bo.
//
// Su dung struct DoublyLinkedList de quan ly head va tail,
// giup viec truyen tham so de dang hon.
// ============================================================

struct Node
{
    int info;
    Node *next;
    Node *previous;
};

// Quan ly danh sach lien ket kep
struct DoublyLinkedList
{
    Node *head;
    Node *tail;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(DoublyLinkedList &l)
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
    p->previous = nullptr;

    return p;
}

// ------------------------------------------------------------
// 3. Duyet tu dau den cuoi
// ------------------------------------------------------------
void outputForward(const DoublyLinkedList &l)
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
// 4. Duyet tu cuoi ve dau
// ------------------------------------------------------------
void outputBackward(const DoublyLinkedList &l)
{
    Node *p = l.tail;

    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->previous;
    }

    cout << endl;
}

// ------------------------------------------------------------
// 5. Dem so Node
// ------------------------------------------------------------
int countNode(const DoublyLinkedList &l)
{
    int count = 0;

    for (Node *p = l.head; p != nullptr; p = p->next)
        count++;

    return count;
}

// ------------------------------------------------------------
// 6. Tim Node co gia tri x
// ------------------------------------------------------------
Node* search(const DoublyLinkedList &l, int x)
{
    Node *p = l.head;

    while (p != nullptr && p->info != x)
        p = p->next;

    return p;
}

// ------------------------------------------------------------
// 7. Them vao dau
// ------------------------------------------------------------
void addHead(DoublyLinkedList &l, int x)
{
    Node *p = createNode(x);

    p->next = l.head;

    if (l.head != nullptr)
        l.head->previous = p;
    else
        l.tail = p;

    l.head = p;
}

// ------------------------------------------------------------
// 8. Them vao cuoi
// ------------------------------------------------------------
void addTail(DoublyLinkedList &l, int x)
{
    Node *p = createNode(x);

    p->previous = l.tail;

    if (l.tail != nullptr)
        l.tail->next = p;
    else
        l.head = p;

    l.tail = p;
}

// ------------------------------------------------------------
// 9. Them sau Node co gia tri value
// ------------------------------------------------------------
bool addAfter(DoublyLinkedList &l, int x, int value)
{
    Node *q = search(l, value);

    if (q == nullptr)
        return false;

    // Them sau tail
    if (q == l.tail)
    {
        addTail(l, x);
        return true;
    }

    Node *p = createNode(x);

    p->next = q->next;
    p->previous = q;

    q->next->previous = p;
    q->next = p;

    return true;
}

// ------------------------------------------------------------
// 10. Them truoc Node co gia tri value
// ------------------------------------------------------------
bool addBefore(DoublyLinkedList &l, int x, int value)
{
    Node *q = search(l, value);

    if (q == nullptr)
        return false;

    // Them truoc head
    if (q == l.head)
    {
        addHead(l, x);
        return true;
    }

    Node *p = createNode(x);

    p->previous = q->previous;
    p->next = q;

    q->previous->next = p;
    q->previous = p;

    return true;
}

// ------------------------------------------------------------
// 11. Sua Node co gia tri cu thanh gia tri moi
// ------------------------------------------------------------
bool update(const DoublyLinkedList &l, int oldValue, int newValue)
{
    Node *p = search(l, oldValue);

    if (p == nullptr)
        return false;

    p->info = newValue;
    return true;
}

// ------------------------------------------------------------
// 12. Xoa dau
// ------------------------------------------------------------
bool deleteHead(DoublyLinkedList &l)
{
    if (l.head == nullptr)
        return false;

    Node *p = l.head;

    l.head = l.head->next;

    if (l.head != nullptr)
        l.head->previous = nullptr;
    else
        l.tail = nullptr;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 13. Xoa cuoi
// ------------------------------------------------------------
bool deleteTail(DoublyLinkedList &l)
{
    if (l.tail == nullptr)
        return false;

    Node *p = l.tail;

    l.tail = l.tail->previous;

    if (l.tail != nullptr)
        l.tail->next = nullptr;
    else
        l.head = nullptr;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 14. Xoa Node dau tien co gia tri x
// ------------------------------------------------------------
bool deleteX(DoublyLinkedList &l, int x)
{
    Node *q = search(l, x);

    if (q == nullptr)
        return false;

    if (q == l.head)
        return deleteHead(l);

    if (q == l.tail)
        return deleteTail(l);

    q->previous->next = q->next;
    q->next->previous = q->previous;

    delete q;

    return true;
}

// ------------------------------------------------------------
// 15. Xoa tat ca Node co gia tri x
// ------------------------------------------------------------
int deleteAllX(DoublyLinkedList &l, int x)
{
    int count = 0;
    Node *p = l.head;

    while (p != nullptr)
    {
        Node *next = p->next;

        if (p->info == x)
        {
            if (p == l.head)
                deleteHead(l);
            else if (p == l.tail)
                deleteTail(l);
            else
            {
                p->previous->next = p->next;
                p->next->previous = p->previous;
                delete p;
            }

            count++;
        }

        p = next;
    }

    return count;
}

// ------------------------------------------------------------
// 16. Xoa toan bo danh sach
// ------------------------------------------------------------
void clear(DoublyLinkedList &l)
{
    while (l.head != nullptr)
        deleteHead(l);
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    DoublyLinkedList l;
    init(l);

    // Tao danh sach
    addTail(l, 10);
    addTail(l, 20);
    addTail(l, 30);
    addTail(l, 40);

    cout << "Duyet tu dau: ";
    outputForward(l);

    cout << "Duyet tu cuoi: ";
    outputBackward(l);

    // Them dau/cuoi
    addHead(l, 5);
    addTail(l, 50);

    // Them truoc/sau
    addAfter(l, 25, 20);
    addBefore(l, 15, 20);

    // Sua
    update(l, 30, 35);

    cout << "Sau them/sua: ";
    outputForward(l);

    // Tim kiem
    Node *p = search(l, 25);
    if (p != nullptr)
        cout << "Tim thay: " << p->info << endl;

    // Xoa dau/cuoi
    deleteHead(l);
    deleteTail(l);

    // Xoa theo gia tri
    deleteX(l, 25);

    cout << "Sau khi xoa: ";
    outputForward(l);

    cout << "So Node: " << countNode(l) << endl;

    // Xoa toan bo
    clear(l);

    cout << "Sau clear: ";
    outputForward(l);

    return 0;
}