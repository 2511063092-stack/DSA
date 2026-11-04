#include <stdio.h>
#define ll long long

double tb(double a[], int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    return sum / n;
}
int cmp(const void *a, const void *b){
    int *x = (int*)a;
    int *y = (int*)b;
    return x - y;s
}
int main(){
    printf("NGO QUAN DUC - DH15C6");
    double a[100];
    // nhap 
    int n; scanf("%d", n);
    for(int i = 0; i < n; i++){
        scanf("%lf", &a[i]);
    }
    // in mang 
    for(int i = 0; i < n; i++){
        printf("sinh vien %d: %lf", i, a[i]);
    }
    //b
    printf("diem tb:  %lf", tb(a, n));
    //c, xet loai
    qsort(a, n, sizeof(double), cmp);
    for(int i = 0; i < n; i++){
        printf(" sinh vien %d: %lf", i, a[i]);
    }
    // d, tim va in
    for(int i = 0; i < n; i++){
        if(a[i] > 8.5) printf("sinh vien %d: %lf", i, a[i]);
        else break;
    }
    
    


}