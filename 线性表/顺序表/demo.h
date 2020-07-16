//
// Created by admin on 2020/7/14.
//

#ifndef DATASTRUCTURE_DEMO_H
#define DATASTRUCTURE_DEMO_H
#include <stdio.h>
#include <stdlib.h>
#define MAXELEMLENGTH 20

typedef struct {
    int index;
    float coefficient;
}Polynomial;

typedef struct {
    Polynomial *elem;
    int length;
}SqList;
//创建线性表
SqList CreateSqList();
//添加项
int AddPolynomial(SqList *L,Polynomial data);
//根据序号获取项
Polynomial GetPolynomial(SqList *L,int index);
//根据项查找序号
int FindPolynomialIndex(SqList *L,Polynomial data);
//判断是否存在该序号的项
int IsExistPolynomial(SqList *L,int index);
//根据序号删除项
int DeletePolynomial(SqList *L,int index);
//根据序号更改项
int ChangePolynomial(SqList *L,int index,Polynomial data);
//多项式相加
SqList UnionSqList(SqList *L,SqList *P);

#endif //DATASTRUCTURE_DEMO_H
