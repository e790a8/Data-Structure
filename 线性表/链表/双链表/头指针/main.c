#include <stdio.h>
#include "demo.h"
int main()
{
    int indexL[] = {0,1,2,3,4};
    int indexQ[] = {0,1,2,4,5,6};
    float coefficientL[] = {10,5,-4,3,2};
    float coefficientQ[] = {-3,8,4,-5,7,-2};
    Polynomial polynomial;
    LinkList linkListL,linkListQ;
    linkListL = CreateLinkList();
    linkListQ = CreateLinkList();
    for (int i = 0; i < sizeof(indexL)/sizeof(int); ++i) {
        polynomial.index = indexL[i];
        polynomial.coefficient = coefficientL[i];
        AddPolynomial(linkListL,polynomial);
    }
    for (int j = 0; j < sizeof(indexQ)/sizeof(int); ++j) {
        polynomial.index = indexQ[j];
        polynomial.coefficient = coefficientQ[j];
        AddPolynomial(linkListQ,polynomial);
    }
    LinkList  linkList,temp;
    linkList = UnionLinkList(linkListL,linkListQ);
    temp = linkList->next;
    while (temp){
        if (!temp->next){
            printf("%.0f*X^%d",temp->data.coefficient,temp->data.index);
        }else{
            printf("%.0f*X^%d+",temp->data.coefficient,temp->data.index);
        }
        temp = temp->next;
    }
    return 0;
}
