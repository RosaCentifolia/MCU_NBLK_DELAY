/*
*FileName:Delay.h
*Description: using to definition Nn-Block Delay Function
*Author: RosaCentifolia
*Version: V1.0
*Fixed record: 
*/

#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>
#include <stdbool.h>
#include "Delay_CONFIG.h"

/*Config Macro*/
#if !defined(DISABLE_8BIT_DELAY_FUNCTION_MODE) && !defined(DISABLE_16BIT_DELAY_FUNCTION_MODE)
#error "Delay_CONFIG.h Setting error. Please define either DISABLE_8BIT_DELAY_FUNCTION_MODE or DISABLE_16BIT_DELAY_FUNCTION_MODE."
/*错误中文翻译：Delay_CONFIG.h 设置错误。请二选一 DISABLE_8BIT_DELAY_FUNCTION_MODE 或 DISABLE_16BIT_DELAY_FUNCTION_MODE。*/
#endif

/*Gobal variable declaration*/
/*
*This variables should be incremented in the 10us timer interrupt service function..
*这个变量应放入10us定时器中断服务函数中自加
*/
#if defined( DISABLE_8BIT_DELAY_FUNCTION_MODE ) && defined( DISABLE_16BIT_DELAY_FUNCTION_MODE )
extern volatile uint32_t g_TIM_Delay_Counter;
#endif
#ifndef  DISABLE_8BIT_DELAY_FUNCTION_MODE
extern volatile uint8_t g_TIM_Delay_Counter;
#endif
#ifndef  DISABLE_16BIT_DELAY_FUNCTION_MODE
extern volatile uint16_t g_TIM_Delay_Counter;
#endif

/*Typedef declaration*/
#if defined( DISABLE_8BIT_DELAY_FUNCTION_MODE ) && defined( DISABLE_16BIT_DELAY_FUNCTION_MODE )
typedef struct {
    uint32_t startValue;
    bool startFlag;
} DelayHandle;
#endif
#ifndef  DISABLE_8BIT_DELAY_FUNCTION_MODE
typedef struct {
    uint8_t  startValue_8bit;
    uint32_t elapsed;
    bool startFlag;
} DelayHandle;
#endif
#ifndef  DISABLE_16BIT_DELAY_FUNCTION_MODE
typedef struct {
    uint16_t  startValue_16bit;
    uint32_t elapsed;
    bool startFlag;
} DelayHandle;
#endif

typedef enum{
    WAITY = 0u,
    READY
}DELAY_REPORT;

/*Function declaration */
#if defined( DISABLE_8BIT_DELAY_FUNCTION_MODE ) && defined( DISABLE_16BIT_DELAY_FUNCTION_MODE )
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue );
void CPUdelay_10us( uint16_t delay_Countdown );
#endif
#ifndef  DISABLE_8BIT_DELAY_FUNCTION_MODE
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue );
void CPUdelay_10us( uint8_t delay_Countdown );
#endif
#ifndef  DISABLE_16BIT_DELAY_FUNCTION_MODE
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue );
void CPUdelay_10us( uint16_t delay_Countdown );
#endif

#endif
