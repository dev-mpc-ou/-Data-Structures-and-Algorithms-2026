#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

#define SIZE 2000

// ============================================================
// DEMO: BAI 5 - BANG BAM
//
// 1. NOI KET TRUC TIEP (Separate / Direct Chaining)
//    Moi o bang bam la dau mot DSLK.
//
// 2. NOI KET HOP NHAT (Coalesced Hashing)
//    Cac node nam ngay trong bang; moi node co con tro
//    next la CHI SO trong bang.
//
// Ham bam:
//     h(x) = abs(x) % SIZE
//
// File nay cho phep chon phuong phap va test rieng.
// ============================================================

// ------------------------------------------------------------
// 1. Ham bam
// ------------------------------------------------------------
int hashFunction(int x)
{
    int r = x % SIZE;

    if (r < 0)
        r += SIZE;

    return r;
}

// ============================================================
// A. NOI KET TRUC TIEP (DIRECT CHAINING)
// ============================================================

struct DirectNode
{
    int key;
    DirectNode *next;
};

struct DirectHash
{
    DirectNode *table[SIZE];
};

// ------------------------------------------------------------
// 2. Khoi tao
// ------------------------------------------------------------
void initDirect(DirectHash &h)
{
    for (int i = 0; i < SIZE; i++)
        h.table[i] = nullptr;
}

// ------------------------------------------------------------
// 3. Them x vao bang bam
// ------------------------------------------------------------
void insertDirect(DirectHash &h, int x)
{
    int index = hashFunction(x);

    DirectNode *p = new DirectNode;
    p->key = x;
    p->next = h.table[index];

    h.table[index] = p;
}

// ------------------------------------------------------------
// 4. Tim x trong bang bam
// ------------------------------------------------------------
bool searchDirect(const DirectHash &h, int x)
{
    int index = hashFunction(x);

    DirectNode *p = h.table[index];

    while (p != nullptr)
    {
        if (p->key == x)
            return true;

        p = p->next;
    }

    return false;
}

// ------------------------------------------------------------
// 5. Xoa x khoi bang bam
// ------------------------------------------------------------
bool deleteDirect(DirectHash &h, int x)
{
    int index = hashFunction(x);

    DirectNode *p = h.table[index];
    DirectNode *prev = nullptr;

    while (p != nullptr)
    {
        if (p->key == x)
        {
            if (prev == nullptr)
                h.table[index] = p->next;
            else
                prev->next = p->next;

            delete p;
            return true;
        }

        prev = p;
        p = p->next;
    }

    return false;
}

// ------------------------------------------------------------
// 6. Xuat toan bo bang bam
// ------------------------------------------------------------
void outputDirect(const DirectHash &h)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << "[" << i << "] ";

        DirectNode *p = h.table[i];

        while (p != nullptr)
        {
            cout << p->key << " -> ";
            p = p->next;
        }

        cout << "NULL\n";
    }
}

// ------------------------------------------------------------
// 7. Xoa toan bo bang bam
// ------------------------------------------------------------
void clearDirect(DirectHash &h)
{
    for (int i = 0; i < SIZE; i++)
    {
        DirectNode *p = h.table[i];

        while (p != nullptr)
        {
            DirectNode *next = p->next;
            delete p;
            p = next;
        }

        h.table[i] = nullptr;
    }
}

// ============================================================
// B. NOI KET HOP NHAT (COALESCED HASHING)
// ============================================================

struct CoalescedNode
{
    int key;
    int next;
    bool used;
};

struct CoalescedHash
{
    CoalescedNode table[SIZE];
};

// ------------------------------------------------------------
// 8. Khoi tao
// ------------------------------------------------------------
void initCoalesced(CoalescedHash &h)
{
    for (int i = 0; i < SIZE; i++)
    {
        h.table[i].key = 0;
        h.table[i].next = -1;
        h.table[i].used = false;
    }
}

// ------------------------------------------------------------
// 9. Tim o trong (tim tu cuoi bang ve dau)
// ------------------------------------------------------------
int findFreeCoalesced(CoalescedHash &h)
{
    // Tim o trong tu cuoi bang ve dau
    for (int i = SIZE - 1; i >= 0; i--)
    {
        if (!h.table[i].used)
            return i;
    }

    return -1;
}

// ------------------------------------------------------------
// 10. Tim x trong bang bam
// ------------------------------------------------------------
bool searchCoalesced(const CoalescedHash &h, int x)
{
    int index = hashFunction(x);

    if (!h.table[index].used)
        return false;

    int p = index;

    while (p != -1)
    {
        if (h.table[p].used && h.table[p].key == x)
            return true;

        p = h.table[p].next;
    }

    return false;
}

// ------------------------------------------------------------
// 11. Them x vao bang bam
// ------------------------------------------------------------
bool insertCoalesced(CoalescedHash &h, int x)
{
    int index = hashFunction(x);

    // O trong bam chinh
    if (!h.table[index].used)
    {
        h.table[index].key = x;
        h.table[index].next = -1;
        h.table[index].used = true;
        return true;
    }

    // Neu da ton tai
    if (searchCoalesced(h, x))
        return false;

    // Tim o trong
    int freeIndex = findFreeCoalesced(h);

    if (freeIndex == -1)
        return false;

    // Di cuoi chuoi
    int p = index;

    while (h.table[p].next != -1)
        p = h.table[p].next;

    h.table[freeIndex].key = x;
    h.table[freeIndex].next = -1;
    h.table[freeIndex].used = true;

    h.table[p].next = freeIndex;

    return true;
}

// ------------------------------------------------------------
// 12. Xoa x khoi bang bam
// ------------------------------------------------------------
bool deleteCoalesced(CoalescedHash &h, int x)
{
    int index = hashFunction(x);

    if (!h.table[index].used)
        return false;

    int p = index;
    int prev = -1;

    while (p != -1)
    {
        if (h.table[p].used && h.table[p].key == x)
        {
            // Neu x nam ngay o bucket dau
            if (prev == -1)
            {
                int nextIndex = h.table[p].next;

                if (nextIndex == -1)
                {
                    h.table[p].used = false;
                    h.table[p].next = -1;
                }
                else
                {
                    // Dua node ke tiep len bucket chinh
                    h.table[p].key = h.table[nextIndex].key;
                    h.table[p].next = h.table[nextIndex].next;
                    h.table[nextIndex].used = false;
                    h.table[nextIndex].next = -1;
                }

                return true;
            }

            // Node nam o giua/cuoi chuoi
            h.table[prev].next = h.table[p].next;
            h.table[p].used = false;
            h.table[p].next = -1;

            return true;
        }

        prev = p;
        p = h.table[p].next;
    }

    return false;
}

// ------------------------------------------------------------
// 13. Xuat toan bo bang bam
// ------------------------------------------------------------
void outputCoalesced(const CoalescedHash &h)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (h.table[i].used)
        {
            cout << "[" << i << "] "
                 << h.table[i].key
                 << " -> next = "
                 << h.table[i].next << "\n";
        }
    }
}

// ============================================================
// C. HOAN VI CUA HAI CHUOI (ANAGRAM)
// ============================================================

// ------------------------------------------------------------
// 14. Kiem tra hai chuoi co la hoan vi cua nhau
// Dung bang dem tan suat ky tu
// ------------------------------------------------------------
bool areAnagrams(string a, string b)
{
    if (a.length() != b.length())
        return false;

    int count[256] = {0};

    for (unsigned char c : a)
        count[c]++;

    for (unsigned char c : b)
        count[c]--;

    for (int i = 0; i < 256; i++)
    {
        if (count[i] != 0)
            return false;
    }

    return true;
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n================ BAI 5 ================\n";
    cout << "1. Noi ket truc tiep - Them\n";
    cout << "2. Noi ket truc tiep - Tim\n";
    cout << "3. Noi ket truc tiep - Xoa\n";
    cout << "4. Noi ket truc tiep - Xuat\n";
    cout << "5. Noi ket hop nhat - Them\n";
    cout << "6. Noi ket hop nhat - Tim\n";
    cout << "7. Noi ket hop nhat - Xoa\n";
    cout << "8. Noi ket hop nhat - Xuat\n";
    cout << "9. Kiem tra hai chuoi co la hoan vi\n";
    cout << "0. Thoat\n";
    cout << "=======================================\n";
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    DirectHash direct;
    CoalescedHash coalesced;

    initDirect(direct);
    initCoalesced(coalesced);

    int choice, x;

    do
    {
        menu();
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Nhap x: ";
            cin >> x;
            insertDirect(direct, x);
            cout << "Da them vao bang bam noi ket truc tiep.\n";
            break;

        case 2:
            cout << "Nhap x: ";
            cin >> x;

            if (searchDirect(direct, x))
                cout << "Tim thay.\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 3:
            cout << "Nhap x: ";
            cin >> x;

            if (deleteDirect(direct, x))
                cout << "Da xoa.\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 4:
            outputDirect(direct);
            break;

        case 5:
            cout << "Nhap x: ";
            cin >> x;

            if (insertCoalesced(coalesced, x))
                cout << "Da them vao bang bam noi ket hop nhat.\n";
            else
                cout << "Khong them duoc (day hoac trung).\n";
            break;

        case 6:
            cout << "Nhap x: ";
            cin >> x;

            if (searchCoalesced(coalesced, x))
                cout << "Tim thay.\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 7:
            cout << "Nhap x: ";
            cin >> x;

            if (deleteCoalesced(coalesced, x))
                cout << "Da xoa.\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 8:
            outputCoalesced(coalesced);
            break;

        case 9:
        {
            string a, b;

            cin.ignore();

            cout << "Chuoi 1: ";
            getline(cin, a);

            cout << "Chuoi 2: ";
            getline(cin, b);

            if (areAnagrams(a, b))
                cout << "Hai chuoi la hoan vi cua nhau.\n";
            else
                cout << "Hai chuoi KHONG phai la hoan vi.\n";

            break;
        }

        case 0:
            cout << "Ket thuc.\n";
            break;

        default:
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);

    clearDirect(direct);

    return 0;
}
