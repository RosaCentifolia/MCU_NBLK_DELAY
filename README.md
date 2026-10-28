一种用于MCU裸机运行的非阻塞式延时方法，配套阻塞式延时方法。

A non-blocking delay method for bare-metal MCU operation, along with a companion blocking delay method.

注意，运行可靠的前提是已经配置好一个定时器中断，并将g_TIM_Delay_Counter放入该定时器中断的中断回调函数中进行自加。（若要实现10us的节拍，则指10us的定时器中断）

Note that reliable operation requires that a timer interrupt has already been configured, and that g_TIM_Delay_Counter is incremented in the interrupt callback function of that timer interrupt. (To achieve a 10 µs tick, this refers to a 10 µs timer interrupt.)

  使用示例：
  
  Usage example: 

    void TIM_10us_IRQHandler(void){
      g_TIM_Delay_Counter++;
    }

非阻塞式的非阻塞式延时方法：DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue )

Non-blocking delay method: DELAY_REPORT NBLK_Delay_10us( DelayHandle *handle, uint32_t delayValue )

  使用示例：编写一个每500ms翻转状态的LED任务函数。
  
  Usage example: Write an LED task function that toggles its state every 500 ms.
  
    static DelayHandle LED_Task_Handle;  

    void LED_Task(void) {
      if ( NBLK_Delay_10us(&ledHandle, 50000) == READY) {  // 500ms=500*100*(10us)=50000
          LED_Toggle();
          // 下一次调用会自动重新启动
          //
      }
      
  注意，示例中的全局变量的静态变量自动初始化为 {0, false}。若使用局部变量，必须显式初始化DelayHandle local_handle = {0, false};
  
  Note that the global/static variables in the example are automatically initialized to {0, false}. If you use a local variable, you must explicitly initialize it: DelayHandle local_handle = {0, false};

阻塞式延时方法：void CPUdelay_10us( uint16_t delay_Countdown )

Blocking delay method: void CPUdelay_10us( uint16_t delay_Countdown )

默认32位模式，若需要使用8位模式或者16位模式，请在Delay_CONFIG.h中选择性注释宏定义DISABLE_8BIT_DELAY_FUNCTION_MODE或者DISABLE_16BIT_DELAY_FUNCTION_MODE。但请注意，不要同时注释两个宏，否则将引发错误。

The default is 32-bit mode. If you need to use 8-bit mode or 16-bit mode, selectively comment out the macro definition DISABLE_8BIT_DELAY_FUNCTION_MODE or DISABLE_16BIT_DELAY_FUNCTION_MODE in Delay_CONFIG.h. However, note that you must not comment out both macros at the same time; otherwise, an error will occur.
