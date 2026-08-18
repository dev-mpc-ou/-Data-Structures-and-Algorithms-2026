#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX = 100;

struct List
{
    int a[MAX];
    int n;
};

void init(List& L) { L.n = 0; }

void input(List& L)
{
    cout << "Nhap n (0.." << MAX << "): ";
    cin >> L.n;
    if (L.n < 0) L.n = 0;
    if (L.n > MAX) L.n = MAX;

    for (int i = 0; i < L.n; i++)
        cin >> L.a[i];
}

void inputFile(List& L, const string& file)
{
    ifstream fin(file);
    if (!fin)
    {
        cout << "Khong mo duoc file!\n";
        return;
    }

    fin >> L.n;
    if (L.n < 0) L.n = 0;
    if (L.n > MAX) L.n = MAX;

    for (int i = 0; i < L.n; i++)
        fin >> L.a[i];

    fin.close();
}

void output(const List& L)
{
    cout << "Danh sach: ";
    for (int i = 0; i < L.n; i++)
        cout << L.a[i] << ' ';
    cout << "\n";
}

int searchSequential(const List& L, int x)
{
    for (int i = 0; i < L.n; i++)
        if (L.a[i] == x) return i;
    return -1;
}

int searchBinary(const List& L, int x)
{
    int left = 0, right = L.n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (L.a[mid] == x) return mid;
        if (L.a[mid] < x) right = mid - 1; // danh sach giam dan
        else left = mid + 1;
    }

    return -1;
}

bool insertAt(List& L, int x, int pos)
{
    if (L.n >= MAX || pos < 0 || pos > L.n) return false;

    for (int i = L.n; i > pos; i--)
        L.a[i] = L.a[i - 1];

    L.a[pos] = x;
    L.n++;
    return true;
}

bool insertLast(List& L, int x)
{
    return insertAt(L, x, L.n);
}

bool deleteAt(List& L, int pos)
{
    if (pos < 0 || pos >= L.n) return false;

    for (int i = pos; i < L.n - 1; i++)
        L.a[i] = L.a[i + 1];

    L.n--;
    return true;
}

bool deleteLast(List& L)
{
    if (L.n == 0) return false;
    L.n--;
    return true;
}

int maxValue(const List& L)
{
    if (L.n == 0) return 0;

    int mx = L.a[0];
    for (int i = 1; i < L.n; i++)
        if (L.a[i] > mx) mx = L.a[i];

    return mx;
}

bool secondLargestDistinct(const List& L, int& ans)
{
    bool hasMax = false, hasSecond = false;
    int mx = 0, second = 0;

    for (int i = 0; i < L.n; i++)
    {
        int x = L.a[i];

        if (!hasMax || x > mx)
        {
            if (hasMax)
            {
                second = mx;
                hasSecond = true;
            }
            mx = x;
            hasMax = true;
        }
        else if (x < mx && (!hasSecond || x > second))
        {
            second = x;
            hasSecond = true;
        }
    }

    if (hasSecond)
    {
        ans = second;
        return true;
    }

    return false;
}

void selectionSort(List& L)
{
    for (int i = 0; i < L.n - 1; i++)
    {
        int maxPos = i;

        for (int j = i + 1; j < L.n; j++)
            if (L.a[j] > L.a[maxPos])
                maxPos = j;

        swap(L.a[i], L.a[maxPos]);
    }
}

void insertionSort(List& L)
{
    for (int i = 1; i < L.n; i++)
    {
        int x = L.a[i];
        int j = i - 1;

        while (j >= 0 && L.a[j] < x)
        {
            L.a[j + 1] = L.a[j];
            j--;
        }

        L.a[j + 1] = x;
    }
}

void bubbleSort(List& L)
{
    for (int i = 0; i < L.n - 1; i++)
    {
        bool changed = false;

        for (int j = 0; j < L.n - 1 - i; j++)
        {
            if (L.a[j] < L.a[j + 1])
            {
                swap(L.a[j], L.a[j + 1]);
                changed = true;
            }
        }

        if (!changed) break;
    }
}

void interchangeSort(List& L)
{
    for (int i = 0; i < L.n - 1; i++)
        for (int j = i + 1; j < L.n; j++)
            if (L.a[i] < L.a[j])
                swap(L.a[i], L.a[j]);
}

int partitionDesc(List& L, int left, int right)
{
    int pivot = L.a[(left + right) / 2];
    int i = left, j = right;

    while (i <= j)
    {
        while (L.a[i] > pivot) i++;
        while (L.a[j] < pivot) j--;

        if (i <= j)
        {
            swap(L.a[i], L.a[j]);
            i++;
            j--;
        }
    }

    return i;
}

void quickSort(List& L, int left, int right)
{
    if (left >= right) return;

    int index = partitionDesc(L, left, right);

    if (left < index - 1)
        quickSort(L, left, index - 1);

    if (index < right)
        quickSort(L, index, right);
}

void quickSortNonRecursive(List& L)
{
    if (L.n <= 1) return;

    int stack[MAX];
    int top = -1;

    stack[++top] = 0;
    stack[++top] = L.n - 1;

    while (top >= 0)
    {
        int right = stack[top--];
        int left = stack[top--];

        int index = partitionDesc(L, left, right);

        if (left < index - 1)
        {
            stack[++top] = left;
            stack[++top] = index - 1;
        }

        if (index < right)
        {
            stack[++top] = index;
            stack[++top] = right;
        }
    }
}

void mergeDesc(List& L, int left, int mid, int right)
{
    int temp[MAX];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (L.a[i] >= L.a[j])
            temp[k++] = L.a[i++];
        else
            temp[k++] = L.a[j++];
    }

    while (i <= mid) temp[k++] = L.a[i++];
    while (j <= right) temp[k++] = L.a[j++];

    for (i = 0; i < k; i++)
        L.a[left + i] = temp[i];
}

void mergeSort(List& L, int left, int right)
{
    if (left >= right) return;

    int mid = (left + right) / 2;

    mergeSort(L, left, mid);
    mergeSort(L, mid + 1, right);
    mergeDesc(L, left, mid, right);
}

void heapifyDesc(List& L, int n, int i)
{
    // Min Heap -> ket qua giam dan
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && L.a[left] < L.a[smallest])
        smallest = left;

    if (right < n && L.a[right] < L.a[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(L.a[i], L.a[smallest]);
        heapifyDesc(L, n, smallest);
    }
}

void heapSort(List& L)
{
    for (int i = L.n / 2 - 1; i >= 0; i--)
        heapifyDesc(L, L.n, i);

    for (int i = L.n - 1; i > 0; i--)
    {
        swap(L.a[0], L.a[i]);
        heapifyDesc(L, i, 0);
    }
}

void menu()
{
    List L;
    init(L);

    int choice;

    do
    {
        cout << "\n========== ON THI MANG ==========\n";
        cout << "1. Nhap ban phim\n";
        cout << "2. Nhap tu data_mang.txt\n";
        cout << "3. Xuat\n";
        cout << "4. Them cuoi\n";
        cout << "5. Them tai vi tri\n";
        cout << "6. Xoa cuoi\n";
        cout << "7. Xoa tai vi tri\n";
        cout << "8. Tim Max\n";
        cout << "9. Tim lon thu 2 phan biet\n";
        cout << "10. Selection Sort\n";
        cout << "11. Insertion Sort\n";
        cout << "12. Bubble Sort\n";
        cout << "13. Interchange Sort\n";
        cout << "14. Quick Sort\n";
        cout << "15. Quick Sort khong de quy\n";
        cout << "16. Merge Sort\n";
        cout << "17. Heap Sort\n";
        cout << "18. Tim kiem tuan tu\n";
        cout << "19. Tim kiem nhi phan\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1: input(L); break;
        case 2: inputFile(L, "data_mang.txt"); break;
        case 3: output(L); break;

        case 4:
        {
            int x; cout << "x = "; cin >> x;
            cout << (insertLast(L, x) ? "Thanh cong\n" : "Danh sach day\n");
            break;
        }

        case 5:
        {
            int x, pos;
            cout << "x, pos = "; cin >> x >> pos;
            cout << (insertAt(L, x, pos) ? "Thanh cong\n" : "Vi tri khong hop le\n");
            break;
        }

        case 6:
            cout << (deleteLast(L) ? "Da xoa\n" : "Danh sach rong\n");
            break;

        case 7:
        {
            int pos; cout << "pos = "; cin >> pos;
            cout << (deleteAt(L, pos) ? "Da xoa\n" : "Vi tri khong hop le\n");
            break;
        }

        case 8:
            if (L.n) cout << "Max = " << maxValue(L) << endl;
            else cout << "Danh sach rong\n";
            break;

        case 9:
        {
            int ans;
            if (secondLargestDistinct(L, ans))
                cout << "Lon thu 2 = " << ans << endl;
            else
                cout << "Khong co gia tri lon thu 2 phan biet\n";
            break;
        }

        case 10: selectionSort(L); output(L); break;
        case 11: insertionSort(L); output(L); break;
        case 12: bubbleSort(L); output(L); break;
        case 13: interchangeSort(L); output(L); break;
        case 14:
            if (L.n) quickSort(L, 0, L.n - 1);
            output(L);
            break;
        case 15: quickSortNonRecursive(L); output(L); break;
        case 16:
            if (L.n) mergeSort(L, 0, L.n - 1);
            output(L);
            break;
        case 17: heapSort(L); output(L); break;

        case 18:
        {
            int x; cout << "x = "; cin >> x;
            int pos = searchSequential(L, x);
            cout << "Vi tri = " << pos << endl;
            break;
        }

        case 19:
        {
            int x;
            cout << "x = "; cin >> x;
            cout << "Luu y: danh sach phai duoc sap xep giam dan.\n";
            int pos = searchBinary(L, x);
            cout << "Vi tri = " << pos << endl;
            break;
        }

        case 0: break;
        default: cout << "Khong hop le!\n";
        }

    } while (choice != 0);
}

int main()
{
    menu();
    return 0;
}
