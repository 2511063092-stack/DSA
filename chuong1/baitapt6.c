#include <stdio.h>
#define MAX 100
// bai 1
// SYAEUQTEI
// stack: o,n

// bai2 
// a
// A B + U V - C * /
// b 
// M = 2

// bai 3
// M = 18

// bai 4
// EASYQUESTI
// STACK: O, N


// bai 5

typedef struct {
    int data[MAX];
    int top;
} Stack;

void InitStack(Stack *s) {
    s->top = -1;
}

int IsEmptyStack(Stack *s) {
    return (s->top == -1);
}

void Push(Stack *s, int x) {
    if (s->top < MAX - 1) {
        s->top++;
        s->data[s->top] = x;
    }
}

int Pop(Stack *s) {
    if (!IsEmptyStack(s)) {
        int val = s->data[s->top];
        s->top--;
        return val;
    }
    return -1;
}

// Hàm đổi thập phân sang nhị phân
void DecToBin(int n) {
    Stack s;
    InitStack(&s);

    if (n == 0) {
        printf("0\n");
        return;
    }

    int temp = n;
    while (temp > 0) {
        Push(&s, temp % 2);
        temp = temp / 2;
    }

    printf("Gia tri nhi phan cua %d la: ", n);
    while (!IsEmptyStack(&s)) {
        printf("%d", Pop(&s));
    }
    printf("\n");
}

// bai 6

typedef struct {
    int items[MAX];
    int front;
    int rear;
    int count;
} Queue;

// Khởi tạo hàng đợi rỗng
void CreateQ(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Kiểm tra hàng đợi có rỗng không
int EmptyQ(Queue *q) {
    return (q->count == 0);
}

// Thêm phần tử vào cuối hàng đợi
void AddQ(Queue *q, int x) {
    if (q->count < MAX) {
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = x;
        q->count++;
    }
}

// Lấy phần tử ở đầu ra khỏi hàng đợi
int RemoveQ(Queue *q) {
    if (!EmptyQ(q)) {
        int val = q->items[q->front];
        q->front = (q->front + 1) % MAX;
        q->count--;
        return val;
    }
    return -1;
}

// 6.a: Tìm phần tử ở cuối hàng đợi, để lại hàng đợi rỗng
int TimCuoi_XoaRong(Queue *q) {
    int val = -1;
    while (!EmptyQ(q)) {
        val = RemoveQ(q);
    }
    return val;
}

// 6.b: Tìm phần tử thứ n, làm hàng đợi mất n phần tử đầu tiên
int TimThuN_XoaN(Queue *q, int n) {
    if (n <= 0 || n > q->count) return -1;
    int val = -1;
    for (int i = 1; i <= n; i++) {
        val = RemoveQ(q);
    }
    return val;
}

// 6.c: Tìm phần tử ở đầu hàng đợi nhưng không xoá nó
int TimDau_KhongXoa(Queue *q) {
    if (EmptyQ(q)) return -1;

    int first = RemoveQ(q);
    int totalRemaining = q->count;

    // Đưa phần tử đầu vào đuôi, rồi xoay các phần tử còn lại về đúng trật tự
    AddQ(q, first);
    for (int i = 0; i < totalRemaining; i++) {
        AddQ(q, RemoveQ(q));
    }
    return first;
}

// 6.d: Tìm phần tử thứ n nhưng không làm thay đổi giá trị và thứ tự hàng đợi
int TimThuN_KhongDoi(Queue *q, int n) {
    if (n <= 0 || n > q->count) return -1;

    int target = -1;
    int total = q->count;

    // Lần lượt lấy ra kiểm tra và đẩy lại về đuôi đủ 1 vòng chu kỳ
    for (int i = 1; i <= total; i++) {
        int x = RemoveQ(q);
        if (i == n) {
            target = x;
        }
        AddQ(q, x);
    }
    return target;
}



int main() {
    printf("===== KIEM TRA BAI 5: STACK DOI THAP PHAN SANG NHI PHAN =====\n");
    DecToBin(19);
    DecToBin(42);

    printf("\n===== KIEM TRA BAI 6: CAC THAO TAC TREN HANG DOI =====\n");
    Queue q;
    
    // Khoi tao va nap du lieu: 10, 20, 30, 40, 50
    CreateQ(&q);
    for (int i = 1; i <= 5; i++) {
        AddQ(&q, i * 10);
    }

    // 6.c: Tim phan tu dau tien (khong lam thay doi hang doi)
    printf("Phan tu dau hang doi: %d\n", TimDau_KhongXoa(&q));
    printf("So phan tu hien tai: %d\n", q.count);

    // 6.d: Tim phan tu thu 3 (khong lam thay doi hang doi)
    printf("Phan tu thu 3 la: %d\n", TimThuN_KhongDoi(&q, 3));
    printf("So phan tu sau khi tim vi tri 3: %d\n", q.count);

    // 6.b: Tim phan tu thu 2, xoa 2 phan tu dau tien
    printf("Tim va xoa den vi tri 2, phan tu thu 2 la: %d\n", TimThuN_XoaN(&q, 2));
    printf("So phan tu con lai: %d\n", q.count);

    // 6.a: Tim phan tu cuoi cung va lam rong hang doi
    printf("Phan tu cuoi cung cua hang doi: %d\n", TimCuoi_XoaRong(&q));
    printf("Hang doi da rong hay chua? %s\n", EmptyQ(&q) ? "Dung (Rong)" : "Sai");

    return 0;
}