#include <iostream>
using namespace std;

// ============================================================
// INTERCHANGE SORT (Sắp xếp đổi chỗ trực tiếp)
//
// - Định nghĩa: So sánh phần tử hiện tại với từng phần tử phía
//   sau; nếu gặp phần tử nhỏ hơn thì đổi chỗ.
// - Ý tưởng:
//     + Chọn a[i].
//     + So sánh lần lượt với a[i+1] ... a[n-1].
//     + Nếu a[j] < a[i] thì đổi chỗ.
//
// Độ phức tạp: O(n²)
// ============================================================

void interchangeSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[i])
                swap(a[i], a[j]);
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

int main()
{
    int a[] = { 5, 3, 8, 1, 9, 2 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    interchangeSort(a, n);

    cout << "Sau interchangeSort: ";
    output(a, n);

    return 0;
}
