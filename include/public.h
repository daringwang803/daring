/*
 * @Description: PUBLIC_H
 * @Author: daringwang
 * @Date: 2021-07-07 20:53:58
 * @LastEditTime: 2021-07-10 10:29:40
 * @LastEditors: daringwang
 * @Reference: All rights reserved by Daring Wang.
 */
#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

/********************
****宏、结构体定义****
********************/
typedef unsigned char      CHAR;
typedef unsigned char      BYTE;
typedef unsigned short int WORD16;
typedef unsigned int       WORD32;
typedef unsigned long int  WORD64;
typedef void               VOID;
//typedef true               TRUE;
//typedef false              FALSE;
typedef bool               BOOLEAN;

#define BYTE_DATA_LEN   8
#define WORD16_DATA_LEN 16
#define WORD32_DATA_LEN 32
#define BYTE_DATA_MAX   255
#define WORD16_DATA_MAX 65535
#define WORD32_DATA_MAX 4294967295

#define DARING_CHECK_INPUT_OUTPUT(_in_, _retdata_) do{\
    if(NULL == (_in_))\
    {\
        return _retdata_;\
    }\
}while(0);

#define DARING_CHECK_INPUT_NO_OUTPUT(_in_) do{\
    if(NULL == (_in_))\
    {\
        return;\
    }\
}while(0);

#endif