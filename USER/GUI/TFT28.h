#ifndef __LCD_H

#define __LCD_H

/*全局变量-颜色代码*/
#define White          0xFFFF           					//显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define WHITE          0xFFFF           					//显示颜色代码
#define BLACK          0x0000
#define BLUE           0x001F
#define BLUE2          0x051F
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0

void TFT_Initial(void);
void Write_Cmd_Data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void Write_Data_U16(unsigned int y);
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void CLR_Screen(unsigned int bColor);
void LCD_SetPoint(unsigned int x, unsigned int y,unsigned int bColor);
unsigned int LCD_Read_Point(unsigned int x, unsigned int y);
void LCD_Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int bColor);	
void LCD_Fill(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int bColor);
void  LCD_Test(void);

#endif
