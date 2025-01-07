
1. Maximum sum circular subarray
    Đây là chương trình C thực hiện việc tìm mảng con (subarray) có tổng lớn nhất trong một mảng tròn (circular integer array). Một mảng tròn là mảng mà phần tử cuối được nối với phần tử đầu, tạo thành một vòng tròn.
    1.1 Phân tích giải thuật
        Phân biệt hai trường hợp chính:

        - Trường hợp 1: Mảng con có tổng lớn nhất nằm hoàn toàn trong mảng liên tiếp (không bị chia tách).
        - Trường hợp 2: Mảng con có tổng lớn nhất bị chia tách, bao gồm cả các phần tử đầu và cuối của mảng.
2. Bước thực hiện cụ thể:

        Bước 1: Tìm tổng lớn nhất với thuật toán Kadane
        Thuật toán Kadane tìm tổng lớn nhất của một mảng con liên tiếp trong mảng thông thường.
        Lặp qua từng phần tử trong mảng và giữ lại giá trị lớn nhất tính được.
        Bước 2: Tính tổng lớn nhất trong trường hợp mảng tròn
        Tổng lớn nhất trong mảng tròn = (Tổng toàn bộ mảng) - (Tổng nhỏ nhất của mảng con).
        Để tìm tổng nhỏ nhất của mảng con:
        Đổi dấu tất cả các phần tử của mảng (âm thành dương và ngược lại).
        Chạy thuật toán Kadane trên mảng đã đổi dấu để tìm tổng lớn nhất.
        Đổi dấu kết quả trở lại và tính tổng nhỏ nhất.
        Bước 3: So sánh
        So sánh tổng lớn nhất tìm được ở hai bước trên:
        Nếu tổng lớn nhất từ Kadane lớn hơn, đó là đáp án.
        Nếu tổng lớn nhất trong mảng tròn lớn hơn, đó là đáp án.
3. Mã giả cho giải thuật chi tiết
        INPUT: Mảng arr gồm n phần tử
        OUTPUT: Tổng lớn nhất của mảng con và mảng con tương ứng

        1. Hàm Kadane(arr, n):
            max_ending_here = 0
            max_so_far = -∞
            start = 0, end = 0, temp_start = 0
            
            FOR i = 0 TO n-1:
                max_ending_here += arr[i]
                
                IF max_ending_here > max_so_far:
                    max_so_far = max_ending_here
                    start = temp_start
                    end = i
                
                IF max_ending_here < 0:
                    max_ending_here = 0
                    temp_start = i + 1
            
            RETURN (max_so_far, start, end)

        2. Hàm MaxCircularSubarraySum(arr, n):
            # Bước 1: Tìm tổng lớn nhất thông thường
            (max_kadane, start_kadane, end_kadane) = Kadane(arr, n)
            
            # Bước 2: Tìm tổng lớn nhất trong trường hợp tròn
            total_sum = SUM(arr)
            FOR i = 0 TO n-1:
                arr[i] = -arr[i]
            
            (min_subarray_sum, _, _) = Kadane(arr, n)
            max_circular = total_sum + min_subarray_sum
            
            # Bước 3: So sánh hai trường hợp
            IF max_circular > max_kadane AND max_circular != 0:
                circular_start = (end_kadane + 1) % n
                circular_end = (start_kadane - 1 + n) % n
                RETURN (max_circular, circular_start, circular_end)
            ELSE:
                RETURN (max_kadane, start_kadane, end_kadane)

        3. Hàm PrintSubarray(arr, start, end, n):
            IF start <= end:
                PRINT arr[start...end]
            ELSE:
                PRINT arr[start...n-1], arr[0...end]

        4. MAIN:
            INPUT arr[]
            n = SIZE(arr)
            (result, start, end) = MaxCircularSubarraySum(arr, n)
            PRINT "Tong lon nhat:", result
            PRINT "Mang con lon nhat:", PrintSubarray(arr, start, end, n)

