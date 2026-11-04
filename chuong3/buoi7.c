#include <stdio.h>

// Chuong 3 cac cau truc du lieu co ban
// mang, ban ghi, danh sach lien ket, ngan xep, hang doi
// con tro la biet luu chu dia chi cua 1 doi tuong khac

// * MANG 
// row major order(luu chu uu tien hanh)
// column major oder 
// location(x[i][j]) = start_address +W(i*c +j)
// search, insert, delete, retrieval, traversal
// them/xoa 1 ptu toan bo nho, do phuc tap lon
// ma tran thua(sparse matrix) gay ton bo nho khong can thiet => mang 2 chieu, dong(so ptu khac 0), cot(3), gia tri
// ma tran duong cheo(diagonal matrix) => M(n)
// ma tran tam giac(triangular matrix) => i(i -1)/ 2+ j - 1

// * ban ghi

// * danh sach lien ket (linked list)
// singly linked list, doubly.., circular linked list
// node 

// a, singly linked list: 
// node: 2 phan: data, pointer(dia chi ngang sau)
// khai bao: du lieu, con tro node tiep
// vi du:
// struct nodetype{
//     ....
// };
// struct node{
//     nodetype data;
//     node* next;
// };
// node* head;
// struct list{
//     char data;
//     list *next;
// };
// list *node1, *node2, node3;
// node1 = new list; node2 = new list;
// node1->data = 'a';
// node2->data ..
// node1->next =node2
// node->next =NULL
// node *newnode;
// newwnode = new node
// newnode ->data hoac (*newnode).data
// delete newnode
// bai 1
// struct node{
//     int data;
//     node *next;
// };
// typedef struct node node;
// node *head;



int main(){
    // node *head, *second, *third;
    // head = new node;
    // second = new node;
    // third = new node;
    // head ->data =1;
    // head->next = second
    // second->data = 2;
    // second->next = third;
    // third->data = 3;
    // third->next = NULL;
    // node *cur;
    // for(cur = head; cur != NULL; cur = cur ->next){
    //     printf("%d", cur->data);
    // }
    // delete head, ...
}