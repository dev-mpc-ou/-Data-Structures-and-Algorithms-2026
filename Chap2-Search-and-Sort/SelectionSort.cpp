#include <iostream>
using namespace std;

// ============================================================
// SELECTION SORT (Sắp xếp chọn)
//
// - Định nghĩa: Chọn phần tử nhỏ nhất trong phần chưa sắp xếp
//   và đưa về đầu đoạn đó.
// - Ý tưởng:
//     + Với mỗi vị trí i, tìm phần tử nhỏ nhất từ i đến n-1.
//     + Đổi phần tử nhỏ nhất với a[i].
//     + Lặp lại cho vị trí tiếp theo.
//
// Độ phức tạp: O(n²)
// ============================================================

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minPos = i;

        // Tìm vị trí phần tử nhỏ nhất từ i đến n-1
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minPos])
                minPos = j;

        // Đổi phần tử nhỏ nhất với a[i]
        swap(a[i], a[minPos]);
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
    int a[] = { 34, 14, 24, 54, 84, 64, 94, 74, 4 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    selectionSort(a, n);

    cout << "Sau selectionSort: ";
    output(a, n);

    return 0;
}
