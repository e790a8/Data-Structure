//
// Created by admin on 2020/7/15.
//

#include "demo.h"
/*
 * 将后继指向自身
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList CreateLinkList(){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    if (!linkList){
        exit(0);
    }
    linkList->next = linkList;
    return linkList;
}

/*
 * 找到当后继为头结点时，就意味着找到尾结点，创建新结点，新结点的后继为尾结点的后继，尾结点的后继为新结点
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList L,Polynomial data){
    LinkList temp = L;
    while (temp){
        if (temp->next == L){
            LinkList linkList = (LinkList)malloc(sizeof(LNode));
            linkList->data = data;
            linkList->next = temp->next;
            temp->next = linkList;
            break;
        }
        temp = temp->next;
    }
}

/*
 * 当后继指向头结点时，意味着已经查找完毕
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
 * 头结点的后继不为自身时，意味着存在首元结点
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
 * 当头结点的后继不为自身时，意味着存在首元结点；
 * 当结点的后继结点为头结点时，意味着找到尾结点
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetEndLNode(LinkList L){
    LinkList linkList = L->next;
    while (linkList != L) {
        if (linkList->next == L){
            return linkList;
        } else{
            linkList = linkList->next;
        }
    }
    return NULL;
}

/*
 * 当头结点的后继不为自身时，意味着存在首元结点；
 * 然后匹配项
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList != L) {
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return 1;
        } else{
            linkList = linkList->next;
        }
    }
    return 0;
}

/*
 *匹配删除，将匹配结点的后继指向为后继的后继，释放后继。
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int DeletePolynomial(LinkList L,Polynomial data){
    LinkList linkList = L->next;
    while (linkList != L) {
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
 * 获取匹配的结点，如不为空，则替换数据域。
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
 * 获取L、P的首元结点，创建新链表；
 * 如两个结点数据的指数一致，则创建新数据；
 * 新数据指数等于其中一个结点的指数，系数等于两个结点系数和，和不为零，则添加至新链表，两个结点都向后移一位；
 * 如其中一个结点数据的指数较小，则将较小的数据添加至新链表；
 * 当其中一个链表遍历完后，退出循环；
 * 检查链表是否全部遍历，如未遍历完，则将剩余项添加至新链表；
 * 返回新链表。
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
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