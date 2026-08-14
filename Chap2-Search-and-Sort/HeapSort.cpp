#include <iostream>
using namespace std;

// ============================================================
// HEAP SORT (Sắp xếp vun đống)
//
// - Định nghĩa: Sử dụng cấu trúc Max Heap để liên tục đưa phần tử
//   lớn nhất về cuối mảng.
// - Ý tưởng:
//     + Xây dựng Max Heap.
//     + Đổi phần tử lớn nhất ở gốc với phần tử cuối.
//     + Giảm kích thước Heap.
//     + Heapify lại.
//     + Lặp đến khi mảng được sắp xếp.
//
// Độ phức tạp: O(n log n) cho mọi trường hợp.
// ============================================================

// Vun lại đống cho nút i trong mảng a có kích thước n
void heapify(int a[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // Tìm phần tử lớn nhất trong (i, con trái, con phải)
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;

    // Nếu gốc không phải lớn nhất thì đổi chỗ và vun tiếp
    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    // Xây dựng Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // Lần lượt đưa phần tử lớn nhất về cuối
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
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
    int a[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    heapSort(a, n);

    cout << "Sau heapSort: ";
    output(a, n);

    return 0;
}
