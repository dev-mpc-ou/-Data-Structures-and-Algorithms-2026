# ĐỀ ÔN GIỮA KỲ 01 - DANH SÁCH ĐẶC VÀ GIẢI THUẬT MẢNG

## Phạm vi

Bám theo Bài 1 của đề cương:

- Danh sách đặc tối đa 100 phần tử `int`
- Nhập / xuất
- Tìm kiếm
- Thêm / xóa
- Max, lớn thứ 2
- Selection Sort
- Insertion Sort
- Bubble Sort
- Interchange Sort
- Quick Sort đệ quy
- Quick Sort không đệ quy
- Merge Sort
- Heap Sort
- Tìm kiếm tuần tự
- Tìm kiếm nhị phân

## Đề luyện tập

Cho danh sách đặc `List` có tối đa 100 số nguyên.

### Phần A - Cơ bản

1. Khai báo cấu trúc danh sách.
2. Nhập danh sách từ bàn phím.
3. Xuất danh sách.
4. Tìm vị trí đầu tiên của `x`.
5. Thêm `x` vào cuối.
6. Xóa phần tử cuối.
7. Xóa phần tử tại vị trí `i`.
8. Chèn `x` vào vị trí `i`.

### Phần B - Tư duy mảng

9. Tìm phần tử lớn nhất.
10. Tìm phần tử lớn thứ 2 **phân biệt**.
11. Đếm số phần tử nguyên tố.
12. Đảo ngược danh sách.
13. Xóa tất cả phần tử trùng nhau, chỉ giữ lần xuất hiện đầu tiên.
14. Kiểm tra danh sách có đối xứng hay không.

### Phần C - Sắp xếp

Viết riêng từng hàm sắp xếp **giảm dần**:

15. Selection Sort.
16. Insertion Sort.
17. Bubble Sort.
18. Interchange Sort.
19. Quick Sort đệ quy.
20. Quick Sort không đệ quy.
21. Merge Sort.
22. Heap Sort.

### Phần D - Tìm kiếm

23. Tìm kiếm tuần tự.
24. Sắp xếp danh sách rồi tìm kiếm nhị phân.
25. So sánh số lần kiểm tra phần tử của tuần tự và nhị phân.

## Bài biến thể nên tự làm

- Tìm 3 phần tử lớn nhất.
- Đưa toàn bộ số chẵn lên đầu nhưng giữ thứ tự tương đối.
- Trộn hai danh sách đã sắp xếp giảm dần.
- Tìm phần tử xuất hiện nhiều nhất.
- Tìm cặp phần tử có tổng bằng `S`.
- Kiểm tra hai danh sách có cùng tập giá trị hay không.

## File dữ liệu

`data_mang.txt` chứa các số nguyên, có thể dùng để test nhanh chương trình.

Định dạng:

```text
n
a1 a2 a3 ... an
```

## Checklist trước khi thi

- [ ] Biết dịch vị trí khi chèn/xóa.
- [ ] Không truy cập `a[i]` ngoài phạm vi.
- [ ] Phân biệt vị trí `i` và chỉ số `i`.
- [ ] Biết điều kiện của lớn thứ 2 phân biệt.
- [ ] Nhớ điều kiện để Binary Search hoạt động.
- [ ] Hiểu `low`, `high`, `mid`.
- [ ] Hiểu `partition` của Quick Sort.
- [ ] Hiểu Merge Sort tách / trộn.
- [ ] Hiểu Heap Sort dùng Max Heap khi cần giảm dần.
- [ ] Có thể viết menu `switch-case`.

## Cách luyện

Lần 1: chạy code mẫu.

Lần 2: xóa phần thân các hàm sort và tự viết.

Lần 3: chỉ giữ đề, tự code từ đầu trong 45-60 phút.
