#include <stdio.h>

// searching problem
// 1. tìm kiếm tuần tự 
// 2. tìm kiếm nhị phân 
// 3. cây nhị phân tìm kiếm 
//dynamic set: key, satellite data
// O(h)
// binary search tree
// moi nut x khoa con trai nho hon, cay con phai lon hon 
// moi nut co 1 khoa duy nhat 
// bieu dien cau nhi phan tim kiem 

struct treenode{
    int data;
    struct treenode *l, *r, *p;
};
typedef struct treenode treenode;

// treenode *create_node(int newkey){
//     treenode *newnode = (treenode*)malloc(sizeof(treenode));
//     if(newnode == NULL){
//         return;
//     }
//     else{
//         newnode->key = newkey;
//         new->l = NULL; newnode->r = NULL;
//         newnode->p = NULL;
//     }
//     return newnode;
// }
// treenode *search(int target, treenode *root){
//     if(root == NULL) return NULL;
//     else if(target == root->key) return root;
//     else if(target < root->key) return search(target, root->l);
//     else return search(target, root->r); 
// }
treenode *find_min(treenode *root){
    if(root == NULL) return NULL;
    else{
        if(root->l == NULL) return root;
        else return find_min(root->l);
        //while(root->l != NULL) root = root->l;
    }
}
// void preorder(treenode *root){
//     if(root != NULL){
//         print("%d", root->key);
//         preorder(root->l);
//         preorder(root->r)
//     }
// }
// can trc (predecessor)c cận sau(successor)
treenode *predecessor(treenode *root, treenode *x){
    if(x->l != NULL){
        return find_max(x->l);
    }
    treenode *y = x->p;
    while(y != NULL && x == y->l){
        x = y; y = y->p;
    }
    return y;
}

//insert