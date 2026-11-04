#include <stdio.h>
#include <stdlib.h>

// ỨNG DỰNG CỦA DANH SÁCH LIÊN KẾT-MA TRẬN THƯA 

// struct value_list{
//     int colum_index;
//     int value;
//     struct value_list *next;
// };
// struct row_list{
//     int row_number;
//     row_list *link_dow;
//     value_list *link_right;
// };
// cộng đa thức 
// p(x) = a1*x^e1... axn^en
// struct polynom{
//     int coef; // he so 
//     int exp;   // so mu
//     struct polynom *next;
// };
// typedef struct polynom polynom;
// polynom *ptr1, *ptr2, *ptr;
// void cong(polynom **node){
//     polynom *polynom, *node, *ptr, *ptr1, *ptr2;
//     node = new polynom;
//     polynomsum = node;
//     while(ptr1 != NULL && ptr2 != NULL){
//         ptr = node;
//         if(ptr1->exp < ptr2->exp){
//             node->coef = ptr2->coef;
//             node->exp = ptr2->exp;
//             ptr2 = ptr2->next; // update ptr list 2
//         }
//         else if(ptr1->exp > ptr2->exp){
//             node->coef = ptr1->coef;
//             node->exp = ptr1->exp;
//             ptr1 = ptr1->next;  update ptr list 1
//         }
//         else{
//             node->coef = ptr2->coef + ptr1->coef;
//             node->exp = ptr2->exp 
//             ptr1 = ptr1->next;   // update ptr list 1
//             ptr2= ptr2->next; // update ptr list 2
//         }
//         node = new polynom
//         ptr->next = node  // update ptr listresult
//     }// end of while
// }

// cycle linked list 

// 4. ngăn xếp (stack)
// LIFO: PUSH, POP
// mang, ngan xep 
// mang dinh luu vi tri cuoi
// overflow, underflow
// ngan xeo top nam o head 
// ung dung truc tiep
// - lịch sử duyệt trang trong trinh duyet web
// -day undo trong bo soan thao
// - call stack ..
// - chinh bien dich compilers
// Parenthenses matching:
int parenthesesmatching(char c[], int n) {
    // Dùng mảng làm stack tĩnh tạm thời
    char stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {
        char ch = c[i];

        // Nếu là dấu mở ngoặc, push vào stack
        if (ch == '(' || ch == '[' || ch == '{') {
            stack[++top] = ch;
        } 
        // Nếu là dấu đóng ngoặc
        else if (ch == ')' || ch == ']' || ch == '}') {
            // Stack rỗng -> thiếu ngoặc mở tương ứng
            if (top == -1) {
                return 0;
            }

            char open = stack[top--];
            if ((ch == ')' && open != '(') ||
                (ch == ']' && open != '[') ||
                (ch == '}' && open != '{')) {
                return 0; // Không khớp loại ngoặc
            }
        }
    }

    // Nếu stack rỗng thì chuỗi hợp lệ (1), còn phần tử là không hợp lệ (0)
    return (top == -1) ? 1 : 0;
}
// dao nguoc tu cho truoc 
// tinh gia chi bieu thuc: s1: luuu toan hang, s2 luu phep toan
// doi co so 

// HÀNG ĐỢI (QUEUE)
//FIFO
// back||rear||tail   front||head
// Enqueue(đưa vao), Dequeue(đưa ra)
// su dung mang, dslk
// vong tron quan quanh
// struct node{
//     Datatype element;
//     struct node *next;
// };
// struct queue{
//     node *front;
//     node *rear;
// }