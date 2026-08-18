#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Student
{
    string mssv;
    string hoTen;
    string lop;
    string sdt;
    double gpa;
};

struct Node
{
    Student data;
    Node* next;
};

struct List
{
    Node* head;
    Node* tail;
    int n;
};

void init(List& L)
{
    L.head = L.tail = nullptr;
    L.n = 0;
}

Node* createNode(const Student& sv)
{
    Node* p = new Node;
    p->data = sv;
    p->next = nullptr;
    return p;
}

void addTail(List& L, const Student& sv)
{
    Node* p = createNode(sv);

    if (L.head == nullptr)
        L.head = L.tail = p;
    else
    {
        L.tail->next = p;
        L.tail = p;
    }

    L.n++;
}

void addHead(List& L, const Student& sv)
{
    Node* p = createNode(sv);

    p->next = L.head;
    L.head = p;

    if (L.tail == nullptr)
        L.tail = p;

    L.n++;
}

bool deleteByMSSV(List& L, const string& mssv)
{
    Node* p = L.head;
    Node* prev = nullptr;

    while (p != nullptr)
    {
        if (p->data.mssv == mssv)
        {
            if (prev == nullptr)
                L.head = p->next;
            else
                prev->next = p->next;

            if (p == L.tail)
                L.tail = prev;

            delete p;
            L.n--;
            return true;
        }

        prev = p;
        p = p->next;
    }

    return false;
}

int deleteByClass(List& L, const string& lop)
{
    int count = 0;
    Node* p = L.head;
    Node* prev = nullptr;

    while (p != nullptr)
    {
        if (p->data.lop == lop)
        {
            Node* del = p;

            if (prev == nullptr)
            {
                L.head = p->next;
                p = L.head;
            }
            else
            {
                prev->next = p->next;
                p = prev->next;
            }

            if (del == L.tail)
                L.tail = prev;

            delete del;
            L.n--;
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

Node* searchMSSV(List& L, const string& mssv)
{
    Node* p = L.head;

    while (p != nullptr)
    {
        if (p->data.mssv == mssv)
            return p;

        p = p->next;
    }

    return nullptr;
}

void printFull(const Student& sv)
{
    cout << "MSSV: " << sv.mssv << '\n'
         << "Ho ten: " << sv.hoTen << '\n'
         << "Lop: " << sv.lop << '\n'
         << "SDT: " << sv.sdt << '\n'
         << "GPA: " << fixed << setprecision(2) << sv.gpa << '\n';
}

void outputFull(const List& L)
{
    cout << "\n========== DANH SACH SINH VIEN ==========\n";

    Node* p = L.head;

    while (p != nullptr)
    {
        printFull(p->data);
        cout << "--------------------------\n";
        p = p->next;
    }

    if (L.head == nullptr)
        cout << "Danh sach rong!\n";
}

void outputShort(const List& L)
{
    cout << "\nMSSV | HoTen | Lop | GPA\n";
    cout << "-------------------------------------------\n";

    Node* p = L.head;

    while (p != nullptr)
    {
        cout << p->data.mssv << " | "
             << p->data.hoTen << " | "
             << p->data.lop << " | "
             << fixed << setprecision(2)
             << p->data.gpa << '\n';

        p = p->next;
    }
}

bool parseStudent(const string& line, Student& sv)
{
    stringstream ss(line);
    string gpaText;

    if (!getline(ss, sv.mssv, '|')) return false;
    if (!getline(ss, sv.hoTen, '|')) return false;
    if (!getline(ss, sv.lop, '|')) return false;
    if (!getline(ss, sv.sdt, '|')) return false;
    if (!getline(ss, gpaText)) return false;

    try
    {
        sv.gpa = stod(gpaText);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool loadFile(List& L, const string& filename)
{
    ifstream fin(filename);

    if (!fin)
        return false;

    string line;
    int count = 0;

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        Student sv;

        if (parseStudent(line, sv))
        {
            addTail(L, sv);
            count++;
        }
    }

    fin.close();

    cout << "Da doc " << count << " sinh vien.\n";
    return true;
}

bool saveFile(const List& L, const string& filename)
{
    ofstream fout(filename);

    if (!fout)
        return false;

    Node* p = L.head;

    while (p != nullptr)
    {
        fout << p->data.mssv << '|'
             << p->data.hoTen << '|'
             << p->data.lop << '|'
             << p->data.sdt << '|'
             << fixed << setprecision(2)
             << p->data.gpa << '\n';

        p = p->next;
    }

    fout.close();
    return true;
}

Student inputStudent()
{
    Student sv;

    cout << "MSSV: ";
    cin >> ws;
    getline(cin, sv.mssv);

    cout << "Ho ten: ";
    getline(cin, sv.hoTen);

    cout << "Lop: ";
    getline(cin, sv.lop);

    cout << "SDT: ";
    getline(cin, sv.sdt);

    cout << "GPA: ";
    cin >> sv.gpa;

    return sv;
}

void sortGpaDesc(List& L)
{
    for (Node* i = L.head; i != nullptr; i = i->next)
    {
        Node* maxNode = i;

        for (Node* j = i->next; j != nullptr; j = j->next)
        {
            if (j->data.gpa > maxNode->data.gpa)
                maxNode = j;
        }

        if (maxNode != i)
            swap(i->data, maxNode->data);
    }
}

void insertKeepGpaDesc(List& L, const Student& sv)
{
    Node* p = createNode(sv);

    if (L.head == nullptr || sv.gpa > L.head->data.gpa)
    {
        p->next = L.head;
        L.head = p;

        if (L.tail == nullptr)
            L.tail = p;

        L.n++;
        return;
    }

    Node* q = L.head;

    while (q->next != nullptr &&
           q->next->data.gpa >= sv.gpa)
    {
        q = q->next;
    }

    p->next = q->next;
    q->next = p;

    if (p->next == nullptr)
        L.tail = p;

    L.n++;
}

void viewStudents(List& L)
{
    if (L.head == nullptr)
    {
        cout << "Danh sach rong!\n";
        return;
    }

    vector<Node*> nodes;
    Node* p = L.head;

    while (p != nullptr)
    {
        nodes.push_back(p);
        p = p->next;
    }

    int pos = 0;
    char c;

    do
    {
        cout << "\n===== XEM SINH VIEN " << pos + 1
             << "/" << nodes.size() << " =====\n";

        printFull(nodes[pos]->data);

        cout << "\n[n] Ke tiep | [p] Quay lai | [q] Thoat: ";
        cin >> c;

        if (c == 'n' && pos + 1 < (int)nodes.size())
            pos++;
        else if (c == 'p' && pos > 0)
            pos--;

    } while (c != 'q');
}

void clear(List& L)
{
    while (L.head != nullptr)
    {
        Node* p = L.head;
        L.head = L.head->next;
        delete p;
    }

    L.tail = nullptr;
    L.n = 0;
}

int main()
{
    List L;
    init(L);

    int choice;

    do
    {
        cout << "\n============================================\n";
        cout << "   ON THI LINKED LIST - QUAN LY SINH VIEN\n";
        cout << "============================================\n";
        cout << "1. Nhap 1 sinh vien\n";
        cout << "2. Doc sinh vien tu sinhvien.txt\n";
        cout << "3. Xuat day du\n";
        cout << "4. Xuat rut gon\n";
        cout << "5. Tim theo MSSV\n";
        cout << "6. Tim theo HoTen + Lop\n";
        cout << "7. Xoa theo MSSV\n";
        cout << "8. Xoa theo Lop\n";
        cout << "9. Sap xep GPA giam dan\n";
        cout << "10. Chen giu thu tu GPA\n";
        cout << "11. Xem tung sinh vien\n";
        cout << "12. Luu ra sinhvien_out.txt\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTail(L, inputStudent());
            break;

        case 2:
            if (!loadFile(L, "sinhvien.txt"))
                cout << "Khong mo duoc sinhvien.txt\n";
            break;

        case 3:
            outputFull(L);
            break;

        case 4:
            outputShort(L);
            break;

        case 5:
        {
            string mssv;
            cout << "MSSV: ";
            cin >> ws;
            getline(cin, mssv);

            Node* p = searchMSSV(L, mssv);

            if (p) printFull(p->data);
            else cout << "Khong tim thay!\n";

            break;
        }

        case 6:
        {
            string name, lop;

            cout << "Ho ten: ";
            cin >> ws;
            getline(cin, name);

            cout << "Lop: ";
            getline(cin, lop);

            Node* p = L.head;
            bool found = false;

            while (p != nullptr)
            {
                if (p->data.hoTen == name &&
                    p->data.lop == lop)
                {
                    printFull(p->data);
                    found = true;
                }

                p = p->next;
            }

            if (!found)
                cout << "Khong tim thay!\n";

            break;
        }

        case 7:
        {
            string mssv;
            cout << "MSSV: ";
            cin >> ws;
            getline(cin, mssv);

            cout << (deleteByMSSV(L, mssv)
                ? "Da xoa!\n"
                : "Khong tim thay!\n");

            break;
        }

        case 8:
        {
            string lop;
            cout << "Lop can xoa: ";
            cin >> ws;
            getline(cin, lop);

            cout << "Da xoa "
                 << deleteByClass(L, lop)
                 << " sinh vien.\n";

            break;
        }

        case 9:
            sortGpaDesc(L);
            cout << "Da sap xep GPA giam dan.\n";
            break;

        case 10:
        {
            Student sv = inputStudent();
            insertKeepGpaDesc(L, sv);
            cout << "Da chen vao dung vi tri GPA.\n";
            break;
        }

        case 11:
            viewStudents(L);
            break;

        case 12:
            if (saveFile(L, "sinhvien_out.txt"))
                cout << "Da luu file.\n";
            else
                cout << "Khong ghi duoc file.\n";
            break;

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    clear(L);
    return 0;
}
