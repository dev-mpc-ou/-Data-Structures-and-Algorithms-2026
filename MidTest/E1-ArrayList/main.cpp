#include <iostream>
#include "ArrayList.h"
#include "Sort.h"

using namespace std;

// MAIN DEMO

int main()
{
    ArrayList ls;

    // 1. Nhập / xuất

    input(ls);

    cout << "\nDanh sach ban dau: ";
    output(ls);

    // 2. Tim kiem tuan tu

    int x;
    cout << "\nNhap x can tim tuan tu: ";
    cin >> x;

    int pos = linearSearch(ls, x);

    if (pos != -1)
        cout << "Tim thay tai vi tri: " << pos << endl;
    else
        cout << "Khong tim thay!\n";

    // 3. Them vao cuoi

    cout << "\nNhap x can them vao cuoi: ";
    cin >> x;

    if (add(ls, x))
        cout << "Them thanh cong!\n";
    else
        cout << "Danh sach day!\n";

    output(ls);

    // 4. Xoa cuoi

    if (deleteLast(ls))
        cout << "\nXoa cuoi thanh cong!\n";
    else
        cout << "\nDanh sach rong!\n";

    output(ls);

    // 5. Xoa tai vi tri i

    int i;
    cout << "\nNhap vi tri can xoa: ";
    cin >> i;

    if (deleteIndex(ls, i))
        cout << "Xoa thanh cong!\n";
    else
        cout << "Vi tri khong hop le!\n";

    output(ls);

    // 6. Chen vao vi tri i

    cout << "\nNhap x va vi tri can chen: ";
    cin >> x >> i;

    if (insertIndex(ls, x, i))
        cout << "Chen thanh cong!\n";
    else
        cout << "Chen that bai!\n";

    output(ls);

    // 7. Tim lon nhat / lon thu 2

    int max, secondMax;

    if (maxValue(ls, max))
        cout << "\nGia tri lon nhat: " << max << endl;

    if (secondMaxValue(ls, secondMax))
        cout << "Gia tri lon thu 2: " << secondMax << endl;
    else
        cout << "Khong co gia tri lon thu 2 phan biet!\n";

    // 8. Selection Sort

    selectionSort(ls);

    cout << "\nSelection Sort giam dan: ";
    output(ls);

    // 9. Insertion Sort

    insertionSort(ls);

    cout << "Insertion Sort giam dan: ";
    output(ls);

    // 10. Bubble Sort

    bubbleSort(ls);

    cout << "Bubble Sort giam dan: ";
    output(ls);

    // 11. Interchange Sort

    interchangeSort(ls);

    cout << "Interchange Sort giam dan: ";
    output(ls);

    // 12. Quick Sort de quy

    quickSort(ls);

    cout << "Quick Sort de quy giam dan: ";
    output(ls);

    // 13. Quick Sort khong de quy

    quickSortNonRecursive(ls);

    cout << "Quick Sort khong de quy: ";
    output(ls);

    // 14. Merge Sort

    mergeSort(ls);

    cout << "Merge Sort giam dan: ";
    output(ls);

    // 15. Heap Sort

    heapSort(ls);

    cout << "Heap Sort giam dan: ";
    output(ls);

    // 16. Binary Search
    // Luu y: danh sach hien dang giam dan.

    cout << "\nNhap x can tim bang Binary Search: ";
    cin >> x;

    pos = binarySearch(ls, x);

    if (pos != -1)
        cout << "Tim thay tai vi tri: " << pos << endl;
    else
        cout << "Khong tim thay!\n";

    return 0;
}