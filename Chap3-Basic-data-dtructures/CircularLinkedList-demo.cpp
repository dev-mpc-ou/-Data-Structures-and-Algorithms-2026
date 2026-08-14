#include <iostream>
using namespace std;

// ============================================================
// DEMO: DANH SACH LIEN KET VONG DON
//
// Cac thao tac:
// 1. Khoi tao
// 2. Tao Node
// 3. Duyet
// 4. Dem Node
// 5. Tim kiem
// 6. Them dau
// 7. Them cuoi
// 8. Them sau Node
// 9. Sua Node
// 10. Xoa dau
// 11. Xoa cuoi
// 12. Xoa Node dau tien co gia tri x
// 13. Xoa tat ca Node co gia tri x
// 14. Xoa toan bo danh sach
// ============================================================

struct Node
{
    int info;
    Node *next;
};

// ============================================================
// 1. KHOI TAO
// ============================================================

void init(Node *&head, Node *&tail)
{
    head = nullptr;
    tail = nullptr;
}

// ============================================================
// 2. TAO NODE
// ============================================================

Node* createNode(int x)
{
    Node *p = new Node;

    p->info = x;
    p->next = nullptr;

    return p;
}

// ============================================================
// 3. DUYET DANH SACH
// ============================================================

void output(Node *head)
{
    if (head == nullptr)
    {
        cout << "Danh sach rong!\n";
        return;
    }

    Node *p = head;

    do
    {
        cout << p->info << " ";
        p = p->next;
    }
    while (p != head);

    cout << endl;
}

// ============================================================
// 4. DEM SO NODE
// ============================================================

int countNode(Node *head)
{
    if (head == nullptr)
        return 0;

    int count = 0;
    Node *p = head;

    do
    {
        count++;
        p = p->next;
    }
    while (p != head);

    return count;
}

// ============================================================
// 5. TIM NODE CO GIA TRI X
// ============================================================

Node* search(Node *head, int x)
{
    if (head == nullptr)
        return nullptr;

    Node *p = head;

    do
    {
        if (p->info == x)
            return p;

        p = p->next;
    }
    while (p != head);

    return nullptr;
}

// ============================================================
// 6. THEM VAO DAU
// ============================================================

void addHead(Node *&head, Node *&tail, int x)
{
    Node *p = createNode(x);

    // Danh sach rong
    if (head == nullptr)
    {
        head = tail = p;
        p->next = head;
        return;
    }

    p->next = head;
    head = p;

    // Giữ lien ket vong
    tail->next = head;
}

// ============================================================
// 7. THEM VAO CUOI
// ============================================================

void addTail(Node *&head, Node *&tail, int x)
{
    Node *p = createNode(x);

    // Danh sach rong
    if (head == nullptr)
    {
        head = tail = p;
        p->next = head;
        return;
    }

    p->next = head;
    tail->next = p;
    tail = p;
}

// ============================================================
// 8. THEM SAU NODE CO GIA TRI X
// ============================================================

bool addAfter(Node *&head, Node *&tail, int x, int value)
{
    Node *q = search(head, value);

    if (q == nullptr)
        return false;

    Node *p = createNode(x);

    p->next = q->next;
    q->next = p;

    // q la Node cuoi
    if (q == tail)
        tail = p;

    return true;
}

// ============================================================
// 9. SUA NODE CO GIA TRI CU THANH GIA TRI MOI
// ============================================================

bool update(Node *head, int oldValue, int newValue)
{
    Node *p = search(head, oldValue);

    if (p == nullptr)
        return false;

    p->info = newValue;

    return true;
}

// ============================================================
// 10. XOA NODE DAU
// ============================================================

bool deleteHead(Node *&head, Node *&tail)
{
    if (head == nullptr)
        return false;

    Node *p = head;

    // Chi co 1 Node
    if (head == tail)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->next;
        tail->next = head;
    }

    delete p;

    return true;
}

// ============================================================
// 11. XOA NODE CUOI
// ============================================================

bool deleteTail(Node *&head, Node *&tail)
{
    if (head == nullptr)
        return false;

    // Chi co 1 Node
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        return true;
    }

    // Tim Node truoc tail
    Node *p = head;

    while (p->next != tail)
        p = p->next;

    p->next = head;
    delete tail;
    tail = p;

    return true;
}

// ============================================================
// 12. XOA NODE DAU TIEN CO GIA TRI X
// ============================================================

bool deleteX(Node *&head, Node *&tail, int x)
{
    if (head == nullptr)
        return false;

    // Xoa head
    if (head->info == x)
        return deleteHead(head, tail);

    Node *prev = head;
    Node *p = head->next;

    while (p != head && p->info != x)
    {
        prev = p;
        p = p->next;
    }

    // Khong tim thay
    if (p == head)
        return false;

    prev->next = p->next;

    // Xoa tail
    if (p == tail)
        tail = prev;

    delete p;

    return true;
}

// ============================================================
// 13. XOA TAT CA NODE CO GIA TRI X
// ============================================================

int deleteAllX(Node *&head, Node *&tail, int x)
{
    int count = 0;

    while (head != nullptr && head->info == x)
    {
        deleteHead(head, tail);
        count++;
    }

    if (head == nullptr)
        return count;

    Node *prev = head;
    Node *p = head->next;

    while (p != head)
    {
        if (p->info == x)
        {
            if (p == tail)
            {
                prev->next = head;
                delete p;
                tail = prev;
                count++;
                break;
            }

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

// ============================================================
// 14. XOA TOAN BO DANH SACH
// ============================================================

void clear(Node *&head, Node *&tail)
{
    while (head != nullptr)
        deleteHead(head, tail);
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n========== DANH SACH LIEN KET VONG ==========\n";
    cout << "1. Them dau\n";
    cout << "2. Them cuoi\n";
    cout << "3. Them sau Node\n";
    cout << "4. Duyet danh sach\n";
    cout << "5. Tim kiem\n";
    cout << "6. Sua Node\n";
    cout << "7. Xoa dau\n";
    cout << "8. Xoa cuoi\n";
    cout << "9. Xoa Node theo gia tri\n";
    cout << "10. Xoa tat ca Node theo gia tri\n";
    cout << "11. Dem Node\n";
    cout << "12. Xoa toan bo\n";
    cout << "0. Thoat\n";
    cout << "=============================================\n";
    cout << "Chon: ";
}

// ============================================================
// MAIN
// ============================================================

int main()
{
    Node *head, *tail;
    init(head, tail);

    int choice;

    do
    {
        menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x;
            cout << "Nhap x: ";
            cin >> x;

            addHead(head, tail, x);
            cout << "Them dau thanh cong!\n";
            break;
        }

        case 2:
        {
            int x;
            cout << "Nhap x: ";
            cin >> x;

            addTail(head, tail, x);
            cout << "Them cuoi thanh cong!\n";
            break;
        }

        case 3:
        {
            int x, value;

            cout << "Nhap x can them: ";
            cin >> x;

            cout << "Them sau gia tri: ";
            cin >> value;

            if (addAfter(head, tail, x, value))
                cout << "Them thanh cong!\n";
            else
                cout << "Khong tim thay Node!\n";

            break;
        }

        case 4:
            cout << "Danh sach: ";
            output(head);
            break;

        case 5:
        {
            int x;
            cout << "Nhap x can tim: ";
            cin >> x;

            Node *p = search(head, x);

            if (p != nullptr)
                cout << "Tim thay: " << p->info << endl;
            else
                cout << "Khong tim thay!\n";

            break;
        }

        case 6:
        {
            int oldValue, newValue;

            cout << "Gia tri cu: ";
            cin >> oldValue;

            cout << "Gia tri moi: ";
            cin >> newValue;

            if (update(head, oldValue, newValue))
                cout << "Sua thanh cong!\n";
            else
                cout << "Khong tim thay Node!\n";

            break;
        }

        case 7:
            if (deleteHead(head, tail))
                cout << "Xoa dau thanh cong!\n";
            else
                cout << "Danh sach rong!\n";

            break;

        case 8:
            if (deleteTail(head, tail))
                cout << "Xoa cuoi thanh cong!\n";
            else
                cout << "Danh sach rong!\n";

            break;

        case 9:
        {
            int x;
            cout << "Nhap gia tri can xoa: ";
            cin >> x;

            if (deleteX(head, tail, x))
                cout << "Xoa thanh cong!\n";
            else
                cout << "Khong tim thay Node!\n";

            break;
        }

        case 10:
        {
            int x;
            cout << "Nhap gia tri can xoa: ";
            cin >> x;

            int count = deleteAllX(head, tail, x);

            cout << "Da xoa " << count << " Node.\n";
            break;
        }

        case 11:
            cout << "So Node: " << countNode(head) << endl;
            break;

        case 12:
            clear(head, tail);
            cout << "Da xoa toan bo danh sach!\n";
            break;

        case 0:
            cout << "Ket thuc chuong trinh.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    }
    while (choice != 0);

    return 0;
}
