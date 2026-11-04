#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* =========================================================================
   PHẦN 1: BÀI TẬP 1 - DANH SÁCH LIÊN KẾT ĐƠN LƯU TRỮ SỐ NGUYÊN
   ========================================================================= */

typedef struct IntNode {
    int data;
    struct IntNode* next;
} IntNode;

IntNode* createIntNode(int value) {
    IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void appendInt(IntNode** head, int value) {
    IntNode* newNode = createIntNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    IntNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printIntList(IntNode* head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    IntNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeIntList(IntNode** head) {
    IntNode* current = *head;
    IntNode* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

void runBaiTap1() {
    IntNode* head = NULL;
    int n;

    printf("\n--- BAI TAP 1: DANH SACH SO NGUYEN ---\n");
    printf("Nhap so luong phan tu n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%d", &x);
        appendInt(&head, x);
    }

    printf("Danh sach so nguyen da nhap: ");
    printIntList(head);

    freeIntList(&head);
}

/* =========================================================================
   PHẦN 2: BÀI TẬP 2 - DANH SÁCH LIÊN KẾT ĐƠN LƯU TRỮ HỆ SỐ VÀ SỐ MŨ
   ========================================================================= */

typedef struct TermNode {
    double coef;             // Hệ số
    int exp;                 // Số mũ
    struct TermNode* next;
} TermNode;

TermNode* createTermNode(double coef, int exp) {
    TermNode* newNode = (TermNode*)malloc(sizeof(TermNode));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void appendTerm(TermNode** head, double coef, int exp) {
    TermNode* newNode = createTermNode(coef, exp);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    TermNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printPolynomial(TermNode* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    TermNode* temp = head;
    int isFirst = 1;

    while (temp != NULL) {
        if (temp->coef != 0) {
            if (!isFirst) {
                if (temp->coef > 0) printf(" + ");
                else printf(" - ");
            } else {
                if (temp->coef < 0) printf("-");
                isFirst = 0;
            }

            double c = fabs(temp->coef);
            if (temp->exp == 0) {
                printf("%.2lf", c);
            } else {
                if (c != 1.0) {
                    printf("%.2lf", c);
                }
                printf("x");
                if (temp->exp != 1) {
                    printf("^%d", temp->exp);
                }
            }
        }
        temp = temp->next;
    }

    if (isFirst) {
        printf("0");
    }
    printf("\n");
}

void freePolynomial(TermNode** head) {
    TermNode* current = *head;
    TermNode* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

void runBaiTap2() {
    TermNode* poly = NULL;
    int n;

    printf("\n--- BAI TAP 2: DANH SACH DA THUC (HE SO, SO MU) ---\n");
    printf("Nhap so luong so hang cua bieu thuc: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        double coef;
        int exp;
        printf("Nhap so hang thu %d (he so, so mu): ", i + 1);
        scanf("%lf %d", &coef, &exp);
        appendTerm(&poly, coef, exp);
    }

    printf("Bieu thuc da nhap: P(x) = ");
    printPolynomial(poly);

    freePolynomial(&poly);
}

/* =========================================================================
   HÀM MAIN ĐIỀU KHIỂN
   ========================================================================= */

int main() {
    int choice;
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Bai tap 1: Danh sach lien ket so nguyen\n");
        printf("2. Bai tap 2: Danh sach lien ket bieu thuc ham mu\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                runBaiTap1();
                break;
            case 2:
                runBaiTap2();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long nhap lai!\n");
        }
    } while (choice != 0);

    return 0;
}