
1. Maximum sum circular subarray
    Đây là chương trình C thực hiện việc tìm mảng con (subarray) có tổng lớn nhất trong một mảng tròn (circular integer array). Một mảng tròn là mảng mà phần tử cuối được nối với phần tử đầu, tạo thành một vòng tròn.
    1.1 Phân tích giải thuật
        Phân biệt hai trường hợp chính:

        - Trường hợp 1: Mảng con có tổng lớn nhất nằm hoàn toàn trong mảng liên tiếp (không bị chia tách).
        - Trường hợp 2: Mảng con có tổng lớn nhất bị chia tách, bao gồm cả các phần tử đầu và cuối của mảng.
2. Bước thực hiện cụ thể:

    Bước 1: Sử dụng thuật toán Kadane
        - Tìm tổng lớn nhất của mảng con trong trường hợp không tròn.
        - Lưu lại chỉ số bắt đầu (start) và kết thúc (end) của mảng con này.
    Bước 2: Tìm tổng lớn nhất trong trường hợp mảng tròn
        - Tính tổng của toàn bộ mảng (total_sum).
        - Đổi dấu các phần tử trong mảng (từ a[i] thành -a[i]).
        - Chạy thuật toán Kadane trên mảng đã đổi dấu để tìm tổng nhỏ nhất của mảng con (min_subarray_sum).
        - Tổng lớn nhất trong trường hợp tròn = total_sum - (-min_subarray_sum).
        - Xác định lại chỉ số bắt đầu và kết thúc cho trường hợp này.
    Bước 3: So sánh hai trường hợp
        - Nếu tổng lớn nhất từ Kadane (trường hợp 1) lớn hơn, đây là đáp án.
        - Ngược lại, tổng lớn nhất trong mảng tròn là đáp án.
        Mã giả cho giải thuật chi tiết
