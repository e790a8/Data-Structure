//
// Created by admin on 2020/7/15.
//

#include "demo.h"

/*
 * 创建单链表，后继为空
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList CreateLinkList(){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    if (!linkList){
        exit(0);
    }
    linkList->next = NULL;
    return linkList;
}

/*
 *找到尾结点，添加项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList L,Polynomial data){
    LinkList temp = L;
    while (temp){
        if (!temp->next){
            LinkList linkList = (LinkList)malloc(sizeof(LNode));
            linkList->data = data;
            linkList->next = temp->next;
            temp->next = linkList;
            break;
        } else {
            temp = temp->next;
        }
    }
}

/*
 *遍历链表，匹配项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetLNode(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return linkList;
        } else{
            linkList = linkList->next;
        }
    }
    return NULL;
}

/*
 *遍历链表，判断是否存在
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList){
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return 1;
        } else{
            linkList = linkList->next;
        }
    }
    return 0;
}

/*
 * 遍历链表，匹配删除
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int DeletePolynomial(LinkList L,Polynomial data){
    LinkList linkList = L;
    while (linkList){
        if (linkList->next->data.index == data.index && linkList->next->data.coefficient == data.coefficient){
            LinkList temp = linkList->next;
            linkList->next = linkList->next->next;
            free(temp);
            return 1;
        } else {
            linkList = linkList->next;
        }
    }
    return 0;
}

/*
 * 更改项值
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
LinkList UnionLinkList(LinkList L,LinkList P){
    LinkList L_start = L->next;
    LinkList P_start = P->next;
    LinkList S = CreateLinkList();
    while (L_start&&P_start){
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
    return S;
}