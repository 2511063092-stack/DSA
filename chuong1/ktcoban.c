#include <stdio.h>
#include <time.h>

int maxl(int a[], int l, int m){
    int sum = 0; int max = -1e9;
    for(int i = m; i >= l; i--){
        sum += a[i];
        if(sum > max){
            max = sum;
        }
    }
    return max;
}
int maxr(int a[], int m, int r){
    int sum = 0; int max = -1e9;
    for(int i = m; i <= r; i++){
        sum += a[i];
        if(sum > max){
            max = sum;
        }
    }
    return max;
}

int maxsub(int a[], int l, int r){
    if(l == r) return a[l];
    else{
        int m = (l + r)/ 2;
        int wl = maxsub(a, l, m);
        int wr = maxsub(a, m + 1, r);
        int wm = maxl(a, l, m) + maxr(a, m + 1, r);
        return fmax(wl, fmax(wr, wm));
    }
}

// int dynamicprogramming(){
//     int ei = a[0];
//     int si = a[0];
//     for(int i = i < n; i++){
//         ei = fmax(a[i], a[i]+ ei);
//         si = fmax(si, ei);
//     }
//     return si;
// } o(n - 1)
int main(){
    // duyet toan bo(brute force)
    int n;
    int a[n];
    int max = -1e9;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; i++){
            int sum = 0;
            for(int k = i; k <= j; k++){
            sum += a[k];
            if(sum > max) max = sum;
            }
        }
    }
    // O(n^3); n*n*n/ 2+ n*n/ 2 + n /2
    // duyet toan bo co cai tien
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = i; j < n; i++){
            sum += a[j];
            if(sum > max) max = sum;

            }
        }
        // O() = n*n/ 2 + n / 2

    // thuat toan đe quy(recursive algorithm)
    // dung ki thuat chia de tri(divide_ and _ conquer)
    // chia bai toan can giai thanh cac bai toan con cung dang
    //  maxsub(a, l, r){
    //     if( l = r) return a[l];  // base case: only element
    //     else{
    //         int m = (l + r) / 2;
    //         wl = maxsub(a, l, m);
    //         wr = maxsub(a, m + 1, r);
    //         wm = maxcrossmidpoint(a, l, m, r);
    //         return max(wl, wr, wm);
    //     }
    //  }

    // thuat toan quy hoach dong(dynamic programming )
    // 3 giai doan 
    //1. divide
    //2. ghi nhan loi giai
    //3. tong hop loi giai(bai toan co kich thuoc lon)
    
    // algorithms
    // input, output, chinh sac, huu han, don tri, tong quat
    // do phuc tap(complexity)
     clock_t startT = clock();
     someOperation(); // goi ham chua thuat toan do 
     clock_t endT = clock();
     clock_t clockTicksTaken = endT - startT;
     double timeInseconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    
     // 1.3 kí hiệu tiệm cận
     // - kí hiệu theta tốc độ tăng bằng nhau 
     // - kí hiệu O lớn(big oh) tốc độ tăng <=  f(n) = o(g(n));
     // - omega lớn >= f(n) >= g(n)
     // định lý: đố với hai hàm bất kì f(n) g(n) f(n) = theta(g(n)) khi và chỉ khi O(N) = omega(n)
     //1.4 Pseudecode giả ngữ 
    //  1.5. phân tích thuật toán 
    //- phép toán cơ bản: bị chẳn bởi hằng số k phủ thuộc kích thước dữ liệu
    // 1, cấu trúc tuần tự 
    //2, vòng lặp for
    // 3,  vòng for lồng nhau
    // 4,if/else
    //- câu lệnh đặc trưng 
    // 1.6 giai cong thuc de quy 
    // pp the quay lui


  }