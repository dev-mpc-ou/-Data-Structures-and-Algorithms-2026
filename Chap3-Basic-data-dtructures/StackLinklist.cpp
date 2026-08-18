#include <iostream>
using namespace std;

// ============================================================
// STACK - DANH SACH LIEN KET
// Cac phuong thuc duoc dat trong struct Stack
// ============================================================
struct Node
{
    int data;
    Node *next;
};

struct Stack
{
    Node *top;

    // 1. Khoi tao
    void init() { top = nullptr; }

    // 2. Kiem tra rong
    bool isEmpty() { return top == nullptr; }

    // 3. Them phan tu vao dinh stack
    void push(int x)
    {
        Node *p = new Node{x, top};
        top = p;
    }

    // 4. Lay phan tu tren dinh stack
    bool pop(int &x)
    {
        if (isEmpty())
            return false;
        Node *p = top;
        x = p->data;
        top = top->next;
        delete p;
        return true;
    }

    // 5. Xem phan tu tren dinh stack
    bool peek(int &x)
    {
        if (isEmpty())
            return false;
        x = top->data;
        return true;
    }

    // 6. Xuat stack
    void output()
    {
        if (isEmpty())
        {
            cout << "Stack rong!\n";
            return;
        }
        cout << "Stack (Top -> Bottom): ";
        for (Node *p = top; p; p = p->next)
            cout << p->data << " ";
        cout << '\n';
    }

    // 7. Xoa toan bo stack
    void clear()
    {
        while (top)
        {
            Node *p = top;
            top = top->next;
            delete p;
        }
    }
};

int main()
{
    Stack s;
    s.init();

    int c, x;
    do
    {
        cout << "\n===== STACK - DSLK =====\n1. Push\n2. Pop\n3. Peek\n4. IsEmpty\n5. Xuat Stack\n0. Thoat\nChon: ";
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Nhap x: ";
            cin >> x;
            s.push(x);
            cout << "Push thanh cong!\n";
            break;
        case 2:
            cout << (s.pop(x) ? "Phan tu vua lay ra: " + to_string(x) + "\n" : "Stack rong!\n");
            break;
        case 3:
            cout << (s.peek(x) ? "Phan tu Top: " + to_string(x) + "\n" : "Stack rong!\n");
            break;
        case 4:
            cout << (s.isEmpty() ? "Stack rong!\n" : "Stack khong rong!\n");
            break;
        case 5:
            s.output();
            break;
        }
    } while (c != 0);

    s.clear();
    return 0;
}