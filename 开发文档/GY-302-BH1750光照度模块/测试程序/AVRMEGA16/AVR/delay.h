/*-----------------------------------------------------------------------
延时函数
编译器：ICC-AVR7.14
目标芯片 : M16
时钟: 11.0592Mhz
-----------------------------------------------------------------------*/
#ifndef __delay_h
#define __delay_h
void delay_nus(unsigned int n);
void delay_nms(unsigned int n);
void delay_1us(void);
void delay_1ms(void) ; 

void delay_1us(void)                 //1us延时函数
  {
   asm("nop");
  }

void delay_nus(unsigned int n)       //N us延时函数
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1us();
  }
  
void delay_1ms(void)                 //1ms延时函数
  {
   unsigned int i;
   for (i=0;i<1500;i++);
  }
  
void delay_nms(unsigned int n)       //N ms延时函数
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }
  
  #endif
  