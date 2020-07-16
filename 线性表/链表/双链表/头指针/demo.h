//
// Created by admin on 2020/7/15.
//

#include <stdio.h>
#include <stdlib.h>
#ifndef DATASTRUCTURE_DEMO_H
#define DATASTRUCTURE_DEMO_H
typedef struct {
    int index;
    float coefficient;
}Polynomial;

typedef struct LNode{
    Polynomial data;
    struct LNode *prior;
    struct LNode *next;
}LNode,*LinkList;
//头指针
//创建双链表
LinkList CreateLinkList();
//添加项
int AddPolynomial(LinkList L,Polynomial data);
//根据项获取结点
LinkList GetLNode(LinkList L,Polynomial data);
//获取第一个结点
LinkList GetFirstLNode(LinkList L);
//获取最后一个结点
LinkList GetEndLNode(LinkList L);
//判断是否存在项
int IsExistPolynomial(LinkList L,Polynomial data);
//删除项
int DeletePolynomial(LinkList L,Polynomial data);
//更改项
int ChangePolynomial(LinkList L,Polynomial des,Polynomial src);
//多项式相加
LinkList UnionLinkList(LinkList L,LinkList P);

#endif //DATASTRUCTURE_DEMO_H
