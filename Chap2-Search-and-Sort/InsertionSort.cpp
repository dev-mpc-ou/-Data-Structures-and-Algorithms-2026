#include <iostream>
using namespace std;

// ============================================================
// INSERTION SORT (Sắp xếp chèn)
//
// - Định nghĩa: Xây dựng dần một đoạn đã được sắp xếp bằng cách
//   chèn phần tử mới vào đúng vị trí.
// - Ý tưởng:
//     + Xem phần tử đầu tiên là đoạn đã sắp xếp.
//     + Lấy phần tử tiếp theo làm key.
//     + Dịch các phần tử lớn hơn key sang phải.
//     + Chèn key vào vị trí thích hợp.
//
// Độ phức tạp:
//   - Tốt nhất  : O(n)
//   - Trung bình: O(n²)
//   - Xấu nhất  : O(n²)
// ============================================================

void insertionSort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        // Dịch các phần tử lớn hơn key sang phải
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        // Chèn key vào vị trí thích hợp
        a[j + 1] = key;
    }
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

int main()
{
    int a[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    insertionSort(a, n);

    cout << "Sau insertionSort: ";
    output(a, n);

    return 0;
}
