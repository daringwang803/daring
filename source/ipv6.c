#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "public.h"
#include "ipv6.h"

/*********************************************************************************
 * function : ipv6地址的累加
 * input    : pAddr    : 待累加的地址，长度是16个字节，主机序，即配置什么便怎样排序
 * input    : maskLen  : 地址掩码长度
 * input    : offSet   : 要累加的个数
 * input    : pNewAddr ：出参，累加后的地址
 * output   : 无
 * comment  :
 * author   : daringwang
 * date     : 2021.6.18
 * *********************************************************************************/
VOID daring_ipv6RangeAdd(BYTE *pAddr, int maskLen, int offSet,  BYTE *pNewAddr)
{
    WORD16 addrTemp[IPV6_ADDR_LEN];    /*pAddr对应的双字节表示*/
    BYTE *pAddrTemp = pAddr;
    int index = 0;
    int key = 0;
    WORD16 byteMax = BYTE_DATA_MAX+1;
    BYTE carryFlag = 0;/*进位标记*/
    BYTE byteNum = 0;  /*从第几个字节开始累加*/
    BYTE addData = 0;   /*初始累加的数值*/
    BYTE remain = maskLen %BYTE_DATA_LEN; /*余数*/
    BYTE intData = maskLen /BYTE_DATA_LEN; /*整除*/

    if(0 == offSet)
    {
        printf("offset can not be 0!\n");
        return;
    }
    else if(1 == offSet)
    {
        memcpy(pNewAddr, pAddr, IPV6_ADDR_LEN);
        return;
    }
    /*byte数据存储到word中*/
    for(index=0; index < IPV6_ADDR_LEN ;index++)
    {
        addrTemp[index]= *pAddrTemp;
        pAddrTemp++;
    }
    /*开始累加的位置是第几个字节，字节的哪个比特位,第一次累计的数值*/
    if(0 == remain)
    {
        addData = 1;
        byteNum = intData - 1;
    }
    else
    {
        addData = 1 << (BYTE_DATA_LEN - remain);
        byteNum = intData;
    }
    /*累加*/
    for(key=0; key < (offSet-1) ;key++)
    {
        /*值累加*/
        addrTemp[byteNum] += addData;
        if(byteMax == addrTemp[byteNum])
        {
            carryFlag = 1;
            addrTemp[byteNum] = 0;/*进位了，该字节值就是0*/
        }
        /*进位处理*/
        for(index= byteNum; index >0 ;index--)
        {
            addrTemp[index-1] += carryFlag;
            carryFlag = 0;/*清零*/
            if(byteMax == addrTemp[index-1])
            {
                carryFlag = 1;
                addrTemp[index-1] = 0;/*进位了，该字节值就是0*/
            }
            
        }
        if(1 == carryFlag)/*最高位进位，溢出*/
        {
            printf("can not add ipv6 data,overflow!\n");
            return;
        }
    }
    /*把累加后的值复制出来*/
    for(index=0;index<IPV6_ADDR_LEN;index++)
    {
        pNewAddr[index] = addrTemp[index];
    }
    return;
}

/**********功能验证函数**************/
VOID daring_test_ipv6RangeAdd()
{
    int index = 0;
    BYTE newAddr[IPV6_ADDR_LEN] = {0};
    int maskLen = 0;
    int offSet = 0;

    printf("\n---Now test function:daring_ipv6RangeAdd(start)---\n");

    /*场景1：掩码为最大值128*/
	BYTE addr1[IPV6_ADDR_LEN] = {0x00,0X00,
                                0xff,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 128;
    offSet = 3;
    printf("scene 1:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr1[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr1, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景2：掩码小于8*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr2[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 6;
    offSet = 3;
    printf("scene 2:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr2[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr2, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景3：掩码能被8整除*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr3[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0Xff,
                                0xf0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 40;
    offSet = 3;
    printf("scene 3:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr3[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr3, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");
    
    /*场景4：掩码不能被8整除*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr4[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0Xff,
                                0xf0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 41;
    offSet = 3;
    printf("scene 4:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr4[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr4, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景5：偏移量为最大值255*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr5[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0Xff,
                                0xf0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 40;
    offSet = 255;
    printf("scene 5:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr5[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr5, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景6：偏移量为0*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr6[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0Xff,
                                0xf0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 41;
    offSet = 0;
    printf("scene 6:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr6[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr6, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景7：偏移量为1*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr7[IPV6_ADDR_LEN] = {0xe0,0X00,
                                0x00,0Xff,
                                0xf0,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 41;
    offSet = 1;
    printf("scene 7:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr7[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr7, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n\n");

    /*场景8：越界*/
    memset(newAddr, 0, IPV6_ADDR_LEN);
	BYTE addr8[IPV6_ADDR_LEN] = {0xff,0Xff,
                                0xff,0Xff,
                                0xfe,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00,
                                0x00,0X00};
	maskLen = 40;
    offSet = 3;
    printf("scene 8:mask length is %u, offset is %u,addr is:\n", maskLen, offSet);
    for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",addr8[index]);
	}
	printf("\n");
    daring_ipv6RangeAdd((BYTE *)addr8, maskLen, offSet, (BYTE *)newAddr);
    printf("After add:\n");
	for(index=0;index< IPV6_ADDR_LEN; index++)
	{
		printf("%02x ",newAddr[index]);
	}
	printf("\n");

    printf("---Now test function:daring_ipv6RangeAdd(end)---\n\n");
    return;
}