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
 * 遍历查找尾结点，添加项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList L,Polynomial data){
    LinkList temp = L;
    while (temp){
        if (temp->next == L){
            LinkList linkList = (LinkList)malloc(sizeof(LNode));
            linkList->data = data;
            linkList->prior = temp;
            linkList->next = temp->next;
            temp->next = linkList;
            L->prior = linkList;
            break;
        }
        temp = temp->next;
    }
}

/*
 * 获取首元结点，遍历查找项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetLNode(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList != L){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return linkList;
        } else{
            linkList = linkList->next;
        }
    }
    return NULL;
}

/*
 * 获取首元结点，头结点后继
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetFirstLNode(LinkList L){
    if (L->next != L){
        return L->next;
    } else{
        return NULL;
    }
}

/*
 * 获取尾结点，头结点前驱
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetEndLNode(LinkList L){
    if (L->prior != L){
        return L->prior;
    } else {
        return NULL;
    }
}

/*
 * 遍历查询项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList != L){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return 1;
        } else{
            linkList = linkList->next;
        }
    }
    return 0;
}

/*
 * 匹配获取目标项，删除
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
 * 匹配获取目标项，更改
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
 * 获取首元结点，遍历运算
 * 时间复杂度:O(2n)
 * 空间复杂度:O(2n)
 */
LinkList UnionLinkList(LinkList L,LinkList P){
    LinkList L_start = L->next;
    LinkList P_start = P->next;
    LinkList S = CreateLinkList();
    while (L_start != L && P_start != P){
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
    while (L_start != L){
        AddPolynomial(S,L_start->data);
        L_start = L_start->next;
    }
    while (P_start != P){
        AddPolynomial(S,P_start->data);
        P_start = P_start->next;
    }
    return S;
}