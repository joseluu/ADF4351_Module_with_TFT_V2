#ifndef __USER_CONF_H

#define __USER_CONF_H
//*****************************************************************************
#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef schar
#define schar signed char 
#endif

#ifndef uint
#define uint unsigned int 
#endif

#ifndef sint
#define sint signed int 
#endif



/*函数声明区*/
void Chip_Init(void);
void USART1_Putc(unsigned char c);
void USART1_Puts(char * str);

void LCD_DrawPoint(unsigned int x,unsigned int y);
void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);
void LCD_DrawPoint_big(unsigned int x,unsigned int y);
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void GUIsquare2pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour);

void drawpoint(unsigned int x,unsigned int y,unsigned int color); 
void Print_Decimal(unsigned char i,unsigned int buffer);
void Display_Coordinate(int x,unsigned int y,unsigned int color);
void Con_Coordinate(int x,unsigned int y,unsigned int color);
void Drow_Touch_Point(unsigned char x,unsigned int y);			   
void Draw_Big_Point(unsigned char x,unsigned int y);


/*IO定义*/
/*2.8寸TFT触摸屏接口定义*/
#define  RS_CLR	        GPIO_ResetBits(GPIOC, GPIO_Pin_12)   //RS置低
#define  RS_SET	        GPIO_SetBits(GPIOC, GPIO_Pin_12)     //RS置高
#define  RW_CLR	        GPIO_ResetBits(GPIOC, GPIO_Pin_11)   //RW置低
#define  RW_SET	        GPIO_SetBits(GPIOC, GPIO_Pin_11)  	//RW置高
#define  RD_CLR	        GPIO_ResetBits(GPIOC, GPIO_Pin_10)   //E置低
#define  RD_SET	        GPIO_SetBits(GPIOC, GPIO_Pin_10)     //E置高
#define  CS_CLR	        GPIO_ResetBits(GPIOC, GPIO_Pin_8)   //CS置低
#define  CS_SET	        GPIO_SetBits(GPIOC, GPIO_Pin_8)     //CS置高
#define  RST_CLR	    GPIO_ResetBits(GPIOC, GPIO_Pin_6)   //RST置低
#define  RST_SET	    GPIO_SetBits(GPIOC, GPIO_Pin_6)     //RST置高
#define  LE_CLR	        GPIO_ResetBits(GPIOB, GPIO_Pin_14)   //LE置低
#define  LE_SET	        GPIO_SetBits(GPIOB, GPIO_Pin_14)     //LE置高


//TFT触摸屏接口定义
#define PEN             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)    //PC12输入的值
#define TPDOUT          GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)   //PC11输入的值
#define TPBUSY          GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)    //PC12输入的值
#define TPDI_CLR		GPIO_ResetBits(GPIOB, GPIO_Pin_15)    //TPDI置低
#define TPDI_SET		GPIO_SetBits(GPIOB, GPIO_Pin_15)      //TPDI置高
#define TPCS_CLR		GPIO_ResetBits(GPIOC, GPIO_Pin_7)    //TPCS置低
#define TPCS_SET		GPIO_SetBits(GPIOC, GPIO_Pin_7)      //TPCS置高
#define TPCLK_CLR		GPIO_ResetBits(GPIOC, GPIO_Pin_9)    //TPCLK置低
#define TPCLK_SET		GPIO_SetBits(GPIOC, GPIO_Pin_9)      //TPCLK置高

//************************************************************************

#define SET_LE()		GPIO_SetBits(GPIOC, GPIO_Pin_14)
#define CLR_LE()		GPIO_ResetBits(GPIOC, GPIO_Pin_14)

#define	SET_SCL()		GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define	CLR_SCL()		GPIO_ResetBits(GPIOC, GPIO_Pin_0)

#define SET_DATA()		GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define CLR_DATA()		GPIO_ResetBits(GPIOC, GPIO_Pin_15)

#define SET_CE()		GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define CLR_CE()		GPIO_ResetBits(GPIOC, GPIO_Pin_13)
//************************************************************************
#define Key_1()						GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define Key_2()						GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define Key_3()						GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define Key_4()						GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)

#define USB_DISCON_L()				GPIO_ResetBits(GPIOC, GPIO_Pin_5)
#define USB_DISCON_H()	    		GPIO_SetBits(GPIOC, GPIO_Pin_5)
//************************************************************************
#endif

