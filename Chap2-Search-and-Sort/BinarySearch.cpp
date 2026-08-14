#include <iostream>
using namespace std;

// ============================================================
// TÌM KIẾM NHỊ PHÂN (Binary Search)
//
// - Chỉ thực hiện trên danh sách ĐÃ ĐƯỢC SẮP XẾP.
// - Ý tưởng: chia tập dữ liệu thành hai nửa, so sánh giá trị
//   cần tìm với phần tử ở giữa để loại bỏ một nửa dữ liệu.
//
// Độ phức tạp:
//   - Tốt nhất  : O(1)   (phần tử nằm chính giữa danh sách)
//   - Xấu nhất  : O(log n)
// ============================================================

// Trả về vị trí của x nếu tìm thấy, -1 nếu không tìm thấy
int binarySearch(const int a[], const int n, const int x)
{
    int left = 0, right = n;

    while (left < right)
    {
        int p = (left + right) / 2;

        if (x == a[p])
            return p;           // Tìm thấy
        else if (x < a[p])
            right = p;          // Tìm bên trái
        else
            left = p + 1;       // Tìm bên phải
    }

    return -1;
}

int main()
{
    // Mảng đã được sắp xếp tăng dần (yêu cầu bắt buộc)
    int a[] = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang da sap xep: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    int x;
    cout << "Nhap gia tri can tim: ";
    cin >> x;

    int pos = binarySearch(a, n, x);

    if (pos != -1)
        cout << "Tim thay " << x << " tai vi tri " << pos << endl;
    else
        cout << "Khong tim thay " << x << " trong mang" << endl;

    return 0;
}
