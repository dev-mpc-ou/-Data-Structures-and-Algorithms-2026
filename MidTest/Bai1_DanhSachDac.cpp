#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100

// ============================================================
// DEMO: BAI 1 - DANH SACH DAC (ARRAY LIST)
// - Cac thao tac co ban: khoi tao, nhap, xuat, tim kiem,
//   them cuoi, xoa cuoi, xoa tai vi tri, them tai vi tri,
//   tim lon nhat, tim lon thu 2.
// - Cac thuat toan sap xep GIAM DAN: selection, insertion,
//   bubble, interchange, quick (de quy + khong de quy),
//   merge, heap.
// - Tim kiem: tuan tu va nhi phan.
// ============================================================

struct List
{
    int a[MAX];
    int n;
};

// ============================================================
// CAC THAO TAC CO BAN
// ============================================================

// ------------------------------------------------------------
// 1. Khoi tao danh sach rong
// ------------------------------------------------------------
void init(List &l)
{
    l.n = 0;
}

// ------------------------------------------------------------
// 2. Nhap danh sach
// ------------------------------------------------------------
void input(List &l)
{
    do
    {
        cout << "Nhap so luong phan tu (0.." << MAX << "): ";
        cin >> l.n;
    } while (l.n < 0 || l.n > MAX);

    for (int i = 0; i < l.n; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> l.a[i];
    }
}

// ------------------------------------------------------------
// 3. Xuat danh sach
// ------------------------------------------------------------
void output(const List &l)
{
    if (l.n == 0)
    {
        cout << "Danh sach rong!\n";
        return;
    }

    cout << "Danh sach: ";
    for (int i = 0; i < l.n; i++)
        cout << l.a[i] << " ";
    cout << "\n";
}

// ------------------------------------------------------------
// 4. Tim phan tu x - tra ve vi tri dau tien
// ------------------------------------------------------------
int searchPosition(const List &l, int x)
{
    for (int i = 0; i < l.n; i++)
    {
        if (l.a[i] == x)
            return i;
    }

    return -1;
}

// ------------------------------------------------------------
// 5. Them phan tu x vao cuoi danh sach
// ------------------------------------------------------------
bool addLast(List &l, int x)
{
    if (l.n == MAX)
        return false;

    l.a[l.n] = x;
    l.n++;
    return true;
}

// ------------------------------------------------------------
// 6. Xoa phan tu cuoi danh sach
// ------------------------------------------------------------
bool deleteLast(List &l, int &x)
{
    if (l.n == 0)
        return false;

    x = l.a[l.n - 1];
    l.n--;
    return true;
}

// ------------------------------------------------------------
// 7. Xoa phan tu tai vi tri i (i: 0..n-1)
// ------------------------------------------------------------
bool deleteAt(List &l, int i, int &x)
{
    if (i < 0 || i >= l.n)
        return false;

    x = l.a[i];

    for (int j = i; j < l.n - 1; j++)
        l.a[j] = l.a[j + 1];

    l.n--;
    return true;
}

// ------------------------------------------------------------
// 8. Them phan tu x tai vi tri i (i: 0..n)
// ------------------------------------------------------------
bool insertAt(List &l, int i, int x)
{
    if (l.n == MAX || i < 0 || i > l.n)
        return false;

    for (int j = l.n; j > i; j--)
        l.a[j] = l.a[j - 1];

    l.a[i] = x;
    l.n++;

    return true;
}

// ------------------------------------------------------------
// 9. Tim gia tri lon nhat
// ------------------------------------------------------------
bool maxValue(const List &l, int &x)
{
    if (l.n == 0)
        return false;

    x = l.a[0];

    for (int i = 1; i < l.n; i++)
        if (l.a[i] > x)
            x = l.a[i];

    return true;
}

// ------------------------------------------------------------
// 10. Tim gia tri lon thu 2 (khac gia tri lon nhat)
// ------------------------------------------------------------
bool secondMax(const List &l, int &x)
{
    if (l.n < 2)
        return false;

    int max1, max2 = 0;

    // Tim gia tri lon nhat truoc.
    if (!maxValue(l, max1))
        return false;

    // Tim gia tri lon nhat nhung phai nho hon max1.
    bool hasSecond = false;

    for (int i = 0; i < l.n; i++)
    {
        if (l.a[i] < max1)
        {
            if (!hasSecond || l.a[i] > max2)
            {
                max2 = l.a[i];
                hasSecond = true;
            }
        }
    }

    if (!hasSecond)
        return false; // Tat ca phan tu bang nhau

    x = max2;
    return true;
}

// ============================================================
// CAC THUAT TOAN SAP XEP (GIAM DAN)
// ============================================================

// ------------------------------------------------------------
// 11. Selection Sort giam dan
// ------------------------------------------------------------
void selectionSortDesc(List &l)
{
    for (int i = 0; i < l.n - 1; i++)
    {
        int posMax = i;

        for (int j = i + 1; j < l.n; j++)
            if (l.a[j] > l.a[posMax])
                posMax = j;

        swap(l.a[i], l.a[posMax]);
    }
}

// ------------------------------------------------------------
// 12. Insertion Sort giam dan
// ------------------------------------------------------------
void insertionSortDesc(List &l)
{
    for (int i = 1; i < l.n; i++)
    {
        int x = l.a[i];
        int j = i - 1;

        while (j >= 0 && l.a[j] < x)
        {
            l.a[j + 1] = l.a[j];
            j--;
        }

        l.a[j + 1] = x;
    }
}

// ------------------------------------------------------------
// 13. Bubble Sort giam dan
// ------------------------------------------------------------
void bubbleSortDesc(List &l)
{
    for (int i = 0; i < l.n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < l.n - i - 1; j++)
        {
            if (l.a[j] < l.a[j + 1])
            {
                swap(l.a[j], l.a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// ------------------------------------------------------------
// 14. Interchange Sort giam dan
// ------------------------------------------------------------
void interchangeSortDesc(List &l)
{
    for (int i = 0; i < l.n - 1; i++)
    {
        for (int j = i + 1; j < l.n; j++)
        {
            if (l.a[i] < l.a[j])
                swap(l.a[i], l.a[j]);
        }
    }
}

// ------------------------------------------------------------
// 15. Quick Sort de quy giam dan
// ------------------------------------------------------------
void quickSortDesc(int a[], int left, int right)
{
    if (left >= right)
        return;

    int i = left;
    int j = right;
    int pivot = a[(left + right) / 2];

    while (i <= j)
    {
        while (a[i] > pivot)
            i++;

        while (a[j] < pivot)
            j--;

        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quickSortDesc(a, left, j);

    if (i < right)
        quickSortDesc(a, i, right);
}

void quickSortDesc(List &l)
{
    if (l.n > 1)
        quickSortDesc(l.a, 0, l.n - 1);
}

// ------------------------------------------------------------
// 16. Quick Sort khong de quy
// Dung stack mang luu cac khoang [left, right]
// ------------------------------------------------------------
struct Range
{
    int left;
    int right;
};

void quickSortDescIterative(List &l)
{
    if (l.n <= 1)
        return;

    Range st[MAX];
    int top = -1;

    st[++top] = {0, l.n - 1};

    while (top >= 0)
    {
        Range cur = st[top--];

        int left = cur.left;
        int right = cur.right;

        int i = left;
        int j = right;
        int pivot = l.a[(left + right) / 2];

        while (i <= j)
        {
            while (l.a[i] > pivot)
                i++;

            while (l.a[j] < pivot)
                j--;

            if (i <= j)
            {
                swap(l.a[i], l.a[j]);
                i++;
                j--;
            }
        }

        if (left < j)
            st[++top] = {left, j};

        if (i < right)
            st[++top] = {i, right};
    }
}

// ------------------------------------------------------------
// 17. Merge Sort giam dan
// ------------------------------------------------------------
void mergeDesc(int a[], int left, int mid, int right)
{
    int temp[MAX];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (a[i] >= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (int p = left; p <= right; p++)
        a[p] = temp[p];
}

void mergeSortDesc(int a[], int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSortDesc(a, left, mid);
    mergeSortDesc(a, mid + 1, right);
    mergeDesc(a, left, mid, right);
}

void mergeSortDesc(List &l)
{
    if (l.n > 1)
        mergeSortDesc(l.a, 0, l.n - 1);
}

// ------------------------------------------------------------
// 18. Heap Sort giam dan
// Muon ket qua giam dan: tao MIN-HEAP
// ------------------------------------------------------------
void heapifyMin(int a[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] < a[smallest])
        smallest = left;

    if (right < n && a[right] < a[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(a[i], a[smallest]);
        heapifyMin(a, n, smallest);
    }
}

void heapSortDesc(List &l)
{
    int n = l.n;

    // Xay dung Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(l.a, n, i);

    // Dua phan tu nho nhat ve cuoi
    for (int i = n - 1; i > 0; i--)
    {
        swap(l.a[0], l.a[i]);
        heapifyMin(l.a, i, 0);
    }

    // Ket qua tang dan -> dao lai de giam dan
    for (int i = 0; i < n / 2; i++)
        swap(l.a[i], l.a[n - 1 - i]);
}

// ============================================================
// TIM KIEM
// ============================================================

// ------------------------------------------------------------
// 19. Tim kiem tuan tu
// ------------------------------------------------------------
int sequentialSearch(const List &l, int x)
{
    for (int i = 0; i < l.n; i++)
        if (l.a[i] == x)
            return i;

    return -1;
}

// ------------------------------------------------------------
// 20. Tim kiem nhi phan
// Yeu cau danh sach phai duoc SAP XEP TANG DAN
// ------------------------------------------------------------
int binarySearch(const List &l, int x)
{
    int left = 0;
    int right = l.n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (l.a[mid] == x)
            return mid;

        if (x < l.a[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

// ============================================================
// MENU
// ============================================================

void menu()
{
    cout << "\n================ BAI 1 ================\n";
    cout << "1. Nhap danh sach\n";
    cout << "2. Xuat danh sach\n";
    cout << "3. Tim phan tu\n";
    cout << "4. Them vao cuoi\n";
    cout << "5. Xoa cuoi\n";
    cout << "6. Xoa tai vi tri i\n";
    cout << "7. Them tai vi tri i\n";
    cout << "8. Tim lon nhat\n";
    cout << "9. Tim lon thu 2 (gia tri khac nhau)\n";
    cout << "10. Selection Sort giam dan\n";
    cout << "11. Insertion Sort giam dan\n";
    cout << "12. Bubble Sort giam dan\n";
    cout << "13. Interchange Sort giam dan\n";
    cout << "14. Quick Sort de quy giam dan\n";
    cout << "15. Quick Sort khong de quy giam dan\n";
    cout << "16. Merge Sort giam dan\n";
    cout << "17. Heap Sort giam dan\n";
    cout << "18. Tim kiem tuan tu\n";
    cout << "19. Tim kiem nhi phan (yeu cau danh sach tang dan)\n";
    cout << "0. Thoat\n";
    cout << "=======================================\n";
}

// ============================================================
// MAIN DEMO
// ============================================================

int main()
{
    List l;
    init(l);

    int choice, x, i;

    do
    {
        menu();
        cout << "Chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            input(l);
            break;

        case 2:
            output(l);
            break;

        case 3:
            cout << "Nhap x: ";
            cin >> x;
            i = searchPosition(l, x);

            if (i != -1)
                cout << "Tim thay tai vi tri " << i << ".\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 4:
            cout << "Nhap x: ";
            cin >> x;
            cout << (addLast(l, x) ? "Them thanh cong.\n" : "Danh sach day.\n");
            break;

        case 5:
            if (deleteLast(l, x))
                cout << "Da xoa: " << x << "\n";
            else
                cout << "Danh sach rong.\n";
            break;

        case 6:
            cout << "Nhap vi tri i (0.." << l.n - 1 << "): ";
            cin >> i;

            if (deleteAt(l, i, x))
                cout << "Da xoa: " << x << "\n";
            else
                cout << "Vi tri khong hop le.\n";
            break;

        case 7:
            cout << "Nhap vi tri i (0.." << l.n << "): ";
            cin >> i;
            cout << "Nhap x: ";
            cin >> x;

            if (insertAt(l, i, x))
                cout << "Them thanh cong.\n";
            else
                cout << "Vi tri khong hop le hoac danh sach day.\n";
            break;

        case 8:
            if (maxValue(l, x))
                cout << "Lon nhat = " << x << "\n";
            else
                cout << "Danh sach rong.\n";
            break;

        case 9:
            if (secondMax(l, x))
                cout << "Lon thu 2 = " << x << "\n";
            else
                cout << "Khong ton tai gia tri lon thu 2 khac nhau.\n";
            break;

        case 10:
            selectionSortDesc(l);
            cout << "Da Selection Sort giam dan.\n";
            break;

        case 11:
            insertionSortDesc(l);
            cout << "Da Insertion Sort giam dan.\n";
            break;

        case 12:
            bubbleSortDesc(l);
            cout << "Da Bubble Sort giam dan.\n";
            break;

        case 13:
            interchangeSortDesc(l);
            cout << "Da Interchange Sort giam dan.\n";
            break;

        case 14:
            quickSortDesc(l);
            cout << "Da Quick Sort de quy giam dan.\n";
            break;

        case 15:
            quickSortDescIterative(l);
            cout << "Da Quick Sort khong de quy giam dan.\n";
            break;

        case 16:
            mergeSortDesc(l);
            cout << "Da Merge Sort giam dan.\n";
            break;

        case 17:
            heapSortDesc(l);
            cout << "Da Heap Sort giam dan.\n";
            break;

        case 18:
            cout << "Nhap x: ";
            cin >> x;
            i = sequentialSearch(l, x);

            if (i != -1)
                cout << "Tim thay tai vi tri " << i << ".\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 19:
            cout << "Luu y: danh sach phai duoc sap xep TANG DAN.\n";
            cout << "Nhap x: ";
            cin >> x;
            i = binarySearch(l, x);

            if (i != -1)
                cout << "Tim thay tai vi tri " << i << ".\n";
            else
                cout << "Khong tim thay.\n";
            break;

        case 0:
            cout << "Ket thuc.\n";
            break;

        default:
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);

    return 0;
}
