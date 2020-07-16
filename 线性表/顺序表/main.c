#include <stdio.h>
#include "demo.h"
int main()
{
    int indexL[] = {0,1,2,3,4};
    int indexQ[] = {0,1,2,4,5,6};
    float coefficientL[] = {10,5,-4,3,2};
    float coefficientQ[] = {-3,8,4,-5,7,-2};
    Polynomial polynomial;
    SqList sqListL;
    SqList sqListQ;
    sqListL = CreateSqList();
    sqListQ = CreateSqList();
    for (int i = 0; i < sizeof(indexL)/sizeof(int); ++i) {
        polynomial.index = indexL[i];
        polynomial.coefficient = coefficientL[i];
        AddPolynomial(&sqListL,polynomial);
    }
    for (int j = 0; j < sizeof(indexQ)/sizeof(int); ++j) {
        polynomial.index = indexQ[j];
        polynomial.coefficient = coefficientQ[j];
        AddPolynomial(&sqListQ,polynomial);
    }
    SqList sqList;
    sqList = UnionSqList(&sqListL,&sqListQ);
    for (int k = 0; k < sqList.length; ++k) {
        if (k == sqList.length-1){
            printf("%.0f*X^%d",sqList.elem[k].coefficient,sqList.elem[k].index);
        } else{
            printf("%.0f*X^%d+",sqList.elem[k].coefficient,sqList.elem[k].index);
        }
    }
    return 0;
}
