#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
using namespace std;

#define MAX 100

// ============================================================
// CẤU TRÚC DANH SÁCH ĐẶC
// ============================================================

struct ArrayList
{
    int a[MAX];
    int size;
};

// ============================================================
// NHẬP / XUẤT
// ============================================================

void input(ArrayList &ls)
{
    do
    {
        cout << "Nhap so phan tu (0.." << MAX << "): ";
        cin >> ls.size;
    }
    while (ls.size < 0 || ls.size > MAX);

    for (int i = 0; i < ls.size; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> ls.a[i];
    }
}

void output(const ArrayList &ls)
{
    for (int i = 0; i < ls.size; i++)
        cout << ls.a[i] << "\t";

    cout << endl;
}

// ============================================================
// TÌM KIẾM
// ============================================================

// Tìm tuần tự.
// Trả về vị trí đầu tiên tìm thấy, -1 nếu không có.
int linearSearch(const ArrayList &ls, int x)
{
    for (int i = 0; i < ls.size; i++)
    {
        if (ls.a[i] == x)
            return i;
    }

    return -1;
}

// Tìm nhị phân trên danh sách đã SẮP XẾP GIẢM DẦN.
// Trả về vị trí nếu tìm thấy, -1 nếu không có.
int binarySearch(const ArrayList &ls, int x)
{
    int left = 0;
    int right = ls.size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (ls.a[mid] == x)
            return mid;

        // Mảng giảm dần:
        // x lớn hơn a[mid] -> tìm bên trái
        if (x > ls.a[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

// ============================================================
// THÊM
// ============================================================

// Thêm một phần tử vào cuối danh sách.
bool add(ArrayList &ls, int x)
{
    if (ls.size >= MAX)
        return false;

    ls.a[ls.size] = x;
    ls.size++;

    return true;
}

// Thêm x vào vị trí i.
// i hợp lệ: 0 <= i <= size
bool insertIndex(ArrayList &ls, int x, int i)
{
    if (ls.size >= MAX || i < 0 || i > ls.size)
        return false;

    for (int j = ls.size; j > i; j--)
        ls.a[j] = ls.a[j - 1];

    ls.a[i] = x;
    ls.size++;

    return true;
}

// ============================================================
// XÓA
// ============================================================

// Xóa phần tử cuối danh sách.
bool deleteLast(ArrayList &ls)
{
    if (ls.size == 0)
        return false;

    ls.size--;
    return true;
}

// Xóa phần tử tại vị trí i.
bool deleteIndex(ArrayList &ls, int i)
{
    if (i < 0 || i >= ls.size)
        return false;

    for (int j = i; j < ls.size - 1; j++)
        ls.a[j] = ls.a[j + 1];

    ls.size--;

    return true;
}

// ============================================================
// GIÁ TRỊ LỚN NHẤT / LỚN THỨ 2
// ============================================================

// Tìm giá trị lớn nhất.
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

// Tìm giá trị lớn thứ 2 PHÂN BIỆT.
// Ví dụ: 10 10 8 5 -> lớn nhất = 10, lớn thứ 2 = 8.
bool secondMaxValue(const ArrayList &ls, int &result)
{
    if (ls.size < 2)
        return false;

    int max;
    maxValue(ls, max);

    bool found = false;

    for (int i = 0; i < ls.size; i++)
    {
        if (ls.a[i] < max)
        {
            if (!found || ls.a[i] > result)
            {
                result = ls.a[i];
                found = true;
            }
        }
    }

    return found;
}

#endif