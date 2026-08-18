#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ============================================================
// DEMO: BAI 2 - QUAN LY DANH SACH SINH VIEN (DSLK DOI)
//
// Chon DSLK DOI vi:
// - So luong sinh vien lon va bien dong.
// - Them/xoa khong can doi ca mang.
// - Can di toi sinh vien ke tiep va quay lai sinh vien truoc.
//
// Danh sach luon duoc sap xep GIAM DAN theo diem trung binh
// sau khi chon chuc nang sap xep.
// ============================================================

struct Student
{
    string name;
    string id;
    string className;
    string phone;
    double gpa;
};

struct Node
{
    Student data;
    Node *prev;
    Node *next;
};

// Quan ly danh sach lien ket doi
struct List
{
    Node *head;
    Node *tail;
    int n;
};

// ============================================================
// CAC THAO TAC CO BAN
// ============================================================

// ------------------------------------------------------------
// 1. Khoi tao
// ------------------------------------------------------------
void init(List &l)
{
    l.head = nullptr;
    l.tail = nullptr;
    l.n = 0;
}

// ------------------------------------------------------------
// 2. Tao Node
// ------------------------------------------------------------
Node* createNode(const Student &s)
{
    Node *p = new Node;
    p->data = s;
    p->prev = nullptr;
    p->next = nullptr;
    return p;
}

// ------------------------------------------------------------
// 3. Nhap 1 sinh vien tu ban phim
// ------------------------------------------------------------
void inputStudent(Student &s)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ho va ten: ";
    getline(cin, s.name);

    cout << "MSSV: ";
    getline(cin, s.id);

    cout << "Lop: ";
    getline(cin, s.className);

    cout << "So dien thoai: ";
    getline(cin, s.phone);

    cout << "Diem trung binh: ";
    cin >> s.gpa;
}

// ------------------------------------------------------------
// 4. Xuat day du 1 sinh vien
// ------------------------------------------------------------
void printStudent(const Student &s)
{
    cout << "Ho ten : " << s.name << "\n";
    cout << "MSSV   : " << s.id << "\n";
    cout << "Lop    : " << s.className << "\n";
    cout << "SDT    : " << s.phone << "\n";
    cout << "Diem TB: " << fixed << setprecision(2) << s.gpa << "\n";
}

// ------------------------------------------------------------
// 5. Xuat rut gon 1 sinh vien (1 dong)
// ------------------------------------------------------------
void printShort(const Student &s, int stt)
{
    cout << left
         << setw(5) << stt
         << setw(25) << s.name
         << setw(15) << s.id
         << setw(12) << s.className
         << setw(8) << fixed << setprecision(2) << s.gpa
         << "\n";
}

// ============================================================
// THEM / XOA
// ============================================================

// ------------------------------------------------------------
// 6. Them sinh vien vao cuoi danh sach
// ------------------------------------------------------------
void pushBack(List &l, const Student &s)
{
    Node *p = createNode(s);

    if (l.head == nullptr)
    {
        l.head = l.tail = p;
    }
    else
    {
        p->prev = l.tail;
        l.tail->next = p;
        l.tail = p;
    }

    l.n++;
}

// ------------------------------------------------------------
// 7. Xoa 1 Node (cap nhat head/tail tu dong)
// ------------------------------------------------------------
void removeNode(List &l, Node *p)
{
    if (p == nullptr)
        return;

    if (p->prev != nullptr)
        p->prev->next = p->next;
    else
        l.head = p->next;

    if (p->next != nullptr)
        p->next->prev = p->prev;
    else
        l.tail = p->prev;

    delete p;
    l.n--;
}

// ============================================================
// XUAT DANH SACH
// ============================================================

// ------------------------------------------------------------
// 8. Xuat day du toan bo sinh vien
// ------------------------------------------------------------
void outputFull(const List &l)
{
    if (l.head == nullptr)
    {
        cout << "Danh sach rong.\n";
        return;
    }

    Node *p = l.head;
    int stt = 1;

    while (p != nullptr)
    {
        cout << "\n===== SINH VIEN " << stt++ << " =====\n";
        printStudent(p->data);
        p = p->next;
    }
}

// ------------------------------------------------------------
// 9. Xuat rut gon - nguoi dung chon truong
// ------------------------------------------------------------
void outputShort(const List &l)
{
    if (l.head == nullptr)
    {
        cout << "Danh sach rong.\n";
        return;
    }

    int showName, showID, showClass, showPhone, showGPA;

    cout << "Hien Ho ten? (1/0): ";
    cin >> showName;
    cout << "Hien MSSV? (1/0): ";
    cin >> showID;
    cout << "Hien Lop? (1/0): ";
    cin >> showClass;
    cout << "Hien SDT? (1/0): ";
    cin >> showPhone;
    cout << "Hien Diem TB? (1/0): ";
    cin >> showGPA;

    Node *p = l.head;

    while (p != nullptr)
    {
        cout << "\n";

        if (showName)
            cout << "Ho ten: " << p->data.name << "\n";

        if (showID)
            cout << "MSSV: " << p->data.id << "\n";

        if (showClass)
            cout << "Lop: " << p->data.className << "\n";

        if (showPhone)
            cout << "SDT: " << p->data.phone << "\n";

        if (showGPA)
            cout << "Diem TB: " << fixed << setprecision(2)
                 << p->data.gpa << "\n";

        p = p->next;
    }
}

// ============================================================
// TIM KIEM / XOA THEO LOP
// ============================================================

// ------------------------------------------------------------
// 10. Tim sinh vien theo ho ten + lop
// ------------------------------------------------------------
Node* findStudent(const List &l, string name, string className)
{
    Node *p = l.head;

    while (p != nullptr)
    {
        if (p->data.name == name &&
            p->data.className == className)
            return p;

        p = p->next;
    }

    return nullptr;
}

// ------------------------------------------------------------
// 11. Xoa tat ca sinh vien thuoc mot lop
// ------------------------------------------------------------
void removeByClass(List &l, string className)
{
    Node *p = l.head;
    int count = 0;

    while (p != nullptr)
    {
        Node *next = p->next;

        if (p->data.className == className)
        {
            removeNode(l, p);
            count++;
        }

        p = next;
    }

    cout << "Da xoa " << count << " sinh vien.\n";
}

// ============================================================
// SAP XEP / CHEN
// ============================================================

// ------------------------------------------------------------
// 12. Sap xep giam dan theo GPA
// Dung doi data trong node de de hoc
// ------------------------------------------------------------
void sortByGPA(List &l)
{
    for (Node *i = l.head; i != nullptr; i = i->next)
    {
        Node *maxNode = i;

        for (Node *j = i->next; j != nullptr; j = j->next)
        {
            if (j->data.gpa > maxNode->data.gpa)
                maxNode = j;
        }

        if (maxNode != i)
            swap(i->data, maxNode->data);
    }
}

// ------------------------------------------------------------
// 13. Chen sinh vien giu thu tu giam dan theo GPA
// ------------------------------------------------------------
void insertSortedByGPA(List &l, const Student &s)
{
    Node *p = createNode(s);

    if (l.head == nullptr)
    {
        l.head = l.tail = p;
        l.n++;
        return;
    }

    // Chen dau
    if (s.gpa >= l.head->data.gpa)
    {
        p->next = l.head;
        l.head->prev = p;
        l.head = p;
        l.n++;
        return;
    }

    // Tim vi tri chen
    Node *cur = l.head;

    while (cur->next != nullptr &&
           cur->next->data.gpa > s.gpa)
    {
        cur = cur->next;
    }

    p->next = cur->next;
    p->prev = cur;

    if (cur->next != nullptr)
        cur->next->prev = p;
    else
        l.tail = p;

    cur->next = p;

    l.n++;
}

// ============================================================
// XEM TUNG SINH VIEN (NEXT / PREV)
// ============================================================

// ------------------------------------------------------------
// 14. Xem tung sinh vien - co the di next / prev
// ------------------------------------------------------------
void browseStudents(const List &l)
{
    if (l.head == nullptr)
    {
        cout << "Danh sach rong.\n";
        return;
    }

    Node *current = l.head;

    while (current != nullptr)
    {
        cout << "\n================================\n";
        printStudent(current->data);
        cout << "================================\n";
        cout << "1. Sinh vien ke tiep\n";
        cout << "2. Sinh vien truoc\n";
        cout << "0. Thoat xem\n";

        int choice;
        cout << "Chon: ";
        cin >> choice;

        if (choice == 1)
        {
            if (current->next != nullptr)
                current = current->next;
            else
                cout << "Dang o sinh vien cuoi.\n";
        }
        else if (choice == 2)
        {
            if (current->prev != nullptr)
                current = current->prev;
            else
                cout << "Dang o sinh vien dau.\n";
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            cout << "Lua chon khong hop le.\n";
        }
    }
}

// ============================================================
// DOC / GHI FILE
// Format moi dong: HoTen|MSSV|Lop|SDT|GPA
// ============================================================

// ------------------------------------------------------------
// 15. Luu danh sach ra file
// ------------------------------------------------------------
void saveToFile(const List &l, string filename)
{
    ofstream out(filename);

    if (!out)
    {
        cout << "Khong mo duoc file.\n";
        return;
    }

    Node *p = l.head;

    while (p != nullptr)
    {
        out << p->data.name << "|"
            << p->data.id << "|"
            << p->data.className << "|"
            << p->data.phone << "|"
            << p->data.gpa << "\n";

        p = p->next;
    }

    out.close();

    cout << "Da luu file " << filename << ".\n";
}

// ------------------------------------------------------------
// 16. Phan tich 1 dong file thanh sinh vien
// ------------------------------------------------------------
bool parseStudent(string line, Student &s)
{
    size_t p1 = line.find('|');
    size_t p2 = line.find('|', p1 + 1);
    size_t p3 = line.find('|', p2 + 1);
    size_t p4 = line.find('|', p3 + 1);

    if (p1 == string::npos ||
        p2 == string::npos ||
        p3 == string::npos ||
        p4 == string::npos)
        return false;

    s.name = line.substr(0, p1);
    s.id = line.substr(p1 + 1, p2 - p1 - 1);
    s.className = line.substr(p2 + 1, p3 - p2 - 1);
    s.phone = line.substr(p3 + 1, p4 - p3 - 1);

    try
    {
        s.gpa = stod(line.substr(p4 + 1));
    }
    catch (...)
    {
        return false;
    }

    return true;
}

// ------------------------------------------------------------
// 17. Doc danh sach tu file
// ------------------------------------------------------------
void loadFromFile(List &l, string filename)
{
    ifstream in(filename);

    if (!in)
    {
        cout << "Khong mo duoc file.\n";
        return;
    }

    // Xoa danh sach cu
    Node *p = l.head;

    while (p != nullptr)
    {
        Node *next = p->next;
        delete p;
        p = next;
    }

    init(l);

    string line;

    while (getline(in, line))
    {
        Student s;

        if (parseStudent(line, s))
            pushBack(l, s);
    }

    in.close();

    cout << "Da doc file " << filename
         << ". So sinh vien: " << l.n << "\n";
}

// ============================================================
// GIAI PHONG
// ============================================================

// ------------------------------------------------------------
// 18. Xoa toan bo danh sach
// ------------------------------------------------------------
void clear(List &l)
{
    Node *p = l.head;

    while (p != nullptr)
    {
        Node *next = p->next;
        delete p;
        p = next;
    }

    init(l);
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n================ BAI 2 ================\n";
    cout << "1. Nhap sinh vien tu ban phim\n";
    cout << "2. Doc danh sach tu file\n";
    cout << "3. Xuat day du\n";
    cout << "4. Xuat rut gon - chon truong\n";
    cout << "5. Tim theo ho ten + lop\n";
    cout << "6. Xoa tat ca sinh vien theo lop\n";
    cout << "7. Sap xep giam dan theo GPA\n";
    cout << "8. Chen sinh vien giu thu tu GPA\n";
    cout << "9. Xem tung sinh vien (Next/Prev)\n";
    cout << "10. Luu danh sach ra file\n";
    cout << "0. Thoat\n";
    cout << "=======================================\n";
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    List l;
    init(l);

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
            Student s;
            inputStudent(s);
            pushBack(l, s);
            cout << "Da them sinh vien.\n";
            break;
        }

        case 2:
        {
            string filename;
            cout << "Ten file: ";
            cin >> filename;
            loadFromFile(l, filename);
            break;
        }

        case 3:
            outputFull(l);
            break;

        case 4:
            outputShort(l);
            break;

        case 5:
        {
            string name, className;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ho va ten: ";
            getline(cin, name);

            cout << "Lop: ";
            getline(cin, className);

            Node *p = findStudent(l, name, className);

            if (p != nullptr)
                printStudent(p->data);
            else
                cout << "Khong ton tai sinh vien.\n";

            break;
        }

        case 6:
        {
            string className;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Nhap lop can xoa: ";
            getline(cin, className);

            removeByClass(l, className);
            break;
        }

        case 7:
            sortByGPA(l);
            cout << "Da sap xep giam dan theo GPA.\n";
            break;

        case 8:
        {
            Student s;
            inputStudent(s);
            insertSortedByGPA(l, s);
            cout << "Da chen giu thu tu GPA.\n";
            break;
        }

        case 9:
            browseStudents(l);
            break;

        case 10:
        {
            string filename;
            cout << "Ten file: ";
            cin >> filename;
            saveToFile(l, filename);
            break;
        }

        case 0:
            cout << "Ket thuc.\n";
            break;

        default:
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);

    clear(l);
    return 0;
}
