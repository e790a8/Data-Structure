//
// Created by admin on 2020/7/15.
//

#include "demo.h"
/*
 * 创建双向循环链表，前驱与后继都指向自身
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList CreateLinkList(){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    if (!linkList){
        exit(0);
    }
    linkList->next = linkList;
    linkList->prior = linkList;
    return linkList;
}

/*
 * 添加项
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList *L,Polynomial data){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    linkList->data = data;
    linkList->prior = *L;
    linkList->next = (*L)->next;
    (*L)->next->prior = linkList;
    (*L)->next = linkList;
    *L = linkList;
}

/*
 * 遍历查找项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetLNode(LinkList L,Polynomial data){
    LinkList linkList = L;
    do {
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return linkList;
        } else{
            linkList = linkList->next;
        }
    }while (linkList != L->next);
    return NULL;
}
/*
 * 获取首元结点，尾结点后继的后继
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetFirstLNode(LinkList L){
    if (L->next->next != L->next){
        return L->next->next;
    } else{
        return NULL;
    }
}

/*
 * 返回尾结点
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetEndLNode(LinkList L){
    if (L != L->next){
        return L;
    } else {
        return NULL;
    }
}

/*
 *遍历匹配目标项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(LinkList L,Polynomial data){
    LinkList linkList = L;
    do {
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return 1;
        } else{
            linkList = linkList->next;
        }
    }while (linkList != L);
    return 0;
}

/*
 * 遍历获取目标项，删除
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int DeletePolynomial(LinkList L,Polynomial data){
    LinkList temp = GetLNode(L,data);
    if (temp){
        temp->prior->next = temp->next;
        temp->next->prior = temp->prior;
        free(temp);
        return 1;
    } else{
        return 0;
    }
}
/*
 * 遍历获取目标项，更改
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int ChangePolynomial(LinkList L,Polynomial des,Polynomial src){
    LinkList linkList = GetLNode(L,des);
    if (linkList){
        linkList->data = src;
        return 1;
    } else{
        return 0;
    }
}

/*
 * 获取首元结点，多项式相加
 * 时间复杂度:O(2n)
 * 空间复杂度:O(2n)
 */
void UnionLinkList(LinkList L,LinkList P,LinkList *S){
    LinkList L_start = L->next->next;
    LinkList P_start = P->next->next;
    while (L_start != L->next && P_start != P->next){
        if (L_start->data.index == P_start->data.index){
            Polynomial polynomial;
            polynomial.index = L_start->data.index;
            polynomial.coefficient = L_start->data.coefficient+P_start->data.coefficient;
            if (polynomial.coefficient != 0){
                AddPolynomial(S,polynomial);
            }
            L_start = L_start->next;
            P_start = P_start->next;
        } else if (L_start->data.index < P_start->data.index){
            AddPolynomial(S,L_start->data);
            L_start = L_start->next;
        } else if (L_start->data.index > P_start->data.index){
            AddPolynomial(S,P_start->data);
            P_start = P_start->next;
        }
    }
    while (L_start != L->next){
        AddPolynomial(S,L_start->data);
        L_start = L_start->next;
    }
    while (P_start != P->next){
        AddPolynomial(S,P_start->data);
        P_start = P_start->next;
    }
}