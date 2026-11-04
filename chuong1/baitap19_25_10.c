#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SẮP XẾP VÀ TÌM KIẾM
// 1. Xét mảng các số nguyên có nội dung như sau:  -9   -9  -5  -2  0  3  7  7  10  15
// Tính số lần so sánh để tìm ra phần tử X = -9 bằng phương pháp:
// - Tìm tuyến tính
// - Tìm nhị phân
// Nhận xét và so sánh 2 phương pháp tìm nêu trên trong trường hợp này và trong trường hợp tổng quát.

// bai lam
// - tim tuyen tinh:
//   + ta so sanh phan tu a[0] và a[1] tim ra -9 (neu tim vi tri dau tien thi 1 lan, duyet tim ca 2 phan tu -9 thi 2 lan)
// - tim nhi phan:
//   + ta so sanh phan tu a[m] = a[4] = 0 voi -9, -9 nho hon tiep tuc doi m ve phan tu a[1] = -9 so sanh tiep voi -9 bang nhau -> tim ra -9 (mat 2 lan so sanh)
// - nhan xet:
//   + trong truong hop nay tim kiem tuyen tinh se nhanh hon vi phan tu can tim o dau day
//   + trong truong hop tong quat: neu gia su truong hop xau nhat tim kiem tuyen tinh phai so sanh n lan con tim kiem nhi phan chi can so sanh log2(n) lan

// bai 2: Cho day so: 10  32  8  50  08  25  65  31  18  23
// a,
// - sap xep chon: duyet tu dau day tim phan tu min dua ve dau day
//   + buoc 1: 8   32  10  50  08  25  65  31  18  23
//   + buoc 2: 8   08  10  50  32  25  65  31  18  23
//   + buoc 3: 8   08  10  50  32  25  65  31  18  23
//   + buoc 4: 8   08  10  18  32  25  65  31  50  23
//   + buoc 5: 8   08  10  18  23  25  65  31  50  32
//   + buoc 6: 8   08  10  18  23  25  65  31  50  32
//   + buoc 7: 8   08  10  18  23  25  31  65  50  32
//   + buoc 8: 8   08  10  18  23  25  31  32  50  65
//
// - sap xep chen: duyet tu dau day tim phan tu nho hon chen vao day da sap xep
//   + buoc 1: 10  32  8   50  08  25  65  31  18  23
//   + buoc 2: 8   10  32  50  08  25  65  31  18  23
//   + buoc 3: 8   10  32  50  08  25  65  31  18  23
//   + buoc 4: 8   08  10  32  50  25  65  31  18  23
//   + buoc 5: 8   08  10  25  32  50  65  31  18  23
//   + buoc 6: 8   08  10  25  32  50  65  31  18  23
//   + buoc 7: 8   08  10  25  31  32  50  65  18  23
//   + buoc 8: 8   08  10  18  25  31  32  50  65  23
//   + buoc 9: 8   08  10  18  23  25  31  32  50  65
//
// - sap noi bot: duyet tim phan tu max dua ve cuoi day
//   + buoc 1: 10  8   32  08  25  50  31  18  23  65
//   + buoc 2: 8   10  08  25  32  31  18  23  50  65
//   + buoc 3: 8   08  10  25  31  18  23  32  50  65
//   + buoc 4: 8   08  10  25  18  23  31  32  50  65
//   + buoc 5: 8   08  10  18  23  25  31  32  50  65

// b,
// - sap xep phan doan (Quick Sort): chon phan tu chot (pivot), chia day thanh 2 phan nho hon chot va lon hon chot
//   + chon pivot = 23: [10  8  08  18]  23  [32  50  25  65  31]
//   + phan doan ben trai [10  8  08  18] (pivot 18) -> [8  08  10  18]
//   + phan doan ben phai [32  50  25  65  31] (pivot 31) -> [25]  31  [32  50  65]
//   + ket qua: 8  08  10  18  23  25  31  32  50  65
//
// - sap xep vun dong (Heap Sort): tao cay nhi phan Max-Heap roi dua phan tu goc (max) ve cuoi day
//   + tao dong ban dau: 65  50  25  32  23  8  10  31  18  08
//   + dua 65 ve cuoi, vun dong lai: 50  32  25  31  23  8  10  08  18  [65]
//   + dua 50 ve cuoi, vun dong lai: 32  31  25  18  23  8  10  08  [50  65]
//   + lap lai den het day: 8  08  10  18  23  25  31  32  50  65
//
// - sap xep tron (Merge Sort): chia doi day den khi con 1 phan tu roi tron lai theo thu tu tang dan
//   + chia 2 nua: [10  32  8  50  08] va [25  65  31  18  23]
//   + tron tung cap nho: [10  32], [8  50], [08] va [25  65], [18  31], [23]
//   + tron nua trai: [8  08  10  32  50], tron nua phai: [18  23  25  31  65]
//   + tron 2 nua lai: 8  08  10  18  23  25  31  32  50  65

// e,
// - tao cay nhi phan tim kiem: phan tu nho hon cho sang nhanh trai, lon hon cho sang nhanh phai
//   + goc = 10
//   + 32 > 10 -> phai 10
//   + 8 < 10 -> trai 10
//   + 50 > 10, > 32 -> phai 32
//   + 08 = 8 -> bo qua (hoac chen trai 8)
//   + 25 > 10, < 32 -> trai 32
//   + 65 > 10, > 32, > 50 -> phai 50
//   + 31 > 10, < 32, > 25 -> phai 25
//   + 18 > 10, < 32, < 25 -> trai 25
//   + 23 > 10, < 32, < 25, > 18 -> phai 18
// - tim phan tu 18 trong cay:
//   + so sanh voi goc 10: 18 > 10 -> qua phai (32)
//   + so sanh voi 32: 18 < 32 -> qua trai (25)
//   + so sanh voi 25: 18 < 25 -> qua trai (18)
//   + so sanh voi 18: 18 == 18 -> tim thay

// bai 3
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// - tim min/max tren mang da sap xep bang nhi phan:
int timMinMang(int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] > a[r]) l = m + 1;
        else r = m;
    }
    return a[l];
}

int timMaxMang(int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (a[m] < a[l]) r = m - 1;
        else l = m;
    }
    return a[l];
}

// - tim min tren cay nhi phan tim kiem: di ve nut ngoai cung ben trai
int timMinCay(Node *root) {
    Node *p = root;
    while (p->left != NULL) p = p->left;
    return p->data;
}

// - tim max tren cay nhi phan tim kiem: di ve nut ngoai cung ben phai
int timMaxCay(Node *root) {
    Node *p = root;
    while (p->right != NULL) p = p->right;
    return p->data;
}

// bai 4
int ktraSNT(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int timNhiPhan(int a[], int n, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

void timSNTTrongMang(int a[], int n) {
    // tim max trong mang a de tao mang cac so nguyen to tang dan
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) max = a[i];
    }
    int snt[1000], k = 0;
    for (int i = 2; i <= max; i++) {
        if (ktraSNT(i) == 1) {
            snt[k] = i;
            k++;
        }
    }

    // dung tim kiem nhi phan kiem tra tung phan tu a[i] co nam trong mang snt khong
    printf("Cac so nguyen to trong mang: ");
    for (int i = 0; i < n; i++) {
        if (timNhiPhan(snt, k, a[i]) != -1) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}

// bai 5
typedef struct {
    char ten[50];
    float diem;
} ThiSinh;

void chonThiSinhCaoNhat(ThiSinh ds[], int n, int m) {
    // sap xep giam dan theo diem, dung strcpy cua string.h de doi ten
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].diem < ds[j].diem) {
                float tgDiem = ds[i].diem;
                ds[i].diem = ds[j].diem;
                ds[j].diem = tgDiem;

                char tgTen[50];
                strcpy(tgTen, ds[i].ten);
                strcpy(ds[i].ten, ds[j].ten);
                strcpy(ds[j].ten, tgTen);
            }
        }
    }

    // in m nguoi cao diem nhat
    printf("Danh sach %d nguoi diem cao nhat:\n", m);
    for (int i = 0; i < m && i < n; i++) {
        printf("%s - %.1f\n", ds[i].ten, ds[i].diem);
    }
}

int main() {
    int a[] = {10, 32, 8, 50, 8, 25, 65, 31, 18, 23};
    int n = 10;

    timSNTTrongMang(a, n);

    ThiSinh ds[4];
    strcpy(ds[0].ten, "An");    ds[0].diem = 7.5;
    strcpy(ds[1].ten, "Binh");  ds[1].diem = 9.0;
    strcpy(ds[2].ten, "Cuong"); ds[2].diem = 8.5;
    strcpy(ds[3].ten, "Dung");  ds[3].diem = 9.5;

    chonThiSinhCaoNhat(ds, 4, 2);

    return 0;
}