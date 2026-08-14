#include <iostream>
using namespace std;

// ============================================================
// BUBBLE SORT (Sắp xếp nổi bọt)
//
// - Định nghĩa: Liên tục so sánh hai phần tử kề nhau và đổi chỗ
//   nếu chúng sai thứ tự.
// - Ý tưởng:
//     + So sánh từng cặp kề nhau.
//     + Sau mỗi lượt, phần tử lớn nhất còn lại "nổi" về cuối.
//     + Lặp lại cho phần chưa sắp xếp.
//
// Độ phức tạp:
//   - Tốt nhất  : O(n)   (nếu có kiểm tra dừng sớm)
//   - Trung bình: O(n²)
//   - Xấu nhất  : O(n²)
// ============================================================

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

// Phiên bản có kiểm tra dừng sớm (Best O(n) khi mảng đã sắp xếp)
void bubbleSortOptimized(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        // Không có hoán vị nào -> mảng đã sắp xếp, dừng sớm
        if (!swapped)
            break;
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
    int a[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    bubbleSort(a, n);

    cout << "Sau bubbleSort: ";
    output(a, n);

    return 0;
}
