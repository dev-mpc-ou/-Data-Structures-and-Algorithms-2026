#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET KEP
// Cac thao tac: khoi tao, tao node, them dau, them cuoi,
// them sau node, them truoc node, tim kiem, sua,
// xoa dau, xoa cuoi, xoa theo gia tri, duyet 2 chieu,
// xoa toan bo.
// ============================================================

struct Node
{
    int info;
    Node *next;
    Node *previous;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(Node *&head, Node *&tail)
{
    head = nullptr;
    tail = nullptr;
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
void outputForward(Node *head)
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
// 4. Duyet tu cuoi ve dau
// ------------------------------------------------------------
void outputBackward(Node *tail)
{
    Node *p = tail;

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
int countNode(Node *head)
{
    int count = 0;

    for (Node *p = head; p != nullptr; p = p->next)
        count++;

    return count;
}

// ------------------------------------------------------------
// 6. Tim Node co gia tri x
// ------------------------------------------------------------
Node* search(Node *head, int x)
{
    Node *p = head;

    while (p != nullptr && p->info != x)
        p = p->next;

    return p;
}

// ------------------------------------------------------------
// 7. Them vao dau
// ------------------------------------------------------------
void addHead(Node *&head, Node *&tail, int x)
{
    Node *p = createNode(x);

    p->next = head;

    if (head != nullptr)
        head->previous = p;
    else
        tail = p;

    head = p;
}

// ------------------------------------------------------------
// 8. Them vao cuoi
// ------------------------------------------------------------
void addTail(Node *&head, Node *&tail, int x)
{
    Node *p = createNode(x);

    p->previous = tail;

    if (tail != nullptr)
        tail->next = p;
    else
        head = p;

    tail = p;
}

// ------------------------------------------------------------
// 9. Them sau Node co gia tri value
// ------------------------------------------------------------
bool addAfter(Node *&head, Node *&tail, int x, int value)
{
    Node *q = search(head, value);

    if (q == nullptr)
        return false;

    // Them sau tail
    if (q == tail)
    {
        addTail(head, tail, x);
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
bool addBefore(Node *&head, Node *&tail, int x, int value)
{
    Node *q = search(head, value);

    if (q == nullptr)
        return false;

    // Them truoc head
    if (q == head)
    {
        addHead(head, tail, x);
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
bool update(Node *head, int oldValue, int newValue)
{
    Node *p = search(head, oldValue);

    if (p == nullptr)
        return false;

    p->info = newValue;
    return true;
}

// ------------------------------------------------------------
// 12. Xoa dau
// ------------------------------------------------------------
bool deleteHead(Node *&head, Node *&tail)
{
    if (head == nullptr)
        return false;

    Node *p = head;

    head = head->next;

    if (head != nullptr)
        head->previous = nullptr;
    else
        tail = nullptr;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 13. Xoa cuoi
// ------------------------------------------------------------
bool deleteTail(Node *&head, Node *&tail)
{
    if (tail == nullptr)
        return false;

    Node *p = tail;

    tail = tail->previous;

    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;

    delete p;
    return true;
}

// ------------------------------------------------------------
// 14. Xoa Node dau tien co gia tri x
// ------------------------------------------------------------
bool deleteX(Node *&head, Node *&tail, int x)
{
    Node *q = search(head, x);

    if (q == nullptr)
        return false;

    if (q == head)
        return deleteHead(head, tail);

    if (q == tail)
        return deleteTail(head, tail);

    q->previous->next = q->next;
    q->next->previous = q->previous;

    delete q;

    return true;
}

// ------------------------------------------------------------
// 15. Xoa tat ca Node co gia tri x
// ------------------------------------------------------------
int deleteAllX(Node *&head, Node *&tail, int x)
{
    int count = 0;
    Node *p = head;

    while (p != nullptr)
    {
        Node *next = p->next;

        if (p->info == x)
        {
            if (p == head)
                deleteHead(head, tail);
            else if (p == tail)
                deleteTail(head, tail);
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
void clear(Node *&head, Node *&tail)
{
    while (head != nullptr)
        deleteHead(head, tail);
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    Node *head, *tail;
    init(head, tail);

    // Tao danh sach
    addTail(head, tail, 10);
    addTail(head, tail, 20);
    addTail(head, tail, 30);
    addTail(head, tail, 40);

    cout << "Duyet tu dau: ";
    outputForward(head);

    cout << "Duyet tu cuoi: ";
    outputBackward(tail);

    // Them dau/cuoi
    addHead(head, tail, 5);
    addTail(head, tail, 50);

    // Them truoc/sau
    addAfter(head, tail, 25, 20);
    addBefore(head, tail, 15, 20);

    // Sua
    update(head, 30, 35);

    cout << "Sau them/sua: ";
    outputForward(head);

    // Tim kiem
    Node *p = search(head, 25);
    if (p != nullptr)
        cout << "Tim thay: " << p->info << endl;

    // Xoa dau/cuoi
    deleteHead(head, tail);
    deleteTail(head, tail);

    // Xoa theo gia tri
    deleteX(head, tail, 25);

    cout << "Sau khi xoa: ";
    outputForward(head);

    cout << "So Node: " << countNode(head) << endl;

    // Xoa toan bo
    clear(head, tail);

    cout << "Sau clear: ";
    outputForward(head);

    return 0;
}