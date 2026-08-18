#include <iostream>
using namespace std;

const int M = 7;

struct HashTable
{
    int table[M];
};

int hashFunc(int key)
{
    int h = key % M;
    if (h < 0) h += M;
    return h;
}

void init(HashTable& H)
{
    for (int i = 0; i < M; i++)
        H.table[i] = -1;
}

bool insert(HashTable& H, int key)
{
    int h = hashFunc(key);

    for (int i = 0; i < M; i++)
    {
        int index = (h + i * i) % M;

        if (H.table[index] == -1)
        {
            H.table[index] = key;
            return true;
        }

        if (H.table[index] == key)
            return false;
    }

    return false;
}

bool search(HashTable& H, int key)
{
    int h = hashFunc(key);

    for (int i = 0; i < M; i++)
    {
        int index = (h + i * i) % M;

        if (H.table[index] == -1)
            return false;

        if (H.table[index] == key)
            return true;
    }

    return false;
}

void output(HashTable& H)
{
    cout << "\n=== QUADRATIC PROBING ===\n";

    for (int i = 0; i < M; i++)
    {
        cout << "Index [" << i << "]: ";

        if (H.table[i] == -1)
            cout << "EMPTY";
        else
            cout << H.table[i];

        cout << endl;
    }
}

int main()
{
    HashTable H;
    init(H);

    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << " QUADRATIC PROBING\n";
        cout << "==============================\n";
        cout << "1. Them phan tu\n";
        cout << "2. Xuat bang\n";
        cout << "3. Tim kiem\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int x;
            cout << "Nhap x: ";
            cin >> x;

            if (insert(H, x))
                cout << "Da them " << x << endl;
            else
                cout << "Khong the them " << x << endl;

            break;
        }

        case 2:
            output(H);
            break;

        case 3:
        {
            int x;
            cout << "Nhap x can tim: ";
            cin >> x;

            if (search(H, x))
                cout << "Tim thay " << x << endl;
            else
                cout << "Khong tim thay " << x << endl;

            break;
        }

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}
