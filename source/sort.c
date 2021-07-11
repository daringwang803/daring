/*
 * @Description: SORT_C
 * @Author: daringwang
 * @Date: 2021-07-07 21:05:51
 * @LastEditTime: 2021-07-10 08:27:57
 * @LastEditors: daringwang
 * @Reference: All rights reserved by Daring Wang.
 */

#include "sort.h"

/**
 * @description: 冒泡排序
 * @param {ptr :数据指针
 *         dataLen ：数据个数}
 * @return {*}
 */
VOID daring_sort_bubble(int *ptr, int dataLen)
{
    int index = 0;
    int index2 = 0;
    int sortBorder = dataLen-1;/*该下标之后的数据都是有序的*/
    int sortedIndex = 0;
    int temp = 0;
    BYTE isSorted = false;

    DARING_CHECK_INPUT_NO_OUTPUT(ptr);
    for(index2 =0;index2< dataLen-1; index2++)
    {
        isSorted = true; /*本轮已经是有序的了*/
        for(index =0;index< sortBorder; index++)
        {
            if(ptr[index]> ptr[index+1])
            {
                temp = ptr[index];
                ptr[index] = ptr[index+1];
                ptr[index+1] = temp;
                sortedIndex = index;
                isSorted = false;
            }
        }
        sortBorder = sortedIndex;

        if(isSorted)
        {
            break;
        }
    } 

    return;   
}

VOID daring_test_sort_bubble()
{
    int data[8] = {3,4,2,1,5,6,7,8};

    printf("\n---Now test bubble sort functions(start)---\n");

    printf("bubble sort before:\n");
    daring_arrayPrint(data, 8);
    
    printf("bubble sort after:\n");
    daring_sort_bubble(data, 8);
    daring_arrayPrint(data, 8);
    printf("\n---Now test bubble sort functions(end)---\n");

    return;

}

/**
 * @description: 快速排序
 * @param  {*}
 * @return {*}
 */
VOID daring_sort_quick(int *ptr, int low , int high)
{
    DARING_CHECK_INPUT_NO_OUTPUT(ptr);

    int key = ptr[0];  /*第一个数据作为key*/
    int minIndex = 0;
    int maxIndex = high;
    if(low >= high)
    {
        //printf("input data error(low=%u,high=%u),or need not sort!\n",low,high);
        return;
    }

    while(low < high)
    {
        while(low< high && ptr[high]>= key)/*找到比key小的high节点*/
        {
            high --;//向前寻找
        }
        ptr[low] = ptr[high];//使用这种覆盖而非交换的方式，一定要先向前寻找

        while(low< high && ptr[low]<= key)/*找到比key大的low节点*/
        {
            low ++;//向后寻找
        }
        ptr[high] = ptr[low];
 
    }
    //printf("now low is %u,high is %u\n",low, high);
    
    daring_sort_quick(ptr, minIndex, low-1);
    daring_sort_quick(ptr, low+1, maxIndex);
    return;

}

VOID daring_test_sort_quick()
{
    int data[8] = {3,4,2,1,5,6,7,8};

    printf("\n---Now test quick sort functions(start)---\n");

    printf("quick sort before:\n");
    daring_arrayPrint(data, 8);
    
    printf("quick sort after:\n");
    daring_sort_quick(data, 0, 7);
    daring_arrayPrint(data, 8);
    printf("\n---Now test quick sort functions(end)---\n");

    return;

}