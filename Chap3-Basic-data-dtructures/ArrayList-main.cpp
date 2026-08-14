#include "ArrayList.h"  // Dùng thư viện danh sách đặc

int main()
{
    // Khai báo một danh sách
    ArrayList ls;

    // Nhập dữ liệu vào danh sách
    ls.input();

    // Xuất danh sách ban đầu
    cout << "Mang ban dau: ";
    ls.output();

    // Thêm 10 vào cuối danh sách
    ls.add(10);

    // Chèn số 20 vào vị trí thứ 2 (chỉ số 1)
    ls.insertIndex(20, 1);

    // Sửa phần tử đầu danh sách thành 99
    ls.update(0, 99);

    // Xóa phần tử ở vị trí thứ 3 (chỉ số 2)
    ls.deleteIndex(2);

    // Xuất danh sách sau khi thao tác
    cout << "Mang sau khi thao tac: ";
    ls.output();

    return 0;
}
