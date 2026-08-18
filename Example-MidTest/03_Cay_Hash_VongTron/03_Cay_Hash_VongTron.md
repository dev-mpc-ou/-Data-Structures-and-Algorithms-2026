# ĐỀ ÔN GIỮA KỲ 03 - CÂY, BẢNG BĂM VÀ DANH SÁCH VÒNG

## Phạm vi

Tổng hợp các Bài 3, 4, 5 trong đề cương.

- Trò chơi vòng tròn / Josephus
- BST
- Duyệt cây đệ quy
- Duyệt cây không đệ quy
- BFS bằng Queue
- Đếm node chứa số nguyên tố
- Hash Separate Chaining
- Hash Coalesced Chaining
- Ứng dụng kiểm tra hai chuỗi là hoán vị

## Phần A - Vòng tròn

Có `n` người ngồi thành vòng tròn.

Người đầu tiên đếm `1`, tiếp tục theo chiều kim đồng hồ. Khi số đếm là số nguyên tố, người đó bị loại. Người kế tiếp tiếp tục đếm.

1. Dùng cấu trúc dữ liệu phù hợp.
2. In thứ tự những người bị loại.
3. Tìm người chiến thắng.
4. Cho biết nếu người chiến thắng là `k` thì người bắt đầu đếm là ai.
5. Mở rộng: sau mỗi lần loại, đảo chiều.

> Khi luyện, tự kiểm tra các trường hợp `n=1,2,3,5,10`.

## Phần B - BST

Cài đặt cây nhị phân tìm kiếm số nguyên:

1. Thêm node.
2. Tìm node.
3. Xóa node.
4. LNR đệ quy.
5. LRN đệ quy.
6. NLR đệ quy.
7. LNR không đệ quy.
8. LRN không đệ quy.
9. NLR không đệ quy.
10. BFS bằng Queue danh sách liên kết.
11. BFS bằng Queue mảng vòng.
12. BFS bằng Queue mảng tịnh tiến.
13. Đếm node chứa giá trị nguyên tố.

## Phần C - AVL

Mở rộng BST thành AVL:

- Balance Factor.
- LL.
- RR.
- LR.
- RL.
- Insert AVL.
- Delete AVL.
- Search AVL.
- LNR / NLR / LRN.

## Phần D - Bảng băm

Cài đặt:

### Separate Chaining

Mỗi bucket là một danh sách liên kết.

### Coalesced Chaining

Mỗi ô gồm:

```text
key
link
```

Yêu cầu:

- Thêm.
- Xóa.
- Tìm.
- Xuất.

## Ứng dụng quan trọng

Kiểm tra hai chuỗi có phải hoán vị hay không.

Ví dụ:

```text
listen
silent
```

Kết quả:

```text
YES
```

Ý tưởng:

- Hai chuỗi phải có cùng độ dài.
- Đếm tần suất từng ký tự.
- Nếu tần suất giống nhau thì là hoán vị.

## Checklist

- [ ] BST: 3 trường hợp xóa node.
- [ ] Stack khi duyệt DFS không đệ quy.
- [ ] Queue khi BFS.
- [ ] Queue vòng khác Queue tịnh tiến ở cách xử lý vị trí.
- [ ] Biết kiểm tra số nguyên tố.
- [ ] Hiểu 4 trường hợp xoay AVL.
- [ ] Separate Chaining dùng linked list.
- [ ] Coalesced dùng `link`.
- [ ] Hash collision.
- [ ] Biết kiểm tra anagram bằng bảng tần suất.

## Dữ liệu

`data_tree.txt` chứa các số nguyên để tạo BST.

`data_hash.txt` chứa các số nguyên để test bảng băm.
