
/*DOC Encode Type: UTF-8*/
/*
*FileName:Delay_CONFIG.h
*Description: Initialization settings for configuring Nn-Block Delay Function
*用途：初始化设置非阻塞delay函数
*Author: RosaCentifolia 
*Version: V1.0
*Fixed record: 
*/

#ifndef __DELAY_CONFIG_H
#define __DELAY_CONFIG_H

/*
*Before use, g_TIM_Delay_Counter needs to be incremented within the 10us timer interrupt service function.
*使用前需要将 g_TIM_Delay_Counter 放入10us定时器中断服务函数中自加
*/


/*Configuration start
**配置开始
**Preset 2 #define, 1 or more Timer Interrupt Service headfile
**预先设置2个#define，一个或多个定时器中断服务头文件
*/

/*
*如果需要使用8bit、16bit版本，请注释这条宏
*If you need to use the 8-bit/16-bit version, please comment out this macro
*#define  DISABLE_8BIT_DELAY_FUNCTION_MODE
*#define  DISABLE_16BIT_DELAY_FUNCTION_MODE
*注意事项：只能同时选择其中一个进行注释，否则将出现严重错误
*Note: Only one of them can be selected for comment at the same time, 
 otherwise serious errors will occur.
*/
#define  DISABLE_8BIT_DELAY_FUNCTION_MODE
#define  DISABLE_16BIT_DELAY_FUNCTION_MODE


/*Include Timer Interrupt Service headfile
**包含定时器中断服务的头文件*/
#include "main.h"  



/*User Config */



#endif
