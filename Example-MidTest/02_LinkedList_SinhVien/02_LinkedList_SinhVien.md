# ĐỀ ÔN GIỮA KỲ 02 - DANH SÁCH LIÊN KẾT QUẢN LÝ

## Phạm vi

Bài luyện tập mô phỏng Bài 2 trong đề cương bằng danh sách liên kết đơn.

Thông tin sinh viên:

- Họ tên
- MSSV
- Lớp
- Số điện thoại
- Điểm trung bình

## Đề luyện tập

### Phần A - Danh sách liên kết

1. Khai báo `Node` và `List`.
2. Khởi tạo danh sách rỗng.
3. Tạo node.
4. Thêm đầu.
5. Thêm cuối.
6. Xóa đầu.
7. Xóa cuối.
8. Tìm sinh viên theo MSSV.
9. Xóa sinh viên theo MSSV.
10. Đếm số sinh viên.

### Phần B - Quản lý sinh viên

11. Nhập danh sách sinh viên từ bàn phím.
12. Đọc danh sách từ `sinhvien.txt`.
13. Xuất đầy đủ thông tin.
14. Xuất rút gọn theo lựa chọn của người dùng.
15. Nhập họ tên + lớp, tìm sinh viên tương ứng.
16. Nhập tên lớp, xóa toàn bộ sinh viên thuộc lớp đó.
17. Sắp xếp giảm dần theo GPA.
18. Chèn sinh viên mới nhưng vẫn giữ thứ tự GPA giảm dần.

### Phần C - File

19. Xuất danh sách ra `sinhvien_out.txt`.
20. Thử sửa dữ liệu trong file rồi đọc lại.
21. Tạo một file dữ liệu lỗi và xử lý trường hợp không mở được file.

## Biến thể để đổi đề

Thay `SinhVien` bằng:

### Sách

```text
MaSach | TenSach | TacGia | NamXB | Gia
```

Yêu cầu tương tự: thêm, xóa, tìm, sắp xếp theo giá.

### Đĩa nhạc

```text
MaDia | TenAlbum | CaSi | TheLoai | NamPhatHanh
```

Yêu cầu tương tự: thêm, xóa, tìm, sắp xếp theo năm phát hành.

### Gợi ý quan trọng

Nếu đề nói danh sách có số lượng **lớn và biến động**, ưu tiên danh sách liên kết thay vì mảng tĩnh.

## File dữ liệu

` sinhvien.txt ` dùng format:

```text
MSSV|HoTen|Lop|SDT|GPA
```

Không dùng dấu `|` trong nội dung tên/lớp.

## Checklist

- [ ] Hiểu `head`.
- [ ] Hiểu `Node*`.
- [ ] Không làm mất node khi xóa.
- [ ] Xóa đúng trường hợp node đầu.
- [ ] Xóa đúng trường hợp node cuối.
- [ ] Xóa node ở giữa.
- [ ] Duyệt danh sách.
- [ ] Sắp xếp node bằng cách đổi dữ liệu hoặc đổi liên kết.
- [ ] Đọc file.
- [ ] Ghi file.
- [ ] Xử lý danh sách rỗng.
