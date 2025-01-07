/*Find distance between given pairs of nodes in a binary tree*/
/*Given a binary tree, determine the distance between given pairs of nodes in it. 
The distance between two nodes is defined as the total number of edges in the shortest 
path from one node to other.*/

#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc của một nút trong cây nhị phân
typedef struct Node {
    int data;               // Dữ liệu của nút
    struct Node* left;      // Con trái của nút
    struct Node* right;     // Con phải của nút
} Node;

// Hàm tạo một nút mới
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node)); // Cấp phát bộ nhớ cho nút mới
    node->data = data;       // Gán giá trị dữ liệu
    node->left = NULL;       // Con trái ban đầu là NULL
    node->right = NULL;      // Con phải ban đầu là NULL
    return node;
}

// Hàm tìm Tổ tiên Chung Thấp nhất (LCA) của hai nút trong cây nhị phân
Node* findLCA(Node* root, int n1, int n2) {
    if (root == NULL) return NULL; // Nếu cây rỗng, trả về NULL

    // Nếu một trong hai nút là gốc, gốc chính là LCA
    if (root->data == n1 || root->data == n2) return root;

    // Đệ quy tìm LCA trong cây con trái và cây con phải
    Node* leftLCA = findLCA(root->left, n1, n2);
    Node* rightLCA = findLCA(root->right, n1, n2);

    // Nếu cả hai bên đều không NULL, gốc là LCA
    if (leftLCA != NULL && rightLCA != NULL) return root;

    // Trả về giá trị không NULL (bên chứa LCA)
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Hàm tìm khoảng cách từ gốc đến một nút bất kỳ
int findDistanceFromRoot(Node* root, int key, int distance) {
    if (root == NULL) return -1; // Nếu nút hiện tại là NULL, trả về -1 (không tìm thấy)

    // Nếu tìm thấy nút có giá trị bằng key, trả về khoảng cách
    if (root->data == key) return distance;

    // Đệ quy tìm trong cây con trái
    int leftDistance = findDistanceFromRoot(root->left, key, distance + 1);
    if (leftDistance != -1) return leftDistance; // Nếu tìm thấy trong cây trái, trả về kết quả

    // Đệ quy tìm trong cây con phải
    return findDistanceFromRoot(root->right, key, distance + 1);
}

// Hàm tìm khoảng cách giữa hai nút trong cây nhị phân
int findDistance(Node* root, int n1, int n2) {
    // Bước 1: Tìm Tổ tiên Chung Thấp nhất (LCA) của hai nút
    Node* lca = findLCA(root, n1, n2);

    if (lca == NULL) return -1; // Nếu LCA không tồn tại, hai nút không nằm trong cùng một cây

    // Bước 2: Tìm khoảng cách từ LCA đến từng nút
    int d1 = findDistanceFromRoot(lca, n1, 0); // Khoảng cách từ LCA đến nút n1
    int d2 = findDistanceFromRoot(lca, n2, 0); // Khoảng cách từ LCA đến nút n2

    // Bước 3: Tổng khoảng cách là tổng khoảng cách từ LCA đến n1 và n2
    return d1 + d2;
}
// Hàm duyệt cây theo thứ tự trước (Pre-order)
    void preOrder(Node* root) {
        if (root!= NULL) {
            printf("%d ", root->data);
            preOrder(root->left);
            preOrder(root->right);
        }
    }

// Hàm chính để kiểm tra
int main() {
    // Tạo cây nhị phân
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->left->right = newNode(8);
    root->right->right->left = newNode(9);
    root->right->right->right = newNode(10);
    root->right->right->right->left = newNode(11);
    root->right->right->right->right = newNode(12);
    root->right->right->right->left->right = newNode(13);
    root->left->left->left = newNode(14);
    root->left->left->right = newNode(15);
    root->left->right->left = newNode(16);
    root->left->right->right = newNode(17);
    int n1 = 12, n2 = 17;
    // Tính khoảng cách giữa hai nút
    int distance = findDistance(root, n1, n2);
    if (distance != -1)
        printf("Khoang cach giua nut %d va nut %d la: %d\n", n1, n2, distance);
    else
        printf("Mot hoac ca hai nut khong ton tai trong cay.\n");

    return 0;
}
