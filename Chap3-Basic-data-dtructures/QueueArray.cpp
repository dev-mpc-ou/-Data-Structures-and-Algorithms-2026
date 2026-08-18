#include <iostream>
using namespace std;
#define MAX 100

// ============================================================
// QUEUE - DANH SACH DAC (mang vong)
// Cac phuong thuc duoc dat trong struct Queue
// ============================================================
struct Queue
{
    int a[MAX];
    int front, rear, count;

    // 1. Khoi tao
    void init()
    {
        front = 0;
        rear = -1;
        count = 0;
    }

    // 2. Kiem tra rong / day
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == MAX; }

    // 3. Them phan tu vao cuoi hang doi
    bool enqueue(int x)
    {
        if (isFull())
            return false;
        rear = (rear + 1) % MAX;
        a[rear] = x;
        count++;
        return true;
    }

    // 4. Lay phan tu dau hang doi
    bool dequeue(int &x)
    {
        if (isEmpty())
            return false;
        x = a[front];
        front = (front + 1) % MAX;
        count--;
        return true;
    }

    // 5. Xem phan tu dau hang doi
    bool peek(int &x)
    {
        if (isEmpty())
            return false;
        x = a[front];
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
        for (int i = 0; i < count; i++)
            cout << a[(front + i) % MAX] << " ";
        cout << '\n';
    }
};

int main()
{
    Queue q;
    q.init();

    int c, x;
    do
    {
        cout << "\n===== QUEUE - DANH SACH DAC =====\n1. Enqueue\n2. Dequeue\n3. Peek\n4. IsEmpty\n5. IsFull\n6. Xuat Queue\n0. Thoat\nChon: ";
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Nhap x: ";
            cin >> x;
            cout << (q.enqueue(x) ? "Enqueue thanh cong!\n" : "Queue day!\n");
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
            cout << (q.isFull() ? "Queue day!\n" : "Queue chua day!\n");
            break;
        case 6:
            q.output();
            break;
        }
    } while (c != 0);

    return 0;
}