#include <iostream>
using namespace std;

#define MAX 100

// ============================================================
// KHAI BÁO CẤU TRÚC DANH SÁCH
// ============================================================

struct ArrayList
{
    int a[MAX];
    int size;
};

// ============================================================
// NHẬP / XUẤT
// ============================================================

// Nhập danh sách
void input(ArrayList &ls)
{
    cout << "Nhap so phan tu: ";
    cin >> ls.size;

    for (int i = 0; i < ls.size; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> ls.a[i];
    }
}

// Xuất danh sách
void output(const ArrayList ls)
{
    for (int i = 0; i < ls.size; i++)
        cout << ls.a[i] << "\t";

    cout << endl;
}

// ============================================================
// TÌM KIẾM
// ============================================================

// Tìm phần tử có giá trị x
// Trả về vị trí nếu tìm thấy, -1 nếu không tìm thấy
int search(const ArrayList &ls, int x)
{
    for (int i = 0; i < ls.size; i++)
    {
        if (ls.a[i] == x)
            return i;
    }

    return -1;
}

// ============================================================
// THÊM
// ============================================================

// Thêm một phần tử vào cuối danh sách
bool add(ArrayList &ls, int x)
{
    // Kiểm tra danh sách đã đầy chưa
    if (ls.size >= MAX)
        return false;

    ls.a[ls.size] = x;
    ls.size++;

    return true;
}

// Thêm một phần tử vào vị trí i
bool insertIndex(ArrayList &ls, int x, int i)
{
    // i có thể bằng size vì có thể chèn vào cuối
    if (ls.size >= MAX || i < 0 || i > ls.size)
        return false;

    // Dời các phần tử sang phải
    for (int j = ls.size; j > i; j--)
        ls.a[j] = ls.a[j - 1];

    ls.a[i] = x;
    ls.size++;

    return true;
}

// ============================================================
// XÓA
// ============================================================

// Xóa phần tử cuối danh sách
bool deleteLast(ArrayList &ls)
{
    // Danh sách rỗng
    if (ls.size == 0)
        return false;

    // Chỉ cần giảm size
    ls.size--;

    return true;
}

// Xóa phần tử tại vị trí i
bool deleteIndex(ArrayList &ls, int i)
{
    // Kiểm tra vị trí
    if (i < 0 || i >= ls.size)
        return false;

    // Dời các phần tử phía sau sang trái
    for (int j = i; j < ls.size - 1; j++)
        ls.a[j] = ls.a[j + 1];

    // Cập nhật số lượng phần tử
    ls.size--;

    return true;
}

// ============================================================
// SỬA
// ============================================================

// Sửa phần tử tại vị trí i
bool update(ArrayList &ls, int i, int x)
{
    if (i < 0 || i >= ls.size)
        return false;

    ls.a[i] = x;

    return true;
}

// ============================================================
// TÌM GIÁ TRỊ LỚN NHẤT
// ============================================================

// Trả về giá trị lớn nhất
bool maxValue(const ArrayList &ls, int &result)
{
    if (ls.size == 0)
        return false;

    result = ls.a[0];

    for (int i = 1; i < ls.size; i++)
    {
        if (ls.a[i] > result)
            result = ls.a[i];
    }

    return true;
}

// ============================================================
// TÌM GIÁ TRỊ LỚN THỨ 2
// ============================================================

// Tìm giá trị lớn thứ 2, không tính trùng giá trị lớn nhất
bool secondMaxValue(const ArrayList &ls, int &result)
{
    if (ls.size < 2)
        return false;

    int max = ls.a[0];

    // Tìm giá trị lớn nhất
    for (int i = 1; i < ls.size; i++)
    {
        if (ls.a[i] > max)
            max = ls.a[i];
    }

    // Tìm phần tử đầu tiên nhỏ hơn max
    bool found = false;

    for (int i = 0; i < ls.size; i++)
    {
        if (ls.a[i] < max)
        {
            result = ls.a[i];
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    // Tìm giá trị lớn nhất nhưng vẫn nhỏ hơn max
    for (int i = 0; i < ls.size; i++)
    {
        if (ls.a[i] < max && ls.a[i] > result)
            result = ls.a[i];
    }

    return true;
}

// ============================================================
// MAIN
// ============================================================

int main()
{
    ArrayList ls;

    // 1. Nhập danh sách
    input(ls);

    // 2. Xuất danh sách
    cout << "\nDanh sach: ";
    output(ls);

    // 3. Tìm phần tử
    int x;
    cout << "\nNhap x can tim: ";
    cin >> x;

    int pos = search(ls, x);

    if (pos != -1)
        cout << "Tim thay tai vi tri: " << pos << endl;
    else
        cout << "Khong tim thay!\n";

    // 4. Thêm vào cuối
    add(ls, 10);

    // 5. Chèn vào vị trí
    insertIndex(ls, 20, 1);

    // 6. Sửa
    update(ls, 0, 99);

    // 7. Xóa cuối
    deleteLast(ls);

    // 8. Xóa tại vị trí
    deleteIndex(ls, 2);

    cout << "\nDanh sach sau thao tac: ";
    output(ls);

    // 9. Tìm lớn nhất
    int max;

    if (maxValue(ls, max))
        cout << "Gia tri lon nhat: " << max << endl;
    else
        cout << "Danh sach rong!\n";

    // 10. Tìm lớn thứ 2
    int secondMax;

    if (secondMaxValue(ls, secondMax))
        cout << "Gia tri lon thu 2: " << secondMax << endl;
    else
        cout << "Khong co gia tri lon thu 2 phan biet!\n";

    return 0;
}