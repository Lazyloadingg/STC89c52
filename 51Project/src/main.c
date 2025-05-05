#include <8052.h>
#include <stdio.h>
#include "delay.h"
#include "lcd1602/lcd1602.h"

#define LED0 P2

// 延迟函数
void delay1ms(unsigned int ms);
void nixietubeSingleLight(unsigned char location, unsigned char num);
int main(void)
{

   // flicker();
   // keyboardControl();

   // keyboardProgressive();
   // keyboardSingleLight();
   lcd1602_init();
   lcd1602_show_string(0, 0, "Hello World");
   lcd1602_show_string(0, 1, "-123");

   while (1)
   {
      // int nums[3][2] = {{1, 1}, {2, 2}, {3, 5}};
      // for (size_t i = 0; i < 3; i++)
      // {
      //    nixietubeSingleLight(nums[i][0], nums[i][1]);
      //    /* code */
      // }
      // /* code */
   }

   // nixietubeSingleLight(2, 3);
   return 0;
}

// 数码管函数
void nixietubeSingleLight(unsigned char location, unsigned char num)
{
   int nums[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
   // while (1)
   // {
   //    /* code */
   switch (location)
   {
   case 1:
      P2_4 = 0;
      P2_3 = 0;
      P2_2 = 0;
      break;
   case 2:
      P2_4 = 0;
      P2_3 = 0;
      P2_2 = 1;
      break;
   case 3:
      P2_4 = 0;
      P2_3 = 1;
      P2_2 = 0;
      break;
   case 4:
      P2_4 = 0;
      P2_3 = 1;
      P2_2 = 1;
      break;
   case 5:
      P2_4 = 1;
      P2_3 = 0;
      P2_2 = 0;
      break;
   case 6:
      P2_4 = 1;
      P2_3 = 0;
      P2_2 = 1;
      break;
   case 7:
      P2_4 = 1;
      P2_3 = 1;
      P2_2 = 0;
      break;
   case 8:
      P2_4 = 1;
      P2_3 = 1;
      P2_2 = 1;
      break;

   default:
      break;
   }
   P0 = nums[num];
   delay1ms(1); // 延迟1ms之后清零，消隐
   P2 = 0x00;
}

// 单个led依次亮起

void keyboardSingleLight(void)
{
   unsigned char i = 0;
   while (1)
   {
      if (P3_1 == 0)
      {
         delay1ms(20);
         while (P3_1 == 0)
            ;
         delay1ms(20);
         P2 = ~(1 << i);
         i++;
         if (i >= 8)
         {
            i = 0;
         }
      }
   }
}
// 依次亮灯直至全亮
void keyboardProgressive()
{
   char ctl = 1;
   while (1)
   {
      if (P3_1 == 0)
      {

         delay1ms(20);
         while (P3_1 == 0)
            ;
         delay1ms(20);
         P2 = ~ctl;
         ctl++;
         if (ctl == 255)
         {
            ctl = 0;
         }
      }
   }
}
// 按键控制亮/灭
void keyboardState()
{
   int p2_1 = 0;
   while (1)
   {

      if (P3_1 == 0)
      {
         delay1ms(20);
         while (P3_1 == 0)
            ;
         delay1ms(20);
         P2_0 = p2_1;
         p2_1 = ~p2_1;
      }
   }
}
// 按键按压控制亮灭
void keyboardControl(void)
{
   if (P3_1 == 0)
   {
      P2_1 = 0;
   }
   else
   {
      P2_1 = 1;
   }
}
// 闪烁
void flicker(void)
{
   while (1)
   {
      LED0 = 0b10101010;
      delay1ms(500);
      LED0 = 0b11111111;
      delay1ms(500);
   }
}
// 流水灯函数
void flowLed(void)
{
   int origin = 0b11111111;
   for (size_t i = 0; i < 8; i++)
   {
      LED0 = origin & (~(1 << i));
      delay1ms(500);
      /* code */
   }
}
