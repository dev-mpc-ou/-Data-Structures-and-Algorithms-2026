#include <iostream>
using namespace std;
#define MAX 100

// ============================================================
// STACK - DANH SACH DAC (mang)
// Cac phuong thuc duoc dat trong struct Stack
// ============================================================
struct Stack
{
    int a[MAX];
    int top;

    // 1. Khoi tao
    void init() { top = -1; }

    // 2. Kiem tra rong / day
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX - 1; }

    // 3. Them phan tu vao dinh stack
    bool push(int x)
    {
        if (isFull())
            return false;
        a[++top] = x;
        return true;
    }

    // 4. Lay phan tu tren dinh stack
    bool pop(int &x)
    {
        if (isEmpty())
            return false;
        x = a[top--];
        return true;
    }

    // 5. Xem phan tu tren dinh stack
    bool peek(int &x)
    {
        if (isEmpty())
            return false;
        x = a[top];
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
        for (int i = top; i >= 0; i--)
            cout << a[i] << " ";
        cout << '\n';
    }
};

int main()
{
    Stack s;
    s.init();

    int c, x;
    do
    {
        cout << "\n===== STACK - DANH SACH DAC =====\n1. Push\n2. Pop\n3. Peek\n4. IsEmpty\n5. IsFull\n6. Xuat Stack\n0. Thoat\nChon: ";
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Nhap x: ";
            cin >> x;
            cout << (s.push(x) ? "Push thanh cong!\n" : "Stack day!\n");
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
            cout << (s.isFull() ? "Stack day!\n" : "Stack chua day!\n");
            break;
        case 6:
            s.output();
            break;
        }
    } while (c != 0);

    return 0;
}