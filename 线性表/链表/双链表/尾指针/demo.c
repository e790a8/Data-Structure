//
// Created by admin on 2020/7/15.
//

#include "demo.h"

/*
 * 创建双链表，前驱、后继都为NULL
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList CreateLinkList(){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    if (!linkList){
        exit(0);
    }
    linkList->next = NULL;
    linkList->prior = NULL;
    return linkList;
}

/*
 * 添加项，返回尾结点
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList *L,Polynomial data){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    linkList->data = data;
    linkList->prior = *L;
    linkList->next = (*L)->next;
    (*L)->next = linkList;
    *L = linkList;
}

/*
 * 遍历前驱结点，匹配项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetLNode(LinkList L,Polynomial data){
    LinkList linkList = L;
    while (linkList->prior){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return linkList;
        } else{
            linkList = linkList->prior;
        }
    }
    return NULL;
}

/*
 * 遍历前驱结点，获取首元结点
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetFirstLNode(LinkList L){
    LinkList linkList = L;
    while (linkList->prior){
        if (!linkList->prior->prior){
            return linkList;
        }
        linkList = linkList->prior;
    }
}

/*
 * 返回尾结点
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetEndLNode(LinkList L){
    return L;
}

/*
 * 遍历前驱结点，匹配项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(LinkList L,Polynomial data){
    LinkList linkList = L;
    while (linkList->prior){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return 1;
        } else{
            linkList = linkList->prior;
        }
    }
    return 0;
}

/*
 * 匹配项，删除项
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
 * 更改匹配项
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
 *分别获取首元结点，多项式相加
 * 时间复杂度:O(4n)
 * 空间复杂度:O(2n)
 */
void UnionLinkList(LinkList L,LinkList P,LinkList *S){
    LinkList L_start = GetFirstLNode(L);
    LinkList P_start = GetFirstLNode(P);
    while (L_start && P_start){
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
    while (L_start){
        AddPolynomial(S,L_start->data);
        L_start = L_start->next;
    }
    while (P_start){
        AddPolynomial(S,P_start->data);
        P_start = P_start->next;
    }
}