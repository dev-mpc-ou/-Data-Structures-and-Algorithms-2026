#include <iostream>
using namespace std;

// ============================================================
// QUEUE - DANH SACH LIEN KET
// Cac phuong thuc duoc dat trong struct Queue
// ============================================================
struct Node
{
    int data;
    Node *next;
};

struct Queue
{
    Node *front;
    Node *rear;

    // 1. Khoi tao
    void init() { front = rear = nullptr; }

    // 2. Kiem tra rong
    bool isEmpty() { return front == nullptr; }

    // 3. Them phan tu vao cuoi hang doi
    void enqueue(int x)
    {
        Node *p = new Node{x, nullptr};
        if (isEmpty())
            front = rear = p;
        else
        {
            rear->next = p;
            rear = p;
        }
    }

    // 4. Lay phan tu dau hang doi
    bool dequeue(int &x)
    {
        if (isEmpty())
            return false;
        Node *p = front;
        x = p->data;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete p;
        return true;
    }

    // 5. Xem phan tu dau hang doi
    bool peek(int &x)
    {
        if (isEmpty())
            return false;
        x = front->data;
        return true;
    }

    // 6. Xuat queue
    void output()
    {
        if (isEmpty())
        {
            cout << "Queue rong!\n";
            return;
        }
        cout << "Queue (Front -> Rear): ";
        for (Node *p = front; p; p = p->next)
            cout << p->data << " ";
        cout << '\n';
    }

    // 7. Xoa toan bo queue
    void clear()
    {
        while (front)
        {
            Node *p = front;
            front = front->next;
            delete p;
        }
        rear = nullptr;
    }
};

int main()
{
    Queue q;
    q.init();

    int c, x;
    do
    {
        cout << "\n===== QUEUE - DSLK =====\n1. Enqueue\n2. Dequeue\n3. Peek\n4. IsEmpty\n5. Xuat Queue\n0. Thoat\nChon: ";
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Nhap x: ";
            cin >> x;
            q.enqueue(x);
            cout << "Enqueue thanh cong!\n";
            break;
        case 2:
            cout << (q.dequeue(x) ? "Phan tu vua lay ra: " + to_string(x) + "\n" : "Queue rong!\n");
            break;
        case 3:
            cout << (q.peek(x) ? "Phan tu Front: " + to_string(x) + "\n" : "Queue rong!\n");
            break;
        case 4:
            cout << (q.isEmpty() ? "Queue rong!\n" : "Queue khong rong!\n");
            break;
        case 5:
            q.output();
            break;
        }
    } while (c != 0);

    q.clear();
    return 0;
}