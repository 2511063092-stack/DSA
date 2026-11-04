#include <stdio.h>
#define ll long long
#include <stdlib.h>

// NGO QUAN DUC- DH15C6

// bai 1
// 1a tinh n!
// 1b tinh luy thua x^n
// 1c tinh log2(n)

// bai 2
// 1.a giai thua
int prime[1005];

void enratothenes(){
    for(int i = 0; i <= 1000; i++){
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;
    for(int i = 0; i <= 1000; i++){
       if(prime[i]){
        for(int j = i * i; j <= 1000; j+=i)
           prime[j] = 0;
       }
    }
}
ll gt(int n){
    ll res = 1;
    for(int i = 2; i <= n; i++){
        if(prime[i]){
           int ep = 0;
           int tmp = n;
           while(tmp >= i){
            ep += tmp/i;
            tmp /= i;
           }
           res *= lt(i, ep);
        }
    }
    return res;
}

// 1.b luy thua nhi phan 
ll lt(int x, int n){
    ll res = 1;
    // xet tung bit cua n
    while(n){
        if(n % 2 == 1){
            // neu b la le bit cuoi cung la 1 
            res *= x;
        }
        x *= x;
        n /= 2;    
    }
    return res;
}

//1.c log2(n)

double log2(int n){
    int res = 0;
        while(n >= 2){
        res += 1;
        n /= 2;
    } return res;
}

// bai 3
// 3.a neu n == k || k == 0 => c(n, k) = 1;
//     neu 0 < k < n => c(n, k) = c(n -1, k - 1) + c(n - 1, k);
int c(int n, int k) {
    if (k == 0 || n == k) {
        return 1;
    }
    return C(n - 1, k - 1) + C(n - 1, k);
}
// 3.b 
// k = 0 c(n, k) = n!/( n -0)! * 0! = n!/ n!*1 = 1
// k = n c(n, k) = n! / (n - n)! * n! = n! / n! = 1;
// 0 < k < n c(n, k) = (n -1)! /(n - k)! * (k - 1)! + (n - 1)! /(n - 1 - k)! * k!
// <=> (n-1)! * k / (n - k)! * k ! + (n - 1)! * (n - k) / (n - k)! * k!
// <=> (n - 1)! * n / (n -k)! * k! = n! / (n - k)! * k! (đpcm)

// 3.c
int c2(int n, int k){
    if(k < 0 || k > n) return 0;
    if( k == 0 || k == n) return 1;
    if(k > n - k){
        k = n - k;
    }
    ll res = 1;
    for(int i = 1; i <= n; i++){
        res *= (n - i + 1) / i;
    }
    return res;
}

// bai 4
// k de qui 
void in(char c[]){
    int len = strlen(c);
    for(int i = len - 1; i >= 0; i--){
        printf("%c", c[i]);
    }
}
// de qui
void recursion(char c[]){
    if(c[0] == '\0') return;
    recursion(c + 1);
    printf("%c", c[0]);
}

// bai 5
void dectobin(int n){
    if(n >= 2)
    dectobin(n / 2);
    printf("%d", n % 2);
}

// bai 6
ll s(int n){
    if(n == 0) return n;
    else{
        if(n % 2 == 0) return -n + s(n - 1);
        else return n + s(n - 1);
    }
}

// bai 7
// 7.1
int queen[8];

int safe(int row, int col){
    for(int i = 0; i < row; i++){
        if(queen[i] == col || abs(queen[i] - col) == abs(i - row)) return 0;
    }
    return 1;
}

void solvequeen(int row){
    if(row == 8){
        return;
    }
    for(int col = 0; col < 8; col++){
        if(safe(row, col)){
            queen[row] = col;
            solvequeen(row + 1);
        }
    }
}

// 7.2
int dx[8] = {2, 2, 1, 1, -2, -2, -1, -1};
int dy[8] = {1, -1, 2, -2, 1, -1, -2, 2};
int board[8][8];

int valid(int nextx, int nexty){
    if((nextx >= 0 && nextx < 8 && nexty >= 0 && nexty < 8) && board[nextx][nexty] == -1) return 1;
    else return 0;
}

int solveknightour(int x, int y, int step){
    if(step == 64) return 1;
    for(int i = 0; i < 8; i++){
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(valid(nextx, nexty)){
            board[nextx][nexty] = step;
            if(solveknightour(nextx, nexty, step + 1)) return 1;
            board[nextx][nexty] = -1;
        }
    }
    return 0;
}

int main(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = - 1;
         }
    }

    if(solveknightour(0, 0, 1)) printf("tim thay loi giai");
}