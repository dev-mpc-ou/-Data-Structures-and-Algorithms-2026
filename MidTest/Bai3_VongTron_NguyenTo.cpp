#include <iostream>
using namespace std;

// ============================================================
// DEMO: BAI 3 - TRO CHOI LOAI NGUOI TRONG VONG TRON
//
// Moi nguoi duoc danh so 1..n.
//
// Quy uoc:
// - Nguoi bat dau dem nhan so 1.
// - Moi lan dem tang 1.
// - Neu so vua dem la so nguyen to thi nguoi dang dem bi loai.
// - Nguoi ke tiep tiep tuc dem so tiep theo.
// - Neu dao chieu: sau moi lan loai, huong di doi nguoc lai.
//
// Dung DSLK VONG (2 chieu) de quan ly vong tron.
// ============================================================

struct Node
{
    int id;
    Node *next;
    Node *prev;
};

// Quan ly vong tron: current la nguoi dang dem
struct CircularList
{
    Node *current;
    int n;
};

// ============================================================
// CAC THAO TAC CO BAN
// ============================================================

// ------------------------------------------------------------
// 1. Khoi tao vong tron rong
// ------------------------------------------------------------
void init(CircularList &l)
{
    l.current = nullptr;
    l.n = 0;
}

// ------------------------------------------------------------
// 2. Tao vong tron gom n nguoi (1..n)
// ------------------------------------------------------------
void createCircle(CircularList &l, int n)
{
    l.current = nullptr;
    l.n = 0;

    for (int i = 1; i <= n; i++)
    {
        Node *p = new Node;
        p->id = i;

        if (l.current == nullptr)
        {
            p->next = p;
            p->prev = p;
            l.current = p;
        }
        else
        {
            Node *last = l.current->prev;

            p->next = l.current;
            p->prev = last;

            last->next = p;
            l.current->prev = p;
        }

        l.n++;
    }
}

// ------------------------------------------------------------
// 3. Kiem tra so nguyen to
// ------------------------------------------------------------
bool isPrime(int x)
{
    if (x < 2)
        return false;

    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;

    return true;
}

// ------------------------------------------------------------
// 4. Xoa node hien tai
// Sau khi xoa, current tro den nguoi ke tiep theo huong
// ------------------------------------------------------------
void removeCurrent(CircularList &l, bool clockwise)
{
    Node *p = l.current;

    if (l.n == 1)
    {
        delete p;
        l.current = nullptr;
        l.n = 0;
        return;
    }

    Node *nextNode = p->next;
    Node *prevNode = p->prev;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    if (clockwise)
        l.current = nextNode;
    else
        l.current = prevNode;

    delete p;
    l.n--;
}

// ------------------------------------------------------------
// 5. Di chuyen theo huong
// clockwise = true  => next
// clockwise = false => prev
// ------------------------------------------------------------
void move(CircularList &l, bool clockwise)
{
    if (l.current == nullptr)
        return;

    if (clockwise)
        l.current = l.current->next;
    else
        l.current = l.current->prev;
}

// ------------------------------------------------------------
// 6. Xuat vong tron
// ------------------------------------------------------------
void printCircle(const CircularList &l)
{
    if (l.current == nullptr)
    {
        cout << "Vong tron rong.\n";
        return;
    }

    Node *p = l.current;

    cout << "Vong tron: ";

    do
    {
        cout << p->id << " ";
        p = p->next;
    } while (p != l.current);

    cout << "\n";
}

// ------------------------------------------------------------
// 7. Xoa toan bo vong tron
// ------------------------------------------------------------
void clear(CircularList &l)
{
    if (l.current == nullptr)
        return;

    Node *p = l.current->next;

    while (p != l.current)
    {
        Node *next = p->next;
        delete p;
        p = next;
    }

    delete l.current;

    l.current = nullptr;
    l.n = 0;
}

// ============================================================
// MO PHONG TRO CHOI
// ============================================================

// ------------------------------------------------------------
// 8. Mo phong - co in cac lan loai
// Tra ve nguoi chien thang, -1 neu tham so khong hop le
// ------------------------------------------------------------
int simulate(int n, int start, bool reverseDirection, bool show)
{
    if (n <= 0 || start < 1 || start > n)
        return -1;

    CircularList l;
    init(l);
    createCircle(l, n);

    // Tim nguoi bat dau
    while (l.current->id != start)
        l.current = l.current->next;

    bool clockwise = true;
    int count = 1;

    if (show)
        cout << "\nBat dau: nguoi " << start << " dem " << count << "\n";

    while (l.n > 1)
    {
        // Neu count la so nguyen to -> loai nguoi dang dem
        if (isPrime(count))
        {
            int removed = l.current->id;

            if (show)
            {
                cout << "So " << count
                     << " la nguyen to -> loai nguoi "
                     << removed << "\n";
            }

            // Luu huong hien tai de tim nguoi ke tiep
            bool oldDirection = clockwise;

            removeCurrent(l, oldDirection);

            if (l.n == 1)
                break;

            // Mo rong: sau khi loai thi dao chieu
            if (reverseDirection)
                clockwise = !clockwise;

            // current da duoc dat la nguoi ke tiep
            // theo huong truoc khi dao chieu.
            // Neu dao chieu, phai lui/tien mot buoc de dung dung nguoi
            // ke tiep theo huong moi.
            if (reverseDirection)
            {
                // Sau khi dao chieu, nguoi tiep theo la nguoi vua dung
                // phia truoc nguoi bi loai theo huong moi.
                if (clockwise)
                    l.current = l.current->next;
                else
                    l.current = l.current->prev;
            }
        }
        else
        {
            // So khong phai nguyen to:
            // nguoi hien tai chi dem, sau do nguoi ke tiep dem.
            move(l, clockwise);
        }

        count++;
    }

    int winner = l.current->id;

    if (show)
        cout << "Nguoi chien thang: " << winner << "\n";

    // Giai phong node cuoi
    delete l.current;
    l.current = nullptr;
    l.n = 0;

    return winner;
}

// ------------------------------------------------------------
// 9. Tim nguoi bat dau khi biet nguoi thang
// Brute force theo mo phong - de hieu va phu hop bai tap
// ------------------------------------------------------------
int findStart(int n, int winner, bool reverseDirection)
{
    for (int start = 1; start <= n; start++)
    {
        int result = simulate(n, start, reverseDirection, false);

        if (result == winner)
            return start;
    }

    return -1;
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n================ BAI 3 ================\n";
    cout << "1. Mo phong co dinh chieu kim dong ho\n";
    cout << "2. Tim nguoi thang khi nguoi 1 bat dau dem\n";
    cout << "3. Tim nguoi bat dau khi biet nguoi thang\n";
    cout << "4. Mo phong dao chieu sau moi lan loai\n";
    cout << "5. Tim nguoi thang khi nguoi 1 bat dau + dao chieu\n";
    cout << "6. Tim nguoi bat dau khi biet nguoi thang + dao chieu\n";
    cout << "0. Thoat\n";
    cout << "=======================================\n";
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    int choice;

    do
    {
        menu();
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int n, start;
            cout << "Nhap n: ";
            cin >> n;
            cout << "Nhap nguoi bat dau: ";
            cin >> start;

            simulate(n, start, false, true);
            break;
        }

        case 2:
        {
            int n;
            cout << "Nhap n: ";
            cin >> n;

            int winner = simulate(n, 1, false, true);
            cout << "Ket qua: nguoi 1 bat dau -> nguoi "
                 << winner << " chien thang.\n";
            break;
        }

        case 3:
        {
            int n, winner;
            cout << "Nhap n: ";
            cin >> n;
            cout << "Nhap nguoi chien thang k: ";
            cin >> winner;

            int start = findStart(n, winner, false);

            if (start != -1)
                cout << "Nguoi bat dau dem la nguoi "
                     << start << ".\n";
            else
                cout << "Khong tim thay.\n";
            break;
        }

        case 4:
        {
            int n, start;
            cout << "Nhap n: ";
            cin >> n;
            cout << "Nhap nguoi bat dau: ";
            cin >> start;

            simulate(n, start, true, true);
            break;
        }

        case 5:
        {
            int n;
            cout << "Nhap n: ";
            cin >> n;

            int winner = simulate(n, 1, true, true);

            cout << "Ket qua: nguoi 1 bat dau + dao chieu -> "
                 << winner << " chien thang.\n";
            break;
        }

        case 6:
        {
            int n, winner;
            cout << "Nhap n: ";
            cin >> n;
            cout << "Nhap nguoi chien thang k: ";
            cin >> winner;

            int start = findStart(n, winner, true);

            if (start != -1)
                cout << "Nguoi bat dau dem la nguoi "
                     << start << ".\n";
            else
                cout << "Khong tim thay.\n";
            break;
        }

        case 0:
            cout << "Ket thuc.\n";
            break;

        default:
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);

    return 0;
}
