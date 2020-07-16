//
// Created by admin on 2020/7/14.
//
#include "demo.h"

/*
 * 创建线性表，初始元素个数为0
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
SqList CreateSqList(){
    Polynomial *elem = (Polynomial *)malloc(sizeof(Polynomial)*MAXELEMLENGTH);
    if (!elem){
        exit(0);
    }
    SqList sqList;
    sqList.elem = elem;
    sqList.length = 0;
    return sqList;
}

/*
 * 添加元素，同时个数自增
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
int AddPolynomial(SqList *L,Polynomial data){
    if (L->length < MAXELEMLENGTH) {
        L->elem[L->length++] = data;
        return 1;
    } else{
        return 0;
    }
}

/*
 * 获取目标序号的项
 * 注：不是索引，是正整数N+
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
Polynomial GetPolynomial(SqList *L,int index){
    if (index > 0 && index <= L->length){
        return L->elem[index-1];
    } else{
        printf("\nout of range\n");
    }
}

/*
 * 遍历查询目标项的序号
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int FindPolynomialIndex(SqList *L,Polynomial data){
    for (int i = 0; i < L->length; ++i) {
        if (L->elem[i].index == data.index && L->elem[i].coefficient == L->elem[i].coefficient){
            return i+1;
        }
    }
    return -1;
}

/*
 * 判断目标序号是否存在
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
int IsExistPolynomial(SqList *L,int index){
    if (index > 0 && index <= L->length){
        return 1;
    } else{
        return 0;
    }
}

/*
 * 删除目标序号，个数自减
 * 时间复杂度:O(n)
 * 空间复杂度:O(1)
 */
int DeletePolynomial(SqList *L,int index){
    if (IsExistPolynomial(L,index)){
        for (int i = index-1; i < L->length-1; ++i) {
            L->elem[i] = L->elem[i+1];
        }
        L->length--;
        return 1;
    } else{
        return 0;
    }
}

/*
 * 改变目标序号的项
 * 时间复杂度:O(1)
 * 空间复杂度:O(1)
 */
int ChangePolynomial(SqList *L,int index,Polynomial data){
    if (IsExistPolynomial(L,index)){
        L->elem[index-1] = data;
        return 1;
    } else{
        return 0;
    }
}

/*
 * 多项式相加
 * 时间复杂度:O(2n)
 * 空间复杂度:O(2n)
 */
SqList UnionSqList(SqList *L,SqList *P){
    int L_start = 0;
    int P_start = 0;
    Polynomial L_Polynomial = L->elem[L_start];
    Polynomial P_Polynomial = P->elem[P_start];
    Polynomial *elem = (Polynomial *)malloc(sizeof(Polynomial) * (L->length+P->length));
    if (!elem){
        exit(0);
    }
    SqList sqList;
    sqList.elem = elem;
    sqList.length = 0;
    while (L_start < L->length && P_start < P->length){
        if (L_Polynomial.index == P_Polynomial.index){
            L_Polynomial.coefficient += P_Polynomial.coefficient;
            if (L_Polynomial.coefficient != 0){
                sqList.elem[sqList.length++] = L_Polynomial;
            }
            L_start ++;
            P_start ++;
            L_Polynomial = L->elem[L_start];
            P_Polynomial = P->elem[P_start];
        } else if (L_Polynomial.index < P_Polynomial.index){
            sqList.elem[sqList.length++] = L_Polynomial;
            L_start ++;
            L_Polynomial = L->elem[L_start];
        } else if (L_Polynomial.index > P_Polynomial.index){
            sqList.elem[sqList.length++] = P_Polynomial;
            P_start ++;
            P_Polynomial = P->elem[P_start];
        }
    }
    while (L_start < L->length){
        sqList.elem[sqList.length++] = L_Polynomial;
        L_start ++;
        L_Polynomial = L->elem[L_start];
    }
    while (P_start < P->length){
        sqList.elem[sqList.length++] = P_Polynomial;
        P_start ++;
        P_Polynomial = P->elem[P_start];
    }
    return sqList;
}