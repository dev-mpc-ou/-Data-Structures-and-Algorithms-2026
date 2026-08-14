#ifndef SORT_H
#define SORT_H

#include "ArrayList.h"
#include <algorithm>
#include <stack>
using namespace std;

// ============================================================
// CÁC HÀM PHỤ
// ============================================================

void swapValue(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

// ============================================================
// 1. SELECTION SORT - GIẢM DẦN
// ============================================================

void selectionSort(ArrayList &ls)
{
    for (int i = 0; i < ls.size - 1; i++)
    {
        int maxPos = i;

        for (int j = i + 1; j < ls.size; j++)
        {
            if (ls.a[j] > ls.a[maxPos])
                maxPos = j;
        }

        swapValue(ls.a[i], ls.a[maxPos]);
    }
}

// ============================================================
// 2. INSERTION SORT - GIẢM DẦN
// ============================================================

void insertionSort(ArrayList &ls)
{
    for (int i = 1; i < ls.size; i++)
    {
        int key = ls.a[i];
        int j = i - 1;

        while (j >= 0 && ls.a[j] < key)
        {
            ls.a[j + 1] = ls.a[j];
            j--;
        }

        ls.a[j + 1] = key;
    }
}

// ============================================================
// 3. BUBBLE SORT - GIẢM DẦN
// ============================================================

void bubbleSort(ArrayList &ls)
{
    for (int i = 0; i < ls.size - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < ls.size - i - 1; j++)
        {
            if (ls.a[j] < ls.a[j + 1])
            {
                swapValue(ls.a[j], ls.a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// ============================================================
// 4. INTERCHANGE SORT - GIẢM DẦN
// ============================================================

void interchangeSort(ArrayList &ls)
{
    for (int i = 0; i < ls.size - 1; i++)
    {
        for (int j = i + 1; j < ls.size; j++)
        {
            if (ls.a[i] < ls.a[j])
                swapValue(ls.a[i], ls.a[j]);
        }
    }
}

// ============================================================
// 5. QUICK SORT - ĐỆ QUY - GIẢM DẦN
// ============================================================

// Dùng phần tử cuối làm pivot.
// Sau partition:
// [l..p-1] >= pivot
// [p] = pivot
// [p+1..r] <= pivot
int partitionDesc(ArrayList &ls, int left, int right)
{
    int pivot = ls.a[right];
    int i = left - 1;

    for (int j = left; j < right; j++)
    {
        if (ls.a[j] > pivot)
        {
            i++;
            swapValue(ls.a[i], ls.a[j]);
        }
    }

    swapValue(ls.a[i + 1], ls.a[right]);

    return i + 1;
}

void quickSort(ArrayList &ls, int left, int right)
{
    if (left >= right)
        return;

    int p = partitionDesc(ls, left, right);

    quickSort(ls, left, p - 1);
    quickSort(ls, p + 1, right);
}

// Hàm gọi Quick Sort đệ quy.
void quickSort(ArrayList &ls)
{
    if (ls.size > 1)
        quickSort(ls, 0, ls.size - 1);
}

// ============================================================
// 6. QUICK SORT KHÔNG ĐỆ QUY - GIẢM DẦN
// ============================================================

// Dùng stack để lưu các đoạn [left, right] cần xử lý.
void quickSortNonRecursive(ArrayList &ls)
{
    if (ls.size <= 1)
        return;

    stack<pair<int, int>> st;
    st.push({0, ls.size - 1});

    while (!st.empty())
    {
        int left = st.top().first;
        int right = st.top().second;
        st.pop();

        if (left >= right)
            continue;

        int p = partitionDesc(ls, left, right);

        if (left < p - 1)
            st.push({left, p - 1});

        if (p + 1 < right)
            st.push({p + 1, right});
    }
}

// ============================================================
// 7. MERGE SORT - GIẢM DẦN
// ============================================================

void mergeDesc(ArrayList &ls, int left, int mid, int right)
{
    int temp[MAX];

    int i = left;
    int j = mid + 1;
    int k = 0;

    // Phần tử lớn hơn được đưa vào trước.
    while (i <= mid && j <= right)
    {
        if (ls.a[i] >= ls.a[j])
            temp[k++] = ls.a[i++];
        else
            temp[k++] = ls.a[j++];
    }

    while (i <= mid)
        temp[k++] = ls.a[i++];

    while (j <= right)
        temp[k++] = ls.a[j++];

    for (int t = 0; t < k; t++)
        ls.a[left + t] = temp[t];
}

void mergeSort(ArrayList &ls, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(ls, left, mid);
    mergeSort(ls, mid + 1, right);

    mergeDesc(ls, left, mid, right);
}

void mergeSort(ArrayList &ls)
{
    if (ls.size > 1)
        mergeSort(ls, 0, ls.size - 1);
}

// ============================================================
// 8. HEAP SORT - GIẢM DẦN
// ============================================================

// Để sắp xếp giảm dần, xây Min Heap.
// Sau mỗi lần đưa phần tử nhỏ nhất về cuối,
// kết quả cuối cùng sẽ giảm dần.
void heapifyMin(ArrayList &ls, int heapSize, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && ls.a[left] < ls.a[smallest])
        smallest = left;

    if (right < heapSize && ls.a[right] < ls.a[smallest])
        smallest = right;

    if (smallest != i)
    {
        swapValue(ls.a[i], ls.a[smallest]);
        heapifyMin(ls, heapSize, smallest);
    }
}

void heapSort(ArrayList &ls)
{
    // Xây Min Heap.
    for (int i = ls.size / 2 - 1; i >= 0; i--)
        heapifyMin(ls, ls.size, i);

    // Đưa phần tử nhỏ nhất về cuối.
    for (int i = ls.size - 1; i > 0; i--)
    {
        swapValue(ls.a[0], ls.a[i]);
        heapifyMin(ls, i, 0);
    }
}

#endif