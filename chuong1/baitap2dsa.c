#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// bai 1
typedef struct
{
    int hour;
    int minute;
} Time;
typedef struct 
{
    char matau[10];
    char gakhoihanh[30];
    char gaden[30];
    Time giokhoihanh;
    Time gioden;
} chuyenTau;

chuyenTau banggiotau[20];

// bai 2
typedef struct 
{
    char masv[15];
    char ten[50];
    int namsinh;
    char lop[20];
    float diem;
} sinhvien;

sinhvien danhsachsv[1000];

int a[100000000];
int n = 10000000;
int prime[10000001];
void sang(){
    for(int i = 0; i < n; i++){
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;
    for(int i = 2; i * i < n; i++){
        if(prime[i]){
            for(int j = i * i ; j < n; j+=i){
                prime[j] = 0;
            }
        }
    }
}

int perfect(int n){
    // dinh ly eulclid neu p la snt va (2^p) - 1 cung la so nguyen to thi (2^p) - 1 * 2^(p-1) la so hoan hao
    for(int i = 2; i <= 33; i++){
        if(prime[i]){
            long long tmp1 = pow(2, i) - 1;
            if(prime[tmp1]){
                long long tmp2 = 1ll * tmp1 * pow(2, i -1);
                if(tmp2 == n) return 1;
            }
        }
    }
    return 0;

}
int main(){
    printf("NGO QUAN DUC");
    // bai 3
    int tmp;
    int x = 0;
    while(scanf("%d", &tmp) != -1){
        a[x] = tmp;
        x++;
    }
    for(int i = 0; i < x; i++){
        if(a[i] > 0 && a[i] % 2 != 0 && a[i] % 3 == 0 && a[i] % 5 != 0){
            printf("so le chia het cho 3 k chia het cho 5: %d .vi tri trong mang: %d", a[i], i);
        }
    }
    // vi chi su dung 1 vong for de duyet qua mang nen trong truong hop xau nhat la duyet qua n vong lap =>> O(N);


    // nguyen to
    sang();
    int cnt = 0, odd = 0, even =0;
    for(int i = 0; i < x ; i++){
        if(prime[a[i]]){
            ++cnt;
            if(a[i] % 2 == 0) ++even;
            else ++odd;
        }
    }
    printf("so luong so nguyen to, snt le, snt chan la: %d %d %d", cnt, odd, even);
    // ham sang so nguyen to sang do phuc tap la n/i =>> O(Nloglog(N))

    int y; scanf("%d", &y);
    if(perfect(y)) printf("yes");
    else printf("no");


    
    
}