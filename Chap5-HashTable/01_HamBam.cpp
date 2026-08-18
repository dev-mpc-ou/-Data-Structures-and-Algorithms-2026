#include <iostream>
using namespace std;

const int M = 7;

int hashFunc(int key)
{
    int h = key % M;
    if (h < 0) h += M;
    return h;
}

int main()
{
    int n;
    cout << "=== HAM BAM h(k) = k % M ===\n";
    cout << "M = " << M << endl;

    cout << "Nhap so luong key: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int key;
        cout << "Nhap key " << i + 1 << ": ";
        cin >> key;

        cout << "h(" << key << ") = "
             << hashFunc(key) << endl;
    }

    return 0;
}
