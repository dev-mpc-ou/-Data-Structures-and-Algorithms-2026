#include <iostream>
#include <iomanip>
using namespace std;

const int M = 7;

struct Node
{
    int key;
    int link;
};

int hashFunc(int key)
{
    int h = key % M;
    if (h < 0) h += M;
    return h;
}

void init(Node table[])
{
    for (int i = 0; i < M; i++)
    {
        table[i].key = -1;
        table[i].link = -1;
    }
}

int findEmpty(Node table[])
{
    for (int i = M - 1; i >= 0; i--)
    {
        if (table[i].key == -1)
            return i;
    }

    return -1;
}

bool insert(Node table[], int key)
{
    int index = hashFunc(key);

    if (table[index].key == -1)
    {
        table[index].key = key;
        table[index].link = -1;
        return true;
    }

    if (table[index].key == key)
        return false;

    int current = index;

    while (table[current].link != -1)
    {
        current = table[current].link;

        if (table[current].key == key)
            return false;
    }

    int emptyIndex = findEmpty(table);

    if (emptyIndex == -1)
        return false;

    table[emptyIndex].key = key;
    table[emptyIndex].link = -1;
    table[current].link = emptyIndex;

    return true;
}

bool search(Node table[], int key)
{
    int current = hashFunc(key);

    while (current != -1)
    {
        if (table[current].key == key)
            return true;

        if (table[current].key == -1)
            return false;

        current = table[current].link;
    }

    return false;
}

void output(Node table[])
{
    cout << "\n=== COALESCED CHAINING ===\n";

    cout << left
         << setw(10) << "Index"
         << setw(10) << "Key"
         << setw(10) << "Link"
         << endl;

    for (int i = 0; i < M; i++)
    {
        cout << left << setw(10) << i;

        if (table[i].key == -1)
        {
            cout << setw(10) << "EMPTY"
                 << setw(10) << -1;
        }
        else
        {
            cout << setw(10) << table[i].key
                 << setw(10) << table[i].link;
        }

        cout << endl;
    }
}

int main()
{
    Node table[M];
    init(table);

    int choice;

    do
    {
        cout << "\n==============================\n";
        cout << " COALESCED CHAINING\n";
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

            if (insert(table, x))
                cout << "Da them " << x << endl;
            else
                cout << "Khong the them " << x << endl;

            break;
        }

        case 2:
            output(table);
            break;

        case 3:
        {
            int x;
            cout << "Nhap x can tim: ";
            cin >> x;

            if (search(table, x))
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
