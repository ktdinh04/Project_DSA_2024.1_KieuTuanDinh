// Given a circular integer array, find a subarray with the largest sum in it.
#include <stdio.h>
#include <stdlib.h>
/* Example
Input {2, 1, -5, 4, -3, 1, -3, 4, -1}
Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.
*/
// Hàm tìm mảng con có tổng lớn nhất sử dụng thuật toán Kadane
int kadane(int arr[], int n, int *start, int *end) {
    int max_ending_here = 0;  // Tổng tạm thời của mảng con kết thúc tại chỉ số hiện tại
    int max_so_far = -1000000; // Giá trị lớn nhất tìm được, khởi tạo với giá trị rất nhỏ
    int temp_start = 0;  // Biến tạm để đánh dấu chỉ số bắt đầu của mảng con hiện tại

    *start = 0; // Khởi tạo chỉ số bắt đầu của mảng con kết quả
    *end = 0;   // Khởi tạo chỉ số kết thúc của mảng con kết quả

    for (int i = 0; i < n; i++) { // Lặp qua từng phần tử của mảng
        max_ending_here += arr[i]; // Cộng giá trị phần tử hiện tại vào tổng tạm thời

        if (max_so_far < max_ending_here) { // Nếu tổng tạm thời lớn hơn tổng lớn nhất hiện tại
            max_so_far = max_ending_here; // Cập nhật tổng lớn nhất
            *start = temp_start;          // Cập nhật chỉ số bắt đầu của mảng con
            *end = i;                     // Cập nhật chỉ số kết thúc của mảng con
        }

        if (max_ending_here < 0) { // Nếu tổng tạm thời trở nên âm
            max_ending_here = 0;   // Đặt lại tổng tạm thời về 0
            temp_start = i + 1;    // Đặt lại chỉ số bắt đầu cho mảng con mới
        }
    }

    return max_so_far; // Trả về tổng lớn nhất tìm được
}

// Hàm tìm mảng con có tổng lớn nhất trong mảng tròn
int maxCircularSubarraySum(int arr[], int n, int *final_start, int *final_end) {
    int max_start, max_end;

    // Bước 1: Tìm tổng lớn nhất sử dụng Kadane (trường hợp không tròn)
    int max_kadane = kadane(arr, n, &max_start, &max_end);

    // Lưu kết quả nếu tổng Kadane là lớn nhất
    *final_start = max_start; // Gán chỉ số bắt đầu cho mảng con lớn nhất
    *final_end = max_end;     // Gán chỉ số kết thúc cho mảng con lớn nhất

    // Bước 2: Tính tổng toàn bộ mảng và tìm tổng nhỏ nhất
    int total_sum = 0; // Biến lưu tổng toàn bộ mảng
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];  // Cộng dồn các phần tử vào tổng
        arr[i] = -arr[i];     // Đảo ngược dấu các phần tử để tìm tổng nhỏ nhất
    }

    int min_start, min_end;
    int max_inverted_kadane = kadane(arr, n, &min_start, &min_end); // Tìm tổng lớn nhất của mảng đã đảo dấu
    int max_circular = total_sum + max_inverted_kadane; // Tổng lớn nhất trong trường hợp tròn

    // Trả lại mảng gốc (không bị đảo ngược)
    for (int i = 0; i < n; i++) {
        arr[i] = -arr[i]; // Đảo lại dấu của mảng để trở về trạng thái ban đầu
    }

    // Bước 3: So sánh 2 trường hợp
    if (max_circular > max_kadane && max_circular != 0) { // Nếu tổng lớn nhất trong trường hợp tròn lớn hơn Kadane
        *final_start = (min_end + 1) % n; // Chỉ số bắt đầu trong trường hợp tròn
        *final_end = (min_start - 1 + n) % n; // Chỉ số kết thúc trong trường hợp tròn
        return max_circular; // Trả về tổng lớn nhất trong trường hợp tròn
    }

    // Trường hợp thông thường (Kadane lớn hơn)
    return max_kadane;
}

// Hàm in ra mảng con từ chỉ số start đến end
void printSubarray(int arr[], int n, int start, int end) {
    if (start <= end) { // Nếu mảng con không bị chia tách (trường hợp thông thường)
        for (int i = start; i <= end; i++) {
            printf("%d ", arr[i]); // In các phần tử từ start đến end
        }
    } else { // Nếu mảng con bị chia tách (trường hợp tròn)
        for (int i = start; i < n; i++) { // In phần đầu từ start đến cuối mảng
            printf("%d ", arr[i]);
        }
        for (int i = 0; i <= end; i++) { // In phần cuối từ đầu mảng đến end
            printf("%d ", arr[i]);
        }
    }
    printf("\n"); // Xuống dòng sau khi in mảng con
}

int main() {
    int arr[] = {8, -4, 3, -5, 4}; // Mảng đầu vào
    int n = sizeof(arr) / sizeof(arr[0]); // Kích thước của mảng
    int start, end; // Các biến lưu chỉ số bắt đầu và kết thúc của mảng con lớn nhất

    int result = maxCircularSubarraySum(arr, n, &start, &end); // Tìm tổng lớn nhất và các chỉ số
    printf("Tong so lon nhat cua mang con: %d\n", result); // In tổng lớn nhất
    printf("Mang con lon nhat la: ");
    printSubarray(arr, n, start, end); // In mảng con lớn nhất

    return 0;
}
