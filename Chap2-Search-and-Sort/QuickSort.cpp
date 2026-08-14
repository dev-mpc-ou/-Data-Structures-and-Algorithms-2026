#include <iostream>
using namespace std;

// ============================================================
// QUICK SORT (Sắp xếp nhanh)
//
// - Định nghĩa: Chọn một phần tử làm pivot, chia mảng thành hai
//   phía rồi đệ quy sắp xếp.
// - Ý tưởng: Chọn pivot ==> Partition (Phân chia) ==> Đệ quy hai phía
//     + Phần nhỏ hơn pivot đưa sang trái.
//     + Phần lớn hơn pivot đưa sang phải.
//     + Tiếp tục với hai đoạn con.
//
// Độ phức tạp:
//   - Trung bình: O(n log n)
//   - Xấu nhất  : O(n²)
// ============================================================

// Phân chia: trả về vị trí cuối cùng của pivot
int partition(int a[], int l, int r)
{
    int pivot = a[r];
    int i = l - 1;

    // Phần nhỏ hơn pivot đưa sang trái
    for (int j = l; j < r; j++)
    {
        if (a[j] < pivot)
            swap(a[++i], a[j]);
    }

    // Đưa pivot về đúng vị trí
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quickSort(int a[], int l, int r)
{
    if (l >= r)
        return;

    int p = partition(a, l, r);
    quickSort(a, l, p - 1);
    quickSort(a, p + 1, r);
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

int main()
{
    int a[] = { 10, 80, 30, 90, 40, 50, 70 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    quickSort(a, 0, n - 1);

    cout << "Sau quickSort: ";
    output(a, n);

    return 0;
}
