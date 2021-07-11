/*
 * @Description: 
 * @Author: daringwang
 * @Date: 2021-07-10 08:14:07
 * @LastEditTime: 2021-07-11 11:01:57
 * @LastEditors: daringwang
 * @Reference: All rights reserved by Daring Wang.
 */
#ifndef _IPV6_H_
#define _IPV6_H_
#include "public.h"

/********************
****宏、结构体定义****
********************/
#define IPV6_ADDR_LEN  16
#define IPV4_ADDR_LEN  4



/********************
*****函数声明********
********************/
VOID daring_ipv6RangeAdd(BYTE *pAddr, int maskLen, int offSet,  BYTE *pNewAddr);
VOID daring_test_ipv6RangeAdd();

#endif
