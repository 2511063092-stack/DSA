#include <stdio.h>

// preorder: nut goc trc -> con
// postorder: cay con -> goc 
//inorder: cay con trai nhat->goc-> cay con phai

// binary tree 
// dn, tc:
// moi node co nhieu nhat 2 con 
// co thu tu
// max so node tren muc i = 2^i-1 
// so node tren cay max = 2^depth(tree) - 1
// cay nhi phan co n nut: depth(cay) >= log2(n+1)
// full binary tree: moi but trong deu co 2 con, moi nut la deu cung do sau 
// complete binary tree: tat ca muc deu day tru muc cuoi, muc sau nhat lech sang trai nhat co the 
//balanced binary tree: chieu cay cua cay con trai va phai moi nut o checnh lech nhau khong qua 1 don vi
// cay nhi phan dau du thi hoan chinh
// cay nhi phan hoan chinh thi can bang 
// bieu dien cay nhi phan:
// mang: nut goc = 0, tu trai sang phai tu tren xuong duoi, danh chi so ca nut rong 2^depth - 1, cha a[i-1/2]  contrai a[2i+ 1], 2i + 1 > n - 1 thi la la
// con tro: 

// duyet cay 
// BFS, DFS:TGP, GTP, TPG
// mot so ung dung:
// bieu thuc so hoc: prefix expression infix expression, postfix expression 

// ky phap nghich dao ba lan( Reserve polish notation- RPN) mot thuat toan kinh dien trong linh vuc trinh bien dich
// C = A OPT B
// 6 3 9 + 5 * 9 / -
//6 9 5 * 9 / - 
// 6 45 9 / -
// 6 5 - 
// 1
// ki phap hau to: su dung ngan xep 

// evaluationpostfix(stack s, postfixExpression E){
//     // bieu thuc duoc luu o mang E
//     i = 0;
//     while( i < so_ki_tu_trong_bieu_thuc){
//         if(E[i] la toan hang)
//              push E[i] vao stack
//         else if(E[i] la phep toan){
//             1. pop phan tu dâu stack va luu vao bien operand1
//             2. pop phan tu dau stack va luu vao bien in operand2 
//             3. tinh: operand2 op operand1 {op = E[1]}, roi push ket qua vao stack
//         }
//         i += 1;
//     }// end while
//     pop phan tu dau stack, luu vao bien result;
//     return result; // chua ket qua cua bieu thuc
// }

// int evaluationPostfix(string E){
//     stack <int> S;
//     int len = E.length();
//     for(int i = 0; i <len; i ++)
//     {
//         if(E[i] >= '0' && E[i] <= '9')
//            S.push(E[i] - '0');
//         else // E[i] la phep toan 
//         {
//             int op1 = S.top();
//             S.pop();
//             int op2 = S.top();
//             S.pop();
//             switch(E[i]){
//                 case '+':
//                   S.push(op2+op1);
//                 case '-':
//                   S.push(op2-op1);
//                 ...
//             }
//         }
//     }
// return S.top();
// }

// int avaluate(node *root){
//     if(root->left == NULL) //external node
//        return root->data;
//     else {
//         //internal node
//         x = evaluate(root->left);
//         y = evaluate(root->right);
//         goi opt la phep toan o node goc root
//         z = x OPT y
//         return z;
//     }
// }

// 4.4.2 ma huffman
// fixed-length code 
// variable-length code 
// optimum sourrce coding problem
// b1: lay 2 ki tu tan xuat nho nhat x va y 
// xay dung cay co 2 nut x va y, z la goc
// dat f(z) = f(x) + f(y)
// xoa x va y them ki tu z vao bang
// ghep 

// procedure huffman_decode(b)
// // b la xau ma hoa van ban theo ma huffman 
// begin 
// <khoi tao p la goc cua cay huffman>
// while<chua dat den ket thuc cua b> do
// begin
//  x<- bit tiep theo trong cay b;
//  if x = 0 then p <-con trai cua p 
//  else          p <- con phai cua p 
//  if(p la nut la) then 
//  begin 
//  <hien thi ki hieu tuong ung voi nut la>
//  <dat lai p la goc cua cay huffman>
//  end;
//  end;
//  end