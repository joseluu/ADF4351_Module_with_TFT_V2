/*==========================================================
//	function:	ADF4530/51 彩屏模块
//	date:		2015/09/18
//	E_Mail:		technicxie@126.com	
==========================================================*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "TFT28.h"											
#include "TOUCH.h"											
#include "lcd.h"
#include "LCD_Protected.h"
#include "GUI.h"
#include "DIALOG.h"
#include "ADF4350_V1.h"

void MainTask(void);

unsigned int Device_code=0x9320;           	//TFT控制IC型号ILI9328 0x9328 0x5408 0x1505
unsigned char Time_1S;					
unsigned int System_Count;
unsigned int XV,YV;
unsigned char Save_Flag;  
unsigned char Charge_Flag[2];
unsigned int Save_Time;  
unsigned long Sweep_Time_Counter;
unsigned char Sweep_DIR_Flag;
/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay(unsigned long nCount)
{
  for(; nCount != 0; nCount--);
}

unsigned long Sweep_Time_Counter;
//unsigned long Current_Fre;
unsigned char Sweep_DIR_Flag;

void OnEditClicked_RF_Out(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_RF_OUT(WM_MESSAGE * pMsg)
{
	unsigned long temp=Register_Buf[6],op;
	double n;
	op = temp%100;
  temp -= op;
	n=temp;
	n /= 1000;
	RF_Fre_Value = n;
	RF_OUT();//输出
}

void OnButtonClicked_Start_F(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_Stop_F(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_Delta_F(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_Ramp_Clk(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_Start_SW(WM_MESSAGE * pMsg)
{
			unsigned long temp=Register_Buf[9],op;
			double n;
			op = temp%100;
			temp -= op;
			n=temp;
			n /= 1000;
			Delta_Fre_value=n;
	
	    Start_Fre_value=Register_Buf[7];
			Stop_Fre_value=Register_Buf[8];
			Sweep_Time_value=Register_Buf[10];
	   if(Start_Fre_value<Stop_Fre_value)
	   {
				TIM_Cmd(TIM3, ENABLE);//Start
				Sweep_Time_Counter=0;
				Current_Fre=Start_Fre_value;
				Sweep_DIR_Flag=0;
				RF_Fre_Value = Start_Fre_value;
				RF_OUT();
	   }
	   else
	   {
				TIM_Cmd(TIM3, DISABLE);//Stop
	   }	
}

void OnButtonClicked_Stop_SW(WM_MESSAGE * pMsg)
{
	   TIM_Cmd(TIM3, DISABLE);//Stop	
}

void OnEditClicked_Start_F(WM_MESSAGE * pMsg)
{
}

void OnEditClicked_Stop_F(WM_MESSAGE * pMsg)
{
}

void OnEditClicked_Delta_F(WM_MESSAGE * pMsg)
{
}

void OnEditClicked_Ramp_Clk(WM_MESSAGE * pMsg)
{
}

void System_Init(void)
{
	//初始化硬件模块
	start_7843();                  //打开触摸功能
	ADF4351_Init();

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	Chip_Init();
	System_Init();
	GUI_Init();
	GUI_SetBkColor(GUI_RED);
	GUI_SetColor(GUI_WHITE);
	MainTask();
	
  while (1)
	{
		IWDG_ReloadCounter();	//喂狗WDR();
  }
}
	 
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  	;
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
