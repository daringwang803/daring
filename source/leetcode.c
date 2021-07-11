/*
 * @Description: 力扣的练习题
 * @Author: daringwang
 * @Date: 2021-07-10 10:15:37
 * @LastEditTime: 2021-07-10 15:33:07
 * @LastEditors: daringwang
 * @Reference: All rights reserved by Daring Wang.
 */
#include "leetcode.h"

/********************************************
 * 题1：
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

实例1：
输入：nums = [1,1,2]
输出：2, nums = [1,2]
实例2：
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]:

分析：使用双计数（双指针）方法，两个指针都向后偏移，遇到不相等的值，就用后值覆盖前值
*********************************************/
int daring_removeDuplicates(int* nums, int numsSize){

    int left = 0;
    int right = 1;
    if(NULL == nums || numsSize <1)
    {
        return 0;
    }
    if(1 == numsSize)
    {
        return 1;
    }

    while(right < numsSize)
    {
        if(nums[left] != nums[right])//不相等就覆盖
        {
            nums[++left] = nums[right];
            
        }
        else
        right ++;
        
    }

    return left+1;
}

void daring_leetcode1()
{
    int data[3] = {1,1,2};
    int len = 0;

    printf("\n---leetcode 1---\n");

    printf("input:\n");
    daring_arrayPrint(data, 3);
    
    printf("output:\n");
    len = daring_removeDuplicates(data, 3);
    daring_arrayPrint(data, len);

    int data2[10] = {0,0,1,1,1,2,2,3,3,4};
    printf("input:\n");
    daring_arrayPrint(data2, 10);
    
    printf("output:\n");
    len = daring_removeDuplicates(data2, 10);
    daring_arrayPrint(data2, len);

    printf("\n");

    return;
}

/*************************
 * 题2：
 * 给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

实例1：
输入: prices = [7,1,5,3,6,4]
输出: 7

实例2：
输入: prices = [1,2,3,4,5]
输出: 4

实例3：
输入: prices = [7,6,4,3,1]
输出: 0

分析：
只需要把所有股票上涨的时间段内的利润累加就是我们所要求的结果
 * *************************/
int daring_maxProfit(int* prices, int pricesSize){
    int i = 0;
    int num = 0;
    if(NULL == prices || pricesSize <=1)
    {
        return 0;
    }

    while(i< pricesSize-1)
    {
        if(prices[i] < prices[i+1])
        {
            num += (prices[i+1] - prices[i]);
        }
        i++;
    }
    return num;
}
void daring_leetcode2()
{
    int data[6] = {7,1,5,3,6,4};
    int money = 0;

    printf("\n---leetcode 2---\n");

    printf("input:\n");
    daring_arrayPrint(data, 6);
    
    money = daring_maxProfit(data, 6);
    printf("output:money is %u\n", money);

    int data2[5] = {1,2,3,4,5};
    printf("input:\n");
    daring_arrayPrint(data2, 5);
    
    money = daring_maxProfit(data2, 5);
    printf("output:money is %u\n", money);

    int data3[5] = {7,6,4,3,1};
    printf("input:\n");
    daring_arrayPrint(data3, 5);
    
    money = daring_maxProfit(data3, 5);
    printf("output:money is %u\n", money);

    printf("\n");

    return;
}

/**************************
 题3：
 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

 实例1：
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]

 实例2：
输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]

分析：其实就是将max-k个数据从最左边依次丢到最右边
************************/
void daring_rotate(int* nums, int numsSize, int k){
    if(NULL == nums || 0 == numsSize)
    {
        return;
    }
    int step = numsSize - k%numsSize;
    int i = 0;

    int *pData= (int *)malloc(sizeof(int)*numsSize*2);//注意此处的长度要乘以sizeof
    memset(pData, 0, sizeof(int)*numsSize*2);//注意此处的长度要乘以sizeof
    memcpy(pData, nums, sizeof(int)*numsSize);//注意此处的长度要乘以sizeof
    for(i=0;i<numsSize;i++)
    {
        pData[numsSize+i] = pData[i];
        nums[i] = pData[step+i];
    }

    free(pData);
    return;
    
}

void daring_leetcode3()
{
    int data[7] = {1,2,3,4,5,6,7};

    printf("\n---leetcode 3---\n");

    printf("input:\n");
    daring_arrayPrint(data, 7);
    
    printf("output:\n");
    daring_rotate(data, 7, 3);
    daring_arrayPrint(data, 7);

    printf("\n");

    int data2[4] = {-1,-100,3,99};
    printf("input:\n");
    daring_arrayPrint(data2, 4);
    
    printf("output:\n");
    daring_rotate(data2, 4, 2);
    daring_arrayPrint(data2, 4);
    return;
}