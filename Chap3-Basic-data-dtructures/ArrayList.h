#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
using namespace std;

#define MAX 100

// Tạo kiểu dữ liệu mảng
struct ArrayList
{
    int a[MAX];
    int size;

    // Hàm nhập vào mảng: Truyền tham chiếu vì ta sẽ thay đổi dữ liệu mảng
    void input()
    {
        cout << "Nhap so phan tu: ";
        cin >> size;

        for (int i = 0; i < size; i++) {
            cout << "a[" << i << "] = ";
            cin >> a[i];
        }
    }

    // Hàm xuất mảng: Truyền tham trị vì ta chỉ xem
    void output()
    {
        for (int i = 0; i < size; i++)
            cout << a[i] << "\t";

        cout << endl;
    }

    // Thêm vào cuối mảng
    bool add(int x)
    {
        // Kiểm tra giới hạn bộ nhớ (Nhược điểm của danh sách đặc)
        if (size >= MAX)
            return false;

        a[size] = x;
        size++; // Cập nhập: Tăng kích thước mảng lên

        return true;
    }

    // Chèn x vào vị trí i
    bool insertIndex(int x, int i)
    {
        // Kiểm tra vị trí chèn có hợp lệ không
        if (size >= MAX || i < 0 || i > size)
            return false;

        // Dời các phần tử mảng sang phải từ vị trí chèn
        for (int j = size; j > i; j--)
            a[j] = a[j - 1];

        // Chèn và cập nhật vị trí
        a[i] = x;
        size++;

        return true;
    }

    // Sửa phần tử tại vị trí i
    bool update(int i, int x)
    {
        // Kiểm tra tính hợp lệ của vị trí
        if (i < 0 || i >= size)
            return false;

        a[i] = x;

        // Trả về True khi hàm thực thi thành công
        return true;
    }

    // Xóa phần tử tại vị trí i
    bool deleteIndex(int i)
    {
        // Kiểm tra tính hợp lệ của vị trí
        if (i < 0 || i >= size)
            return false;

        // Dời các phần tử về bên TRÁI tại vị trí bị xóa
        for (int j = i; j < size - 1; j++)
            a[j] = a[j + 1];

        // Cập nhật: Giảm số lượng phần tử mảng
        size--;

        return true;
    }
};

#endif