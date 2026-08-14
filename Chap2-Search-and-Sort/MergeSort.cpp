#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// MERGE SORT (Sắp xếp trộn)
//
// - Định nghĩa: Chia mảng thành các phần nhỏ, sắp xếp từng phần
//   rồi trộn lại.
// - Ý tưởng: Chia ==> Sắp xếp ==> Trộn
//     + Chia mảng thành 2 nửa.
//     + Đệ quy sắp xếp từng nửa.
//     + Merge hai nửa đã sắp xếp.
//
// Độ phức tạp: O(n log n) cho mọi trường hợp.
// ============================================================

// Trộn hai nửa [l..m] và [m+1..r] đã sắp xếp thành [l..r] đã sắp xếp
void merge(int a[], int l, int m, int r)
{
    int i = l, j = m + 1;
    vector<int> temp;

    // Trộn hai nửa đã sắp xếp
    while (i <= m && j <= r)
    {
        if (a[i] <= a[j])
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    // Đưa phần còn lại của mỗi nửa vào temp
    while (i <= m)
        temp.push_back(a[i++]);
    while (j <= r)
        temp.push_back(a[j++]);

    // Ghi ngược lại mảng
    for (int k = 0; k < temp.size(); k++)
        a[l + k] = temp[k];
}

void mergeSort(int a[], int l, int r)
{
    if (l >= r)
        return;

    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

void output(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << "\t";
    cout << endl;
}

int main()
{
    int a[] = { 38, 27, 43, 3, 9, 82, 10 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Mang ban dau: ";
    output(a, n);

    mergeSort(a, 0, n - 1);

    cout << "Sau mergeSort: ";
    output(a, n);

    return 0;
}
