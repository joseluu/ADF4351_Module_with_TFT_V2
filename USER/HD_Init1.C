/*==========================================================
//	function:	ADF4530/51 彩屏模块
//	date:		2015/09/18
//	E_Mail:		technicxie@126.com	
//	https://item.taobao.com/item.htm?spm=a230r.1.14.78.WLsG6o&id=522114761979&ns=1&abbucket=18#detail
//  版权声明：版权归纳米电子淘宝店，不得采用我们的资料，在网络上销售相同或者类似模块，违者必究！谢谢配合！
==========================================================*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configure GPIO Pin
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	/*变量定义区*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	//***************************************************************************
	// PA OUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	// PB OUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// PB IN
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PC OUT
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// PC IN
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// PD IN
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART1_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
  /*
  *  USART1_TX -> PA9 , USART1_RX ->	PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

void USART2_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	//使能串口2时钟
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOD | 
            RCC_APB2Periph_AFIO |
            RCC_APB1Periph_USART2 , 
            ENABLE);

	/* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//重映射管脚
	
	// D5 做T2X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // D6 做R2X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART2, &USART_ClockInitStructure);
    USART_Init(USART2, &USART_InitStructure);
    
    USART_Cmd(USART2, ENABLE);
	//串口2使用接收中断
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}

void USART1_Putc(unsigned char c)
{
	USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

void USART1_Puts(char * str)
{
	while(*str)
    {
        USART_SendData(USART1, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures SDIO IRQ channel.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Timer2中断 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Timer3中断 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Timer4中断 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*UART1*/
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	/*UART2*/
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : TIM_Configuration program.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void Tim2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructure.TIM_Period = 100;			//计数值   
  TIM_TimeBaseStructure.TIM_Prescaler = 14400-1;    	//预分频,此值+1为分频的除数
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;  	//
  //TIM_TimeBaseStructure.TIM_Period=2000;		 					/* 自动重装载寄存器周期的值(计数值) */
																	/* 累计 TIM_Period个频率后产生一个更新或者中断 */
  //TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);				    /* 时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1) */
  //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* 采样分频 */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		/* 向上计数模式 */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    /* 清除溢出中断标志 */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2, ENABLE);											/* 开启时钟 */
}

void Tim3_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructure.TIM_Period = 10;			//计数值   
  TIM_TimeBaseStructure.TIM_Prescaler = 720-1;    	//预分频,此值+1为分频的除数
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;  	//
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		/* 向上计数模式 */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    /* 清除溢出中断标志 */
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  //TIM_Cmd(TIM3, ENABLE);											/* 开启时钟 */
   TIM_Cmd(TIM3, DISABLE);
}

void Tim4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* TIM4 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* 基础设置*/
	TIM_TimeBaseStructure.TIM_Period = 1000;			//计数值   
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;    	//预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;  	//
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*使能预装载*/
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	/*预先清除所有中断位*/ 
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
	/* 溢出都配置中断*/
	TIM_ITConfig(TIM4,TIM_IT_Update, ENABLE);
	
	/* 允许TIM4开始计数 */
	TIM_Cmd(TIM4, ENABLE);
}

void  Chip_Init(void)
{
	//初始化时钟源
	//RCC_Configuration();
	
	//初始化GPIO
	GPIO_Configuration();

	//初始化tim1的PWM
	Tim2_Configuration(); 
	Tim3_Configuration(); 
	Tim4_Configuration();
	//初始化IIC
	//I2C_Configuration();

    //初始化UART
	//USART1_Configuration();

	//初始化NVIC
	NVIC_Configuration();
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
