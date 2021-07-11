#include <stdio.h>
#include "array.h"


/*********************************************************************************
 * function : 数组插入元素
 * input    : pos    : 待插入位置，数组下标加一
 * input    : data   : 待插入的数据，是一个word32值
 * input    : pArray : 数组指针
 * input    : num    : 数组元素个数,数组总好长度比num长,插入后，该值会加一
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.20
 * *********************************************************************************/
VOID daring_arrayElementInsert(int pos, int data, int *pArray, int *num)
{
    int index = 0;
    if(NULL == pArray || NULL == num || 0 == *num)
    {
        printf("input data error!\n");
        return;
    }
    if(*num < pos)
    {
        printf("daring array ElementInsert:data len(%u) must not be smaller than insert position(%u)!\n",*num, pos);
        return;
    }

    for(index=*num;index >= pos-1; index--)
    {
        pArray[index] = pArray[index-1];
    }
    pArray[index+1] = data;
    *num +=1;

    return;
}

/*********************************************************************************
 * function : 数组删除元素
 * input    : pos    : 待删除位置，数组下标加一
 * input    : pArray : 数组指针
 * input    : num    : 数组元素个数,数组总好长度比num长.删除后该值减一
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.20
 * *********************************************************************************/
VOID daring_arrayElementDelete(int pos, int *pArray, int *num)
{
    int index = 0;
    if(NULL == pArray || NULL == num || 0 == *num)
    {
        printf("input data error!\n");
        return;
    }
    if(*num < pos)
    {
        printf("daring array ElementDelete:data len(%u) must not be smaller than insert position(%u)!\n",*num, pos);
        return;
    }
    else if(*num == pos)/*删除最后一个*/
    {
        pArray[*num-1] = 0;
    }

    for(index=pos-1;index < *num-1; index++)
    {
        pArray[index] = pArray[index+1];
    }
    *num -=1;

    return;
}

VOID daring_arrayPrint(int *pArray, int num)
{
    int index = 0;
    if(NULL == pArray)
    {
        printf("input data pArray=NULL!\n");
        return;
    }
    printf("array element is :\n");
    for(index=0;index < num; index++)
    {
        printf("pos %-2u: %-5u\n",index+1, pArray[index]);
    }

    return;
}

/*********************************************************************************
 * function : 生成规定长度的数组并赋值
 * input    : pData     : 初始化的数据
 * input    : num       : 初始化的数据个数
 * input    : arrayLen  : 数组长度
 * output   : 数组首地址
 * comment  :
 * author   : daringwang
 * date     : 2021.6.20
 * *********************************************************************************/
int *daring_arrayCreate(int *pData, int num, int arrayLen)
{
    int *pt = NULL;
    int index = 0;

    if(NULL == pData)
    {
        printf("input data pData=NULL!\n");
        return NULL;
    }
    if(arrayLen < num)
    {
        printf("array len(%u) must not be smaller than data len(%u)!\n",arrayLen, num);
        return NULL;
    }

    pt = (int *)malloc(arrayLen* sizeof(int));

    for(index=0;index <num; index++)
    {
        pt[index] = pData[index];
    }

    return pt;
}

/*********************************************************************************
 * function : 数组插入元素
 * input    : pArray : 数组指针
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.20
 * *********************************************************************************/
VOID daring_arrayDelete(int *pArray)
{
    if(NULL == pArray)
    {
        printf("input data pArray=NULL!\n");
        return;
    }
    free(pArray);
    pArray = NULL;

    return;
}

VOID daring_test_array()
{
    int data[10] = {1,2,3,4,5,6,7,8,9,10};
    int dataNum = 10;
    int arrayLen = 20;
    int *pArray = NULL;

    printf("\n---Now test array functions(start)---\n");
    pArray = daring_arrayCreate((int *)data, dataNum, arrayLen);
    if(NULL == pArray)
    {
        printf("create array failed!\n");
        return;
    }
    daring_arrayPrint(pArray, dataNum);

    daring_arrayElementInsert(3, 30, pArray, &dataNum);
    daring_arrayElementInsert(11, 100, pArray, &dataNum);
    daring_arrayElementDelete(1, pArray, &dataNum);
    daring_arrayElementDelete(8, pArray, &dataNum);
    daring_arrayPrint(pArray, dataNum);

    daring_arrayDelete(pArray);
    printf("\n---Now test array functions(end)---\n");

    return;
}