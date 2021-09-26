/************************************************************************************
*                                                                                   *
*   File Name   : sw_compile_date.h                                                 *
*   Version     : 1.00                                                              *
*   Author      : Huan Hoang                                                        *
*   note        :                                                                   *
*                                                                                   *
************************************************************************************/

#ifndef SW_COMPILE_DATE_H
	#define SW_COMPILE_DATE_H
struct RTC_Struct{
	unsigned char Sec;
	unsigned char Min;
	unsigned char Hour;
	unsigned char Date;
	unsigned char Month;
	unsigned char Year;
};

extern struct RTC_Struct CompileDateCode;

/*Read and all data from ROM for compile date code.*/
void GetCompileDate(struct RTC_Struct *ptr);
/*	This function returns with index of bit "mask".*/
unsigned char NumberIndex(unsigned short mask);

#endif	/* SW_COMPILE_DATE_H */


