#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int size;
} ArrayList;

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

struct dnode {
    int data;
    struct dnode *prev;
    struct dnode *next;
};
typedef struct dnode dnode;

struct cnode {
    int data;
    struct cnode *next;
};
typedef struct cnode cnode;

void init_arr(ArrayList *list) {
    list->size = 0;
}

void pushback_arr(ArrayList *list, int x) {
    if (list->size < MAX) {
        list->data[list->size++] = x;
    }
}

void pushfront_arr(ArrayList *list, int x) {
    if (list->size < MAX) {
        for (int i = list->size; i > 0; i--) {
            list->data[i] = list->data[i - 1];
        }
        list->data[0] = x;
        list->size++;
    }
}

void print_arr(ArrayList list) {
    for (int i = 0; i < list.size; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");
}

void sort_arr(ArrayList *list) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = i + 1; j < list->size; j++) {
            if (list->data[i] > list->data[j]) {
                int tmp = list->data[i];
                list->data[i] = list->data[j];
                list->data[j] = tmp;
            }
        }
    }
}

void remove_duplicates_arr(ArrayList *list) {
    if (list->size <= 1) return;
    int k = 1;
    for (int i = 1; i < list->size; i++) {
        if (list->data[i] != list->data[i - 1]) {
            list->data[k++] = list->data[i];
        }
    }
    list->size = k;
}

void remove_odds_arr(ArrayList *list) {
    int k = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->data[i] % 2 == 0) {
            list->data[k++] = list->data[i];
        }
    }
    list->size = k;
}

node *makenode(int x) {
    node *newnode = (node*)malloc(sizeof(node));
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}

void pushback(node **head, int x) {
    node *newnode = makenode(x);
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    node *tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newnode;
}

void pushfront(node **head, int x) {
    node *newnode = makenode(x);
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    newnode->next = *head;
    *head = newnode;
}

void duyet(node *head) {
    node *tmp = head;
    while (tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void sort(node *head) {
    for (node *p = head; p != NULL && p->next != NULL; p = p->next) {
        for (node *q = p->next; q != NULL; q = q->next) {
            if (p->data > q->data) {
                int tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
}

void insert_sorted(node **head, int x) {
    node *newnode = makenode(x);
    if (*head == NULL || (*head)->data >= x) {
        newnode->next = *head;
        *head = newnode;
        return;
    }
    node *tmp = *head;
    while (tmp->next != NULL && tmp->next->data < x) {
        tmp = tmp->next;
    }
    newnode->next = tmp->next;
    tmp->next = newnode;
}

void remove_duplicates(node *head) {
    node *tmp = head;
    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->data == tmp->next->data) {
            node *del = tmp->next;
            tmp->next = del->next;
            free(del);
        } else {
            tmp = tmp->next;
        }
    }
}

void remove_odds(node **head) {
    while (*head != NULL && (*head)->data % 2 != 0) {
        node *del = *head;
        *head = (*head)->next;
        free(del);
    }
    node *tmp = *head;
    while (tmp != NULL && tmp->next != NULL) {
        if (tmp->next->data % 2 != 0) {
            node *del = tmp->next;
            tmp->next = del->next;
            free(del);
        } else {
            tmp = tmp->next;
        }
    }
}

void remove_even_pos_not_div3(node **head) {
    while (*head != NULL && ((*head)->data > 0 && (*head)->data % 2 == 0 && (*head)->data % 3 != 0)) {
        node *del = *head;
        *head = (*head)->next;
        free(del);
    }
    node *tmp = *head;
    while (tmp != NULL && tmp->next != NULL) {
        int val = tmp->next->data;
        if (val > 0 && val % 2 == 0 && val % 3 != 0) {
            node *del = tmp->next;
            tmp->next = del->next;
            free(del);
        } else {
            tmp = tmp->next;
        }
    }
}

void tbc_odd_div15(node *head) {
    long long sum = 0;
    int cnt = 0;
    node *tmp = head;
    while (tmp != NULL) {
        if (tmp->data % 2 != 0 && tmp->data % 15 == 0) {
            sum += tmp->data;
            cnt++;
        }
        tmp = tmp->next;
    }
    if (cnt == 0) {
        printf("Khong co so thoa man\n");
    } else {
        printf("TBC le chia het 15: %.2f\n", (float)sum / cnt);
    }
}

int is_square(int n) {
    if (n < 0) return 0;
    int r = (int)round(sqrt(n));
    return r * r == n;
}

void count_and_print_squares(node *head) {
    int cnt = 0;
    int pos = 1;
    printf("Vi tri so chinh phuong: ");
    node *tmp = head;
    while (tmp != NULL) {
        if (is_square(tmp->data)) {
            printf("%d ", pos);
            cnt++;
        }
        pos++;
        tmp = tmp->next;
    }
    printf("\nSo luong so chinh phuong: %d\n", cnt);
}

dnode *makednode(int x) {
    dnode *newnode = (dnode*)malloc(sizeof(dnode));
    newnode->data = x;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

void pushback_dlist(dnode **head, int x) {
    dnode *newnode = makednode(x);
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    dnode *tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newnode;
    newnode->prev = tmp;
}

void duyet_dlist(dnode *head) {
    dnode *tmp = head;
    while (tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void sort_dlist(dnode *head) {
    for (dnode *p = head; p != NULL && p->next != NULL; p = p->next) {
        for (dnode *q = p->next; q != NULL; q = q->next) {
            if (p->data > q->data) {
                int tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
}

void insert_sorted_dlist(dnode **head, int x) {
    dnode *newnode = makednode(x);
    if (*head == NULL || (*head)->data >= x) {
        newnode->next = *head;
        if (*head != NULL) (*head)->prev = newnode;
        *head = newnode;
        return;
    }
    dnode *tmp = *head;
    while (tmp->next != NULL && tmp->next->data < x) {
        tmp = tmp->next;
    }
    newnode->next = tmp->next;
    newnode->prev = tmp;
    if (tmp->next != NULL) tmp->next->prev = newnode;
    tmp->next = newnode;
}

void remove_odds_dlist(dnode **head) {
    dnode *cur = *head;
    while (cur != NULL) {
        if (cur->data % 2 != 0) {
            dnode *del = cur;
            if (del == *head) {
                *head = del->next;
                if (*head != NULL) (*head)->prev = NULL;
                cur = *head;
            } else {
                if (del->prev != NULL) del->prev->next = del->next;
                if (del->next != NULL) del->next->prev = del->prev;
                cur = del->next;
            }
            free(del);
        } else {
            cur = cur->next;
        }
    }
}

cnode *makecnode(int x) {
    cnode *newnode = (cnode*)malloc(sizeof(cnode));
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}

void pushback_clist(cnode **head, int x) {
    cnode *newnode = makecnode(x);
    if (*head == NULL) {
        *head = newnode;
        newnode->next = *head;
        return;
    }
    cnode *tmp = *head;
    while (tmp->next != *head) {
        tmp = tmp->next;
    }
    tmp->next = newnode;
    newnode->next = *head;
}

void duyet_clist(cnode *head) {
    if (head == NULL) return;
    cnode *tmp = head;
    do {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}

void sort_clist(cnode *head) {
    if (head == NULL || head->next == head) return;
    cnode *p = head;
    do {
        cnode *q = p->next;
        while (q != head) {
            if (p->data > q->data) {
                int tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
            q = q->next;
        }
        p = p->next;
    } while (p->next != head);
}

void remove_odds_clist(cnode **head) {
    if (*head == NULL) return;

    cnode *tail = *head;
    while (tail->next != *head) {
        tail = tail->next;
    }

    while (*head != NULL && (*head)->data % 2 != 0) {
        if (*head == tail) {
            free(*head);
            *head = NULL;
            return;
        }
        cnode *del = *head;
        *head = (*head)->next;
        tail->next = *head;
        free(del);
    }

    if (*head == NULL) return;

    cnode *cur = *head;
    while (cur->next != *head) {
        if (cur->next->data % 2 != 0) {
            cnode *del = cur->next;
            cur->next = del->next;
            if (del == tail) {
                tail = cur;
            }
            free(del);
        } else {
            cur = cur->next;
        }
    }
}

int main() {
    int n, x;
    printf("Nhap n: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    ArrayList arr_xuoi, arr_nguoc;
    init_arr(&arr_xuoi);
    init_arr(&arr_nguoc);

    printf("Nhap %d so: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        pushback_arr(&arr_xuoi, x);
        pushfront_arr(&arr_nguoc, x);
    }
    printf("Mang xuoi: ");
    print_arr(arr_xuoi);
    printf("Mang nguoc: ");
    print_arr(arr_nguoc);

    sort_arr(&arr_xuoi);
    printf("Mang sap xep: ");
    print_arr(arr_xuoi);
    remove_duplicates_arr(&arr_xuoi);
    printf("Mang xoa trung: ");
    print_arr(arr_xuoi);
    remove_odds_arr(&arr_xuoi);
    printf("Mang xoa le: ");
    print_arr(arr_xuoi);

    node *head_xuoi = NULL;
    node *head_nguoc = NULL;

    for (int i = 0; i < n; i++) {
        pushback(&head_xuoi, arr_nguoc.data[n - 1 - i]);
        pushfront(&head_nguoc, arr_nguoc.data[n - 1 - i]);
    }

    printf("\nDSLK xuoi: ");
    duyet(head_xuoi);
    printf("DSLK nguoc: ");
    duyet(head_nguoc);

    sort(head_xuoi);
    printf("DSLK sap xep: ");
    duyet(head_xuoi);

    printf("Nhap so can chen: ");
    scanf("%d", &x);
    insert_sorted(&head_xuoi, x);
    printf("DSLK sau khi chen: ");
    duyet(head_xuoi);

    remove_duplicates(head_xuoi);
    printf("DSLK sau xoa trung: ");
    duyet(head_xuoi);

    tbc_odd_div15(head_xuoi);
    count_and_print_squares(head_xuoi);

    remove_even_pos_not_div3(&head_xuoi);
    printf("DSLK sau xoa chan duong khong chia het cho 3: ");
    duyet(head_xuoi);

    remove_odds(&head_xuoi);
    printf("DSLK sau xoa le: ");
    duyet(head_xuoi);

    dnode *dhead = NULL;
    cnode *chead = NULL;

    pushback_dlist(&dhead, 9);
    pushback_dlist(&dhead, 3);
    pushback_dlist(&dhead, 8);
    pushback_dlist(&dhead, 4);

    printf("\nDSLK kep: ");
    duyet_dlist(dhead);
    sort_dlist(dhead);
    printf("DSLK kep sort: ");
    duyet_dlist(dhead);
    insert_sorted_dlist(&dhead, 5);
    printf("DSLK kep chen 5: ");
    duyet_dlist(dhead);
    remove_odds_dlist(&dhead);
    printf("DSLK kep xoa le: ");
    duyet_dlist(dhead);

    pushback_clist(&chead, 7);
    pushback_clist(&chead, 2);
    pushback_clist(&chead, 9);
    pushback_clist(&chead, 6);

    printf("\nDSLK vong: ");
    duyet_clist(chead);
    sort_clist(chead);
    printf("DSLK vong sort: ");
    duyet_clist(chead);
    remove_odds_clist(&chead);
    printf("DSLK vong xoa le: ");
    duyet_clist(chead);

    return 0;
}