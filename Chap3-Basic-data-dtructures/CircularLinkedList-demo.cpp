#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET VONG (DSLK don vong)
// Dac diem: node cuoi tro ve node dau (tail->next = head)
// Cac thao tac: khoi tao, tao node, them dau, them cuoi,
// them sau node, tim kiem, sua, xoa dau, xoa cuoi,
// xoa theo gia tri, duyet, xoa toan bo.
//
// Su dung struct CircularLinkedList de quan ly head va tail,
// giup viec truyen tham so de dang hon.
// ============================================================

struct Node
{
    int info;
    Node *next;
};

// Quan ly danh sach lien ket vong
struct CircularLinkedList
{
    Node *head;
    Node *tail;
};

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(CircularLinkedList &l)
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
// 3. Duyet danh sach (di tu head den khi quay lai head)
// ------------------------------------------------------------
void output(const CircularLinkedList &l)
{
    if (l.head == nullptr)
    {
        cout << endl;
        return;
    }

    Node *p = l.head;

    do
    {
        cout << p->info << " ";
        p = p->next;
    } while (p != l.head);

    cout << endl;
}

// ------------------------------------------------------------
// 4. Dem so Node
// ------------------------------------------------------------
int countNode(const CircularLinkedList &l)
{
    if (l.head == nullptr)
        return 0;

    int count = 0;
    Node *p = l.head;

    do
    {
        count++;
        p = p->next;
    } while (p != l.head);

    return count;
}

// ------------------------------------------------------------
// 5. Tim Node co gia tri x
// ------------------------------------------------------------
Node* search(const CircularLinkedList &l, int x)
{
    if (l.head == nullptr)
        return nullptr;

    Node *p = l.head;

    do
    {
        if (p->info == x)
            return p;

        p = p->next;
    } while (p != l.head);

    return nullptr;
}

// ------------------------------------------------------------
// 6. Them vao dau
// ------------------------------------------------------------
void addHead(CircularLinkedList &l, int x)
{
    Node *p = createNode(x);

    // Danh sach rong
    if (l.head == nullptr)
    {
        l.head = p;
        l.tail = p;
        p->next = p;            // tu tro vao chinh no
        return;
    }

    p->next = l.head;
    l.tail->next = p;
    l.head = p;
}

// ------------------------------------------------------------
// 7. Them vao cuoi
// ------------------------------------------------------------
void addTail(CircularLinkedList &l, int x)
{
    Node *p = createNode(x);

    // Danh sach rong
    if (l.head == nullptr)
    {
        l.head = p;
        l.tail = p;
        p->next = p;            // tu tro vao chinh no
        return;
    }

    p->next = l.tail->next;     // p->next = head
    l.tail->next = p;
    l.tail = p;
}

// ------------------------------------------------------------
// 8. Them sau Node co gia tri x
// ------------------------------------------------------------
bool addAfter(CircularLinkedList &l, int x, int value)
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
bool update(const CircularLinkedList &l, int oldValue, int newValue)
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
bool deleteHead(CircularLinkedList &l)
{
    if (l.head == nullptr)
        return false;

    Node *p = l.head;

    // Chi co 1 Node
    if (l.head == l.tail)
    {
        l.head = nullptr;
        l.tail = nullptr;
        delete p;
        return true;
    }

    l.head = l.head->next;
    l.tail->next = l.head;
    delete p;

    return true;
}

// ------------------------------------------------------------
// 11. Xoa cuoi
// ------------------------------------------------------------
bool deleteTail(CircularLinkedList &l)
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

    // Tim node dung truoc tail
    Node *p = l.head;

    while (p->next != l.tail)
        p = p->next;

    Node *q = l.tail;

    p->next = l.head;
    l.tail = p;
    delete q;

    return true;
}

// ------------------------------------------------------------
// 12. Xoa Node dau tien co gia tri x
// ------------------------------------------------------------
bool deleteX(CircularLinkedList &l, int x)
{
    if (l.head == nullptr)
        return false;

    // Xoa head
    if (l.head->info == x)
        return deleteHead(l);

    Node *prev = l.head;
    Node *p = l.head->next;

    while (p != l.head && p->info != x)
    {
        prev = p;
        p = p->next;
    }

    // Khong tim thay (da quay ve head)
    if (p == l.head)
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
int deleteAllX(CircularLinkedList &l, int x)
{
    if (l.head == nullptr)
        return 0;

    int count = 0;

    // Xoa cac node o dau co gia tri x
    while (l.head != nullptr && l.head->info == x)
    {
        deleteHead(l);
        count++;
    }

    if (l.head == nullptr)
        return count;

    Node *prev = l.head;
    Node *p = l.head->next;

    while (p != l.head)
    {
        if (p->info == x)
        {
            Node *next = p->next;

            prev->next = next;

            // Neu xoa tail thi cap nhat tail
            if (p == l.tail)
                l.tail = prev;

            delete p;
            p = next;
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
void clear(CircularLinkedList &l)
{
    while (l.head != nullptr)
        deleteHead(l);
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    CircularLinkedList l;
    init(l);

    // Tao danh sach
    addTail(l, 10);
    addTail(l, 20);
    addTail(l, 30);
    addTail(l, 40);

    cout << "Danh sach ban dau: ";
    output(l);

    // Kiem tra tinh chat vong
    if (l.tail != nullptr && l.tail->next == l.head)
        cout << "Tinh chat vong: OK (tail->next = head)" << endl;

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
