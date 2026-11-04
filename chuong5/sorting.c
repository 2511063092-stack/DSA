#include <stdio.h>

// internal sort
//external sort
// parallel sort 
//in place, stable 

// 1. insertion sort 
// lay mot buoc lap lay ra phan tu va xep vao day da duoc sap xep 
void insertionsort(int a[], int n){
    int k, pos, tmp;
    for(k = 1; k < n; k++){
        tmp = a[k];
        pos = k;
        while((pos > 0) && (a[pos - 1] > tmp)){
            a[pos] = a[pos - 1];
            pos = pos - 1;
            a[pos] = tmp;
        }
    }
}

//2. selection sort 
// moi buoc lap chon phan tu nho nhat chua sap xep day len vi tri cuoi sorted
// void selectionsort(int a[], int n){
//     int i, j, index_min;
//     for(int i = 0; i < n - 1; i++){
//         index_min = i;
//         for(int j = i + 1; j < n; j++){
//             if(a[j] < a[index_min]){
//                 index_min = j;
//             }
//         }
//         swap(a[i], a[index_min]);
//     }
// }

// 3. bubble sort
// moi buoc lap day phan tu max ve cuoi day
void bubblesort(int a[], int n){
    int haveswap;
     for(int i = 1; i < n; i++){
        haveswap = 0;
        for(int j  = 1; j <= n - 1; j ++){
            if(a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                haveswap = 1;
            }
        }
        if(haveswap == 0);
        break;
     }
}

// divide and conquer 
// 4. merge sort
// T(n) = 2t(n/2) + o(n), O(nlogn)
// 5. quick sort
// pivot, partition
int partition(int a[], int l, int r){
    int pivot =a[(l + r) / 2];
    while(l < r){
        while(a[l] < pivot) l++;
        while(a[r] > pivot) r--;
        if(l < r){
            swap(&a[l], &a[r]);
            l++; r--;
        }
    }
    return r;
}
// O(NlogN)
// 6. sap xep vun dong( heap sort)
// heap la cau nhi pha:
// - tinh cau truc (structural property): tat ca deu la day, ngoai tru muc cuoi cung, muc cuoi duoc dien tu trai sang phai 
// - tinh co thu tu hay tinh chat dong(heap property): voi moi nut x 
//           + Parent(x) >= x: max-heap 
//           + OR Paren(x) <=: min_heap 
// root = a[1]
// con trai = a[2*i]
// con phai = a[2*i + 1]
// cha = a[i / 2]
// khoi phuc tinh chat max_heap(vun lau dong)
// - max-HEAPIPY:
    // + doi cho nut i voi nut con lon
    // + di chuyen xuong theo cay 
    // +tiep tuc qua trinh cho den khi nut khong con be hon con
    //O(log2n)
// Tao max-heap tu mot mang khong duoc sap xep 
// - BUIL-MAX-heap
// nut la a[n/2]+1.. n
// 1. n = length[A]
// 2. for i <- [n / 2] down to 1
// 3. do max-heapipy(a, i, n)
// O(nlog2n)
// nut co chieu cao h <= [n/ 2^h+1]
// chieu cao cua heap = log2n
// -> 0(n)
// sap xep vun dong
// 1.buil-max-heap
// 2. doi cho a[i] va a[n]
// 3. loai nut n ra khoi max-heap giam kich thuoc di 1
// 4. max-heapipy doi voi nut goc moi de khoi phuc max-heap 
// O(nlog2n)