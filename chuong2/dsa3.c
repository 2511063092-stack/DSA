#include <stdio.h>

// cac so do thuạt toan co ban 
int listsize;
int prod(int list[], int k){
    if(k == listsize - 1) return list[k];
    else return list[k] * prod(list, k + 1);
}
int sn(int a[], int n){
    if(n == 1) return a[0];
    else return a[n - 1] + sn(a, n - 1);
}

int hanoitower(int n, char a, char b, char c){
    if(n == 1) return 1;
    else return hanoitower(n - 1, a, b, c) +hanoitower(1, a, c, b) +hanoitower(n -1, b, c, a);
}

// vd: palindrome 
// ta goi palindrome la xau ma doc no tu trai qua phai cung giong nhu doc tu phai qua trai

int palindrome(int a[], int l, int r){
    if(l >= r ) return 1;
    else{
        if(a[l] == a[r]){
            return palindrome(a, l + 1, r - 1);
        }
        else return -1;
    }
}

// vd: duong di tren luoi o
int countpath(i, j, d, c){
    if(i == d || j == c){
        return 1;
    }
    else return countpath(i + 1, j, d, c) + countpath(i, j + 1, d, c) + countpath(i +1, j + 1, d, c);
}
// 2.4 phan tich thuat toan de qui
// 2.5 de qui co nho 
// - tao mang d[n][k] ktao ban dau = -1 
// kiem tra d[n][k] != -1 thi da dc tinh 

int D[100][100]; //D[n][k] = c[n][k];
int c(int n, int k){
    if(k == 0 || k == n) return 1;
    else return c(n - 1, k - 1) + c(n - 1, k);
}
int c_conho(int n, int k){
    if(k == 0 || k = n) return 1;
    if(D[n][k] != - 1) return D[n][k];
    else{
        D[n][k] = c_conho(n - 1, k - 1) + c_conho[n -1, k];
        return D[n][k];
    }
}
// clock_t startT = clock();
//      someOperation(); // goi ham chua thuat toan do 
//      clock_t endT = clock();
//      clock_t clockTicksTaken = endT - startT;
//      double timeInseconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    
int m[100] = {-1};
int fabonacci(int n){
    if(n == 0 || n == 1) return 1;
    
    if(m[n] != -1) return m[n];
    else{ 
        m[n] = fibonacci(n -1) + fibonacci(n - 2);
        return m[n];
    }
}
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j <=k; j++ ) D[i][j] = - 1;
    // }
    // clock_t = startT1 = clock();
    // long long kq1 = c_conho(n, k);
    // clock_t endT1 = clock();

    // clock_t startT2 = clock();
    // long long kq2 = c(n, k);
    // clock_t endT2 = clock();

    // printf("%.7f %.7f", (double)(endT1 - startT1) / CLOCKS_PER_SEC);
// 3. so do thuat toan quay lui
// bai toan liet ke(Q): D la tap loi giai chap nhan duoc cua bai toan thoa man tinh chat p 
// loi giai bo phan cap k ( 0 <= k <= n) bo co thu tu k thanh phan
// *thuat toan quay lui duoc xay dung dua tren viec xay dung dan dan thanh phan cua loi giai
// * bat dau tu loi giai rong().
// * tren co so tinh chat p chon ra tap ca UCV cua loi giai S1 tap con cua A1 bo sung vao loi giai rong
// * loi giai bo phan cau 1 
// * thanh phan cap 2 (a1, a2.. an);
// Sk != rong; Sk = rong

// vd: liet ke cac xau nhi phan co do dai n 
int a[100];

void ghinhan(){
    for(int i = 0; i < n; i++){
        printf("%d", a[i]);
    }
}
void try(int k){
    // xay dung bit thu k
    for(int i = 0; i <= 1; i++){
       a[k] = i;
       if(k == n) ginhan();
       else try(k + 1);
    }
}
// liet ke tap con m tap con cua n 
void try1(int k){
    for(int i = a[k - 1] + 1; i <= n - m +k; i++){
        a[k] = i;
        if(k == m) ghinhan();
        else try1(k + 1);
    }
}

int check(int j, int k){
    for(int i = 1; i <= k - 1; i++){
        if(j == a[i]) return 0;
        else return 1;
    }
}

void try3(int k){
    for(int i = 1; i <= n; i++){
        if(check(i, k)){
            a[k] = i
            if(k == n) ghinhan();
            else truy3(k + 1);
        }
    }
}

int check1(int j, int k){// 1 neu dat dc o k, j neu k trung cot va duong cheo
   // (1, ai), (2, a[2])...(k -1, a[k - 1])
   for(int i = 1; i <= k - 1; i++){
    if(j == a[i] || abs(j -a[i]) == k - i) return 0;
    else return 1;
   }
}
// bai toan sap xep hau the n-queen problem 

void queen(int k){  //xac dinh toa do cot cua quan hau thu k dang nam o dong thu k
    // n cot: 1, 2.. n
    //cot j != a[1], a[2].. a[k -1]; k cung cot
    // j - a[i] != k - i voi i = 1..k k cung duong cheo 
    for( int j = 1; j <= n - 1; j++){
        if(check1(j, k)){
            a[k] = j;
            if(k == n) ghinhan();
            else queen(k + 1);
        }
    }

}

// CHIA DE TRI
// divide
// conquer 
// combine
// vd binary search 
// nhan so nguyen thuat toan karatsuba
// luy thua 

// QUY hoach dong 
// - phan ra 
// ghi nhan loi giai
// tong hop loi giai
// vd fibo 
// fn = fn2 + fn1
// cau truc con toi uu
// so luong bai toan con khong qua lon
// vd 1 Day con lon nhat O(N)
int a[1000];
int mem[1000];
int comp[1000];
int max_sum(int i){
    if(i == 1) return a[i];
    if(comp[i]) return mem[i];
    int res = fmax(a[i], a[i] + max_sum(i - 1));
    mem[i] = res;
    comp[i] = i;
    return res;
}
void trace(int i){ // truy vet
    if(i != 1 && mem[i] == a[i] +mem[i - 1])
    trace(i - 1);
    printf("%d", a[i]);
}
// vd day con chung dai nhat, longest common subsequence - lcs)
// z thuoc a, b
int ai[1000], b1[1000];
int memo[100][100];
int lcs(int i, int j){
    if(i == -1 || j == -1) return 0;
    if(memo[i][j] != -1) return memo[i][j];
    if(ai[i] == b1[j]) memo[i][j] == lcs(i - 1, j - 1) + 1;
    else memo[i][j]== fmax(lcs(i, j - 1), lcs(i - i, j));
    return memo[i][j];
}
void trace1(int i, int j){ // in ra man hinh day con dai nhat 
     if(i == -1 || j == -1) return;
     if(a[i] == b1[j] && memo[i][j] == memo[i-1][j-1] + 1){
        trace(i - 1, j - 1);
        printf("%d", a[i]);
     }
     if(memo[i][j] = memo[i][j - 1]){
        trace(i , j - 1);
        return;
     }
     if(memo[i][j] == memo[i - 1][j]){
        trace(i - 1, j);
        return;
     }

}
int main(){
    try(1);
}