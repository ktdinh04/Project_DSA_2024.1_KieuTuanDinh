# Maximum sum circular subarray
   Đây là chương trình C thực hiện việc tìm mảng con (subarray) có tổng lớn nhất trong một mảng tròn (circular integer array). Một mảng tròn là mảng mà phần tử cuối được nối với phần tử đầu, tạo thành một vòng tròn.
## 1. Xác định bài toán:   
- Đầu vào: Một mảng số nguyên `arr` có kích thước n, là một mảng tròn (circular array), trong đó phần tử cuối nối liền với phần tử đầu.
- Đầu ra: Tổng lớn nhất của một mảng con liên tục (subarray) và các chỉ số bắt đầu, kết thúc của mảng con đó.
## 2. Phân tích bài toán
Một mảng tròn có thể được xem như được nối lại từ hai đầu. Do đó, subarray tối ưu có thể nằm trong một trong hai trường hợp:

- Hoàn toàn bên trong mảng gốc (giống bài toán subarray bình thường).
- Kéo dài qua cuối mảng và đầu mảng (trường hợp "circular").
Tìm tổng lớn nhất cho từng trường hợp, sau đó chọn giá trị lớn hơn.
## 3. Xây dựng giải thuật
### Bước 1: Tìm tổng lớn nhất không tròn
#### Sử dụng thuật toán Kadane’s Algorithm:

Khởi tạo: 

- `max_ending_here = arr[0]`: Tổng tạm thời
-  `max_so_far = arr[0]`: Tổng lớn nhất đã tìm thấy
Lặp qua từng phần tử `arr[i]` từ chỉ số 1 đến cuối:

- Cập nhật `max_ending_here = max(arr[i], max_ending_here + arr[i])`  
- Cập nhật `max_so_far = max(max_so_far, max_ending_here)`  
- Nếu `max_so_far < 0`  thì đặt tổng tạm thời `max_ending_here = 0`  
Kết quả là `max_so_far` và các chỉ số bắt đầu/kết thúc của mảng con.
###  Bước 2: Tính tổng mảng và tìm tổng nhỏ nhất

-  Tính tổng toàn bộ mảng `total_sum`  
-  Đảo dấu tất cả các phần tử trong mảng.
- Sử dụng lại thuật toán Kadane trên mảng đã đảo dấu để tìm tổng lớn nhất (thực chất là tổng nhỏ nhất của mảng gốc).
- Tổng lớn nhất trong trường hợp tròn là: `max_circular = total_sum - tổng nhỏ nhất`
### Bước 3:  Xử lý trường hợp đặc biệt
- Nếu mảng toàn số âm, `max_circular = 0 `(không hợp lệ). Trong trường hợp này, kết quả là `max_kadane`.

### Bước 4: So sánh và chọn kết quả cuối cùng

- So sánh `max_kadane` và `max_circular`  
   - Nếu `max_kadane` > `max_circular`, kết quả là max_kadane.  
   - Ngược lại, kết quả là `max_circular` và chỉ số bắt đầu/kết thúc cần được tính lại.  


## 4. Độ phức tạp
    - Thời gian: O(n), vì thuật toán Kadane và các bước khác chỉ duyệt mảng một lần.
    - Không gian: O(1), vì chỉ sử dụng các biến tạm, không sử dụng mảng phụ.
## 5. Mã giả: 

Hàm chính:

    FUNCTION maxCircularSubarraySum(arr, n):
    # Bước 1: Tìm tổng lớn nhất không tròn
    max_kadane, start_kadane, end_kadane = Kadane(arr, n)
    
    # Lưu chỉ số bắt đầu và kết thúc của mảng con tốt nhất ban đầu
    final_start = start_kadane
    final_end = end_kadane

    # Bước 2: Tính tổng toàn bộ mảng
    total_sum = 0
    FOR i FROM 0 TO n-1:
        total_sum = total_sum + arr[i]
        arr[i] = -arr[i]  # Đảo dấu các phần tử

    # Tìm tổng nhỏ nhất bằng cách tìm tổng lớn nhất của mảng đã đảo dấu
    min_kadane, min_start, min_end = Kadane(arr, n)
    max_circular = total_sum + min_kadane

    # Khôi phục lại mảng gốc
    FOR i FROM 0 TO n-1:
        arr[i] = -arr[i]  # Đảo lại dấu

    # Bước 3: Xử lý trường hợp đặc biệt (mảng toàn số âm)
    IF max_circular == 0:
        RETURN max_kadane, start_kadane, end_kadane

    # Bước 4: So sánh và chọn kết quả tốt nhất
    IF max_circular > max_kadane:
        final_start = (min_end + 1) MOD n
        final_end = (min_start - 1 + n) MOD n
        RETURN max_circular, final_start, final_end
    ELSE:
        RETURN max_kadane, final_start, final_end


Hàm Kadane: Tìm tổng lớn nhất của mảng con
    
    FUNCTION Kadane(arr, n):
    # Khởi tạo các biến
    max_ending_here = 0
    max_so_far = arr[0]
    start = 0
    end = 0
    temp_start = 0

    # Duyệt qua từng phần tử của mảng
    FOR i FROM 0 TO n-1:
        max_ending_here = max_ending_here + arr[i]

        # Nếu tìm thấy tổng lớn hơn tổng lớn nhất hiện tại
        IF max_ending_here > max_so_far:
            max_so_far = max_ending_here
            start = temp_start
            end = i

        # Nếu tổng tạm thời trở nên âm, đặt lại
        IF max_ending_here < 0:
            max_ending_here = 0
            temp_start = i + 1

    RETURN max_so_far, start, end

## 6.Code 
 - [Maximum_sum_circular_subarray](https://github.com/ktdinh04/Project_DSA_2024.1_KieuTuanDinh/blob/main/Maximum_sum_circular_subarray.c)
 
