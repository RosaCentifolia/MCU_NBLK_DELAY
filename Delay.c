/*
*FileName:Delay.c
*Description: using to definition Nn-Block Delay Function
*Author: RosaCentifolia
*Version: V1.0
*Fixed record: 
*/
#include "Delay.h"

/*Gobal variable declaration*/
/*
*This variables should be incremented in the 10us timer interrupt service function.
*这个变量应放入10us定时器中断服务函数中自加
*/
#if defined( DISABLE_8BIT_DELAY_FUNCTION_MODE ) && defined( DISABLE_16BIT_DELAY_FUNCTION_MODE )
volatile uint32_t g_TIM_Delay_Counter=0;
#endif
#ifndef  DISABLE_8BIT_DELAY_FUNCTION_MODE
volatile uint8_t g_TIM_Delay_Counter=0;
#endif
#ifndef  DISABLE_16BIT_DELAY_FUNCTION_MODE
volatile uint16_t g_TIM_Delay_Counter=0;
#endif

#if defined( DISABLE_8BIT_DELAY_FUNCTION_MODE ) && defined( DISABLE_16BIT_DELAY_FUNCTION_MODE )
/*
*Function: NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue )
*Value: *handle, delayValue
*description: Delay 10 us by Un-Block function and TIM server
*Return: DELAY_REPORT: WAITY
                       READY
*Error:
*Author: RosaCentifolia

*使用示例：
*Usage example
*
  //全局变量：静态变量自动初始化为 {0, false}
    Global variables: static variables are automatically initialized to {0, false}
  //注意，在局部变量中，必须显式初始化
    Note that local variables must be explicitly initialized.
  //For example：some_function(void) {
  //             DelayHandle local_handle = {0, false};
  //             }
  //
  
  static DelayHandle LED_Task_Handle;  

  void LED_Task(void) {
      if ( NBLK_Delay_10us(&ledHandle, 50000) == READY) {  // 500ms=500*100*(10us)=50000
          LED_Toggle();
          // 下一次调用会自动重新启动
      }
  }

*/
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue ){
    // 延迟为0时直接退出，不涉及状态
    // Exit immediately when the delay is 0, without involving the state.
    if( delayValue==0 ){
        return READY;
    }else{
        if (!handle->startFlag) {
            // 第一次调用：启动延时，记录开始时间
            // First call: start delay, record start time
            handle->startValue = g_TIM_Delay_Counter;
            handle->startFlag = true;
            return WAITY;
        } else {
            // 已启动延时：检查是否达到延时
            // Delay started: Check if the delay has been reached
            if ( (g_TIM_Delay_Counter - handle->startValue) >= delayValue) {
                // 延时完成，重置
                // Delay complete, reset for the next start
                handle->startFlag = false;
                return READY;
            } else {
                return WAITY;
            }
        }
    }
}

/*
*Function: CPUdelay_10us( uint16_t delay_Countdown )
*Value: 
*description: Delay 10*n us by Blocked Function
              Override __WEAK void CPUdelay_10us( uint16_t delay_Countdown )
              definition in "GPIO_IIC.c"
*Return: DELAY_REPORT: 
*Error:
*Author: RosaCentifolia
*/
void CPUdelay_10us( uint16_t delay_Countdown ){
    uint32_t vauleStartCounter = g_TIM_Delay_Counter;
    while ( (g_TIM_Delay_Counter - vauleStartCounter)<delay_Countdown );
}

#endif

#ifndef  DISABLE_8BIT_DELAY_FUNCTION_MODE
#warning  "8bit delay function is enabled, must be ensured that any foreground program uses less than 2.55 ms"
/*警告中文翻译：8位延时函数已启用，必须确保任何前台程序使用的时间少于 2.55 毫秒*/
/*
*Function: NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue )
*Value: *handle, delayValue
*description: Delay 10 us by Un-Block function and TIM server, 8bit counter version
*Return: DELAY_REPORT: WAITY
                       READY
*Error: Un-test
*Author: RosaCentifolia

*使用示例：
*Usage example
*
  //全局变量：静态变量自动初始化为 {0, false}
    Global variables: static variables are automatically initialized to {0, false}
  //注意，在局部变量中，必须显式初始化
    Note that local variables must be explicitly initialized.
  //For example：some_function(void) {
  //             DelayHandle local_handle = {0,0,0, false};
  //             }
  //
  
  static DelayHandle LED_Task_Handle;  

  void LED_Task(void) {
      if ( NBLK_Delay_10us(&ledHandle_8bit, 50000) == READY) {  // 500ms=500*100*(10us)=50000
          LED_Toggle();
          // 下一次调用会自动重新启动
      }
  }
*注意事项：必须确保任意前台程序占用小于2.55ms
*Precautions: It must be ensured that any foreground program uses less than 2.55 ms
*/
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue ){
    
    uint8_t  difference_8bit;
    
    // 延迟为0时直接退出，不涉及状态
    // Exit immediately when the delay is 0, without involving the state.
    if( delayValue==0 ){
        return READY;
    }else{
        if ( !handle->startFlag ) {
            handle->startValue_8bit = g_TIM_Delay_Counter;
            handle->elapsed = 0;
            handle->startFlag = true;
            return WAITY;
        }else{
            difference_8bit = g_TIM_Delay_Counter - handle->startValue_8bit;
            handle->elapsed += difference_8bit;
            handle->startValue_8bit = g_TIM_Delay_Counter;
            if( handle->elapsed >= delayValue ){
                handle->startFlag = false;
                return READY;
            }else{
                return WAITY;
            }
        }
    }

}

/*
*Function: CPUdelay_10us( uint8_t delay_Countdown )
*Value: 
*description: Delay 10*n us by Blocked Function ( n<255 )
*Return: 
*Error: Un-test
*Author: RosaCentifolia
*/
void CPUdelay_10us( uint8_t delay_Countdown ){
    uint8_t valueStartCounter = g_TIM_Delay_Counter;
    while ( (g_TIM_Delay_Counter - valueStartCounter)<delay_Countdown );
}

#endif

#ifndef  DISABLE_16BIT_DELAY_FUNCTION_MODE
#warning  "16bit delay function is enabled, must be ensured that any foreground program uses less than 655.35 ms"
/*警告中文翻译：16位延时函数已启用，必须确保任何前台程序使用的时间少于 655.35 ms 毫秒*/

/*
*Function: NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue )
*Value: *handle, delayValue
*description: Delay 10 us by Un-Block function and TIM server, 16bit counter version
*Return: DELAY_REPORT: WAITY
                       READY
*Error: Un-test
*Author: RosaCentifolia
*注意事项：必须确保任意前台程序占用小于655.35 ms
*Precautions: It must be ensured that any foreground program uses less than 655.35 ms
*/
DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue ){
    
    uint16_t  difference_16bit;

    // 延迟为0时直接退出，不涉及状态
    // Exit immediately when the delay is 0, without involving the state.
    if( delayValue==0 ){
        return READY;
    }else{
        if ( !handle->startFlag ) {
            handle->startValue_16bit = g_TIM_Delay_Counter;
            handle->elapsed = 0;
            handle->startFlag = true;
            return WAITY;
        }else{
            difference_16bit = g_TIM_Delay_Counter - handle->startValue_16bit;
            handle->elapsed += difference_16bit;
            handle->startValue_16bit = g_TIM_Delay_Counter;
            if( handle->elapsed >= delayValue ){
                handle->startFlag = false;
                return READY;
            }else{
                return WAITY;
            }
        }
    }

}


/*
*Function: CPUdelay_10us( uint16_t delay_Countdown )
*Value: 
*description: Delay 10*n us by Blocked Function ( n<65535 )
*Return: 
*Error: Un-test
*Author: RosaCentifolia
*/
void CPUdelay_10us( uint16_t delay_Countdown ){
    uint16_t valueStartCounter = g_TIM_Delay_Counter;
    while ( (g_TIM_Delay_Counter - valueStartCounter )<delay_Countdown );
}
#endif
