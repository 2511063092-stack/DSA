#include <stdio.h>
#include <math.h>


int main(){
    double a, b, c; scanf("%lf%lf%lf", &a, &b, &c);
    if(a == 0){
        if(b == 0){
            if(c == 0) printf("pt co vo so nghiem");
            else printf("phuong trinh vo nghiem");
        }
        else{
            double x = -c / b;
            printf("phuong trinh bac nhat co 1 nghiem: x = %.4lf", x);
        }
    }
    else{
        double delta = b * b - 4 * a *c;
        if(delta < 0){
            printf("phuong trinh vo nghiem vi delta < 0 ");
        }
        else if(delta == 0){
            double x = -b / (2*a);
            printf("phuong trinh co nghiem kep: x = %.4lf", x);
        }
        else{
            double x1 = (-b + sqrt(delta)) / (2*a);
            double x2 = (-b - sqrt(delta)) / (2*a);
            printf("phuong trinh co 2 nghiem phan biet: x1 = %.4lf x2 = %.4lf", x1, x2);
        }
}

// bai 2 
 // xay dung bo test
// STT	a	b	c	Kết quả mong muốn (nghiệm)	Kết quả nhận được khi chạy
// 1	0	0	0	Vô số nghiệm	Vô số nghiệm
// 2	0	0	5	Vô nghiệm	Vô nghiệm
// 3	0	2	-4	x = 2	x = 2.0000
// 4	1	-3	2	x1 = 2, x2 = 1	x1 = 2.0000, x2 = 1.0000
// 5	1	2	1	delta = 0, x = -1	x = -1.0000
// 6	1	1	1	delta = -3 < 0 → vô nghiệm	Vô nghiệm (delta = -3.0000)

// bai 3
    int max_tmp = -1e9;
    int tmp;
    while(scanf("%d", &tmp) != -1){
        if(tmp > max_tmp){
            max_tmp = tmp;
            printf("gia tri lon nhat hien tai: %d", tmp);
        }
    }
}