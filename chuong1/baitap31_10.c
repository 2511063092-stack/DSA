#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SẮP XẾP VÀ TÌM KIẾM[cite: 3]
// 1. Xét mảng các số nguyên có nội dung như sau:  -9   -9  -5  -2  0  3  7  7  10  15[cite: 3]
// Tính số lần so sánh để tìm ra phần tử X = -9 bằng phương pháp:[cite: 3]
// - Tìm tuyến tính[cite: 3]
// - Tìm nhị phân[cite: 3]
// Nhận xét và so sánh 2 phương pháp tìm nêu trên trong trường hợp này và trong trường hợp tổng quát.[cite: 3]

// bai lam[cite: 1]
// - tim tuyen tinh:[cite: 1, 3]
//   + so sanh a[0] = -9 voi X = -9: bang nhau -> tim thay ngay tai vi tri 0 (1 lan so sanh)
//   + neu yeu cau tim tat ca cac phan tu X = -9: so sanh tiep a[1] = -9 -> tim thay tai vi tri 1 (2 lan so sanh)
// - tim nhi phan (mang da sap xep tang dan, n = 10):[cite: 1, 3]
//   + buoc 1: l = 0, r = 9 -> m = (0 + 9) / 2 = 4. a[4] = 0. So sanh 0 voi -9: 0 > -9 -> tim nua ben trai (r = m - 1 = 3)
//   + buoc 2: l = 0, r = 3 -> m = (0 + 3) / 2 = 1. a[1] = -9. So sanh -9 voi -9: bang nhau -> tim thay tai vi tri 1
//   => Tong so lan so sanh: 2 lan
// - nhan xet:[cite: 1, 3]
//   + trong truong hop nay tim kiem tuyen tinh nhanh hon vi phan tu can tim nam ngay o dau day (1 lan so sanh)[cite: 1]
//   + trong truong hop tong quat: tim kiem tuyen tinh co do phuc tap O(n), truong hop xau nhat phai duyet qua n lan so sanh; tim kiem nhi phan co do phuc tap O(log n), so lan so sanh toi da chi khoang log2(n) nen khi tap du lieu lon thi tim kiem nhi phan toi uu hon rat nhieu[cite: 1]

// =========================================================================
// 2. Cho day so: 10  32  8  50  08  25  65  31  18  23[cite: 3]

// a,[cite: 1, 3]
// - sap xep chon (Selection Sort): duyet tu dau day, tim phan tu nho nhat trong doan chua sap xep dua ve dau doan[cite: 1, 3]
//   + buoc 1: tim min tu a[0..9] la 8 (tai a[2]) -> doi cho a[0] va a[2] -> [8]  32  10  50  08  25  65  31  18  23
//   + buoc 2: tim min tu a[1..9] la 08 (tai a[4]) -> doi cho a[1] va a[4] -> [8  08]  10  50  32  25  65  31  18  23
//   + buoc 3: tim min tu a[2..9] la 10 (tai a[2]) -> giu nguyen -> [8  08  10]  50  32  25  65  31  18  23
//   + buoc 4: tim min tu a[3..9] la 18 (tai a[8]) -> doi cho a[3] va a[8] -> [8  08  10  18]  32  25  65  31  50  23
//   + buoc 5: tim min tu a[4..9] la 23 (tai a[9]) -> doi cho a[4] va a[9] -> [8  08  10  18  23]  25  65  31  50  32
//   + buoc 6: tim min tu a[5..9] la 25 (tai a[5]) -> giu nguyen -> [8  08  10  18  23  25]  65  31  50  32
//   + buoc 7: tim min tu a[6..9] la 31 (tai a[7]) -> doi cho a[6] va a[7] -> [8  08  10  18  23  25  31]  65  50  32
//   + buoc 8: tim min tu a[7..9] la 32 (tai a[9]) -> doi cho a[7] va a[9] -> [8  08  10  18  23  25  31  32]  50  65
//   + buoc 9: tim min tu a[8..9] la 50 (tai a[8]) -> giu nguyen -> [8  08  10  18  23  25  31  32  50  65]
//
// - sap xep chen (Insertion Sort): lay tung phan tu chua sap xep chen vao vi tri dung trong doan da sap xep[cite: 3]
//   + khoi dau: [10]  32  8  50  08  25  65  31  18  23
//   + buoc 1 (xet 32): 32 > 10 -> [10  32]  8  50  08  25  65  31  18  23
//   + buoc 2 (xet 8) : 8 < 10, 32 -> chen 8 len dau -> [8  10  32]  50  08  25  65  31  18  23
//   + buoc 3 (xet 50): 50 > 32 -> giu nguyen -> [8  10  32  50]  08  25  65  31  18  23
//   + buoc 4 (xet 08): 08 chen vao sau 8 -> [8  08  10  32  50]  25  65  31  18  23
//   + buoc 5 (xet 25): 25 chen vao giua 10 va 32 -> [8  08  10  25  32  50]  65  31  18  23
//   + buoc 6 (xet 65): 65 > 50 -> giu nguyen -> [8  08  10  25  32  50  65]  31  18  23
//   + buoc 7 (xet 31): 31 chen vao giua 25 va 32 -> [8  08  10  25  31  32  50  65]  18  23
//   + buoc 8 (xet 18): 18 chen vao giua 10 va 25 -> [8  08  10  18  25  31  32  50  65]  23
//   + buoc 9 (xet 23): 23 chen vao giua 18 va 25 -> [8  08  10  18  23  25  31  32  50  65]
//
// - sap xep noi bot (Bubble Sort): duyet so sanh cac cap phan tu ke nhau, day phan tu lon nhat ve cuoi day[cite: 1, 3]
//   + luot 1: 10  8  32  08  25  50  31  18  23  [65] (65 noi ve cuoi)
//   + luot 2: 8  10  08  25  32  31  18  23  [50  65] (50 noi ve vi tri ke cuoi)
//   + luot 3: 8  08  10  25  31  18  23  [32  50  65] (32 noi ve vi tri)
//   + luot 4: 8  08  10  25  18  23  [31  32  50  65] (31 noi ve vi tri)
//   + luot 5: 8  08  10  18  23  [25  31  32  50  65] (25 noi ve vi tri)
//   + luot 6: khong con cap nao bi dao nguoc -> ket thuc: 8  08  10  18  23  25  31  32  50  65

// b,[cite: 3]
// - sap xep phan doan (Quick Sort): chon chot pivot = 23 (phan tu cuoi), chia thanh tap <= 23 va > 23[cite: 3]
//   + phan hoach 1: [10  8  08  18]  23  [32  50  25  65  31]
//   + nua trai [10  8  08  18] chon pivot = 18 -> phan hoach tiep: [10  8  08]  18 -> sap tiep duoc: 8  08  10  18
//   + nua phai [32  50  25  65  31] chon pivot = 31 -> phan hoach: [25]  31  [32  50  65] -> sap tiep nua phai duoc: 25  31  32  50  65
//   + ghep lai: 8  08  10  18  23  25  31  32  50  65
//
// - sap xep vun dong (Heap Sort):[cite: 3]
//   + buoc 1 (tao Max-Heap tu day goc): 65  50  25  32  23  8  10  31  18  08
//   + buoc 2 (lan luot doi root voi phan tu cuoi heap roi vun lai):
//     * doi 65 voi 08, vun lai: 50  32  25  31  23  8  10  08  18  [65]
//     * doi 50 voi 18, vun lai: 32  31  25  18  23  8  10  08  [50  65]
//     * doi 32 voi 08, vun lai: 31  23  25  18  08  8  10  [32  50  65]
//     * tiep tuc lap den khi cay chi con 1 nut -> mang thu duoc: 8  08  10  18  23  25  31  32  50  65
//
// - sap xep tron (Merge Sort): chia doi den day con 1 phan tu roi tron tung cap theo thu tu tang dan[cite: 3]
//   + chia doi day: [10  32  8  50  08] va [25  65  31  18  23]
//   + chia nho: [10] [32] [8] [50] [08] va [25] [65] [31] [18] [23]
//   + tron cap 2: [10  32], [8  50], [08] va [25  65], [18  31], [23]
//   + tron cap 4-5: [8  10  32  50] tron [08] -> [8  08  10  32  50]
//                   [18  25  31  65] tron [23] -> [18  23  25  31  65]
//   + tron 2 nua cuoi cung: 8  08  10  18  23  25  31  32  50  65

// e,[cite: 3]
// - tao cay nhi phan tim kiem (BST): phan tu nho hon re trai, lon hon hoac bang re phai[cite: 3]
//   + chen 10: 10 la nut goc (root)
//   + chen 32: 32 > 10 -> con phai cua 10
//   + chen 8 : 8 < 10  -> con trai cua 10
//   + chen 50: 50 > 10, > 32 -> con phai cua 32
//   + chen 08: 08 == 8 -> bo qua (hoac quy uoc chen vao con trai cua 8)
//   + chen 25: 25 > 10, < 32 -> con trai cua 32
//   + chen 65: 65 > 10, > 32, > 50 -> con phai cua 50
//   + chen 31: 31 > 10, < 32, > 25 -> con phai cua 25
//   + chen 18: 18 > 10, < 32, < 25 -> con trai cua 25
//   + chen 23: 23 > 10, < 32, < 25, > 18 -> con phai cua 18
//
// - cac buoc tim phan tu 18 trong cay:[cite: 3]
//   + bat dau tu nut goc 10: 18 > 10 -> di sang nut con phai (32)
//   + tai nut 32: 18 < 32 -> di sang nut con trai (25)
//   + tai nut 25: 18 < 25 -> di sang nut con trai (18)
//   + tai nut 18: 18 == 18 -> tim thay phan tu can tim (qua 4 nut: 10 -> 32 -> 25 -> 18)

// 3. Xay dung thuat toan tim min, max bang tim kiem nhi phan va tren cay BST[cite: 3]

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// tao nut moi cho cay
Node* taoNode(int val) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = val;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// tren mang da sap xep tang dan: min = a[0], max = a[n-1]
// neu la mang xoay vong (rotated sorted array), tim min bang tim kiem nhi phan:
int timMinNhiPhan(int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] > a[r]) l = m + 1;
        else r = m;
    }
    return a[l];
}

// tim max tren mang xoay vong bang tim kiem nhi phan:
int timMaxNhiPhan(int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (a[m] < a[l]) r = m - 1;
        else l = m;
    }
    return a[l];
}

// tim min tren cay BST: di lien tuc ve nhanh ngoai cung ben trai[cite: 3]
int timMinBST(Node* root) {
    if (root == NULL) return -1;
    Node* p = root;
    while (p->left != NULL) {
        p = p->left;
    }
    return p->data;
}

// tim max tren cay BST: di lien tuc ve nhanh ngoai cung ben phai[cite: 3]
int timMaxBST(Node* root) {
    if (root == NULL) return -1;
    Node* p = root;
    while (p->right != NULL) {
        p = p->right;
    }
    return p->data;
}

// 4. Ham tim kiem nhi phan tim tat ca so nguyen to trong mang 1 chieu co n phan tu[cite: 3]

int laSNT(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// ham tim kiem nhi phan co ban tren mang tang dan
int binarySearch(int a[], int n, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// tim tat ca cac so nguyen to trong mang a bang cach tra cuu qua bang SNT da sap xep
void timSNTBangNhiPhan(int a[], int n) {
    int maxVal = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > maxVal) maxVal = a[i];
    }
    if (maxVal < 2) {
        printf("Khong co so nguyen to trong mang\n");
        return;
    }

    // lap bang cac so nguyen to <= maxVal (day da sap xep tang dan)
    int *bangSNT = (int*)malloc((maxVal + 1) * sizeof(int));
    int dem = 0;
    for (int i = 2; i <= maxVal; i++) {
        if (laSNT(i)) {
            bangSNT[dem++] = i;
        }
    }

    printf("Cac so nguyen to co trong mang: ");
    int coSNT = 0;
    for (int i = 0; i < n; i++) {
        if (binarySearch(bangSNT, dem, a[i]) != -1) {
            printf("%d ", a[i]);
            coSNT = 1;
        }
    }
    if (!coSNT) printf("Khong co");
    printf("\n");

    free(bangSNT);
}
// 5. Danh sach thi sinh gom n nguoi, chon ra m nguoi co diem cao nhat[cite: 3]

typedef struct {
    char ten[50];
    float diem;
} ThiSinh;

void chonThiSinhDiemCaoNhat(ThiSinh ds[], int n, int m) {
    // sap xep giam dan theo diem
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].diem < ds[j].diem) {
                // hoan doi diem
                float tgDiem = ds[i].diem;
                ds[i].diem = ds[j].diem;
                ds[j].diem = tgDiem;

                // hoan doi chuoi ten dung strcpy trong string.h
                char tgTen[50];
                strcpy(tgTen, ds[i].ten);
                strcpy(ds[i].ten, ds[j].ten);
                strcpy(ds[j].ten, tgTen);
            }
        }
    }

    printf("Danh sach %d thi sinh co diem cao nhat:\n", m);
    for (int i = 0; i < m && i < n; i++) {
        printf("%d. %-20s - %.2f diem\n", i + 1, ds[i].ten, ds[i].diem);
    }
}

int main(){
    // test bai 4[cite: 3]
    int a[] = {10, 32, 8, 50, 8, 25, 65, 31, 18, 23};
    int n = 10;
    timSNTBangNhiPhan(a, n);

    // test bai 5[cite: 3]
    ThiSinh ds[5];
    strcpy(ds[0].ten, "Nguyen Van A"); ds[0].diem = 7.5;
    strcpy(ds[1].ten, "Tran Thi B");   ds[1].diem = 9.25;
    strcpy(ds[2].ten, "Le Van C");     ds[2].diem = 8.0;
    strcpy(ds[3].ten, "Pham Thi D");   ds[3].diem = 9.75;
    strcpy(ds[4].ten, "Hoang Van E");  ds[4].diem = 6.5;

    chonThiSinhDiemCaoNhat(ds, 5, 3);

    return 0;
}