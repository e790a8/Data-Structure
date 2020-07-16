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
 * 创建新结点，添加至尾结点后，更新尾指针
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
void AddPolynomial(LinkList *L,Polynomial data){
    LinkList linkList = (LinkList)malloc(sizeof(LNode));
    linkList->data = data;
    linkList->next = (*L)->next;
    (*L)->next = linkList;
    *L = linkList;
}

/*
 * 当结点不为尾结点时，匹配项；
 * 当结点为尾结点时，结束检索
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
LinkList GetLNode(LinkList L,Polynomial data){
    LinkList linkList = L;
    do {
        if (linkList->data.index == data.index && linkList->data.coefficient == data.coefficient){
            return linkList;
        } else {
            linkList = linkList->next;
        }
    }while (linkList != L);
    return NULL;
}

/*
 * 尾结点的后继的后继不为尾结点时，意味着存在首元结点
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetFirstLNode(LinkList L){
    if (L->next->next != L){
        return L->next->next;
    } else{
        return NULL;
    }
}

/*
 * 当尾结点的后继不为尾结点时，则存在尾结点
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
LinkList GetEndLNode(LinkList L){
    if (L->next != L){
        return L;
    } else{
        return NULL;
    }
}

/*
 * 当结点不为尾结点时，匹配项；
 * 当结点为尾结点时，结束检索
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
 *当结点不为尾结点时，匹配删除，将匹配结点的后继指向为后继的后继，如需删除的结点为尾结点时，更新尾指针，释放后继；
 *当结点为尾结点时，结束检索；
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int DeletePolynomial(LinkList *L,Polynomial data){
    LinkList linkList = *(L);
    do {
        if (linkList->next->data.index == data.index && linkList->next->data.coefficient == data.coefficient){
            LinkList temp = linkList->next;
            linkList->next = linkList->next->next;
            if (temp == *(L)){
                *(L) = linkList;
            }
            free(temp);
            return 1;
        } else {
            linkList = linkList->next;
        }
    }while (linkList != *(L));
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