/*==========================================================
//	function:	ADF4530/51 彩屏模块
//	date:		2015/09/18
//	E_Mail:		technicxie@126.com	
==========================================================*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"
#include "ADF4350_V1.h"

extern unsigned char Save_Flag;  //用于保存数据
extern unsigned char Charge_Flag[2];//用于标记寄存器被改变，需要保存
extern unsigned int Save_Time;
extern unsigned char Number_Index;
unsigned char Key_SW_Flag;
unsigned char Register_Index;
unsigned char Key_Return_Flag;

//EventsFunctionList
void OnEditClicked_Ramp_Clk(WM_MESSAGE * pMsg);
void OnEditClicked_Delta_F(WM_MESSAGE * pMsg);
void OnEditClicked_Stop_F(WM_MESSAGE * pMsg);
void OnEditClicked_Start_F(WM_MESSAGE * pMsg);
void OnButtonClicked_Stop_SW(WM_MESSAGE * pMsg);
void OnButtonClicked_Start_SW(WM_MESSAGE * pMsg);
void OnButtonClicked_Ramp_Clk(WM_MESSAGE * pMsg);
void OnButtonClicked_Delta_F(WM_MESSAGE * pMsg);
void OnButtonClicked_Stop_F(WM_MESSAGE * pMsg);
void OnButtonClicked_Start_F(WM_MESSAGE * pMsg);
void OnButtonClicked_RF_OUT(WM_MESSAGE * pMsg);
void OnEditClicked_RF_Out(WM_MESSAGE * pMsg);
//EndofEventsFunctionList

//EventsFunctionList
void OnButtonClicked_Back_Key(WM_MESSAGE * pMsg);
void OnButtonClicked_Enter(WM_MESSAGE * pMsg);
void OnButtonClicked_Symbol(WM_MESSAGE * pMsg);
void OnButtonClicked_C(WM_MESSAGE * pMsg);
void OnButtonClicked_D(WM_MESSAGE * pMsg);
void OnButtonClicked_9(WM_MESSAGE * pMsg);
void OnButtonClicked_8(WM_MESSAGE * pMsg);
void OnButtonClicked_7(WM_MESSAGE * pMsg);
void OnButtonClicked_6(WM_MESSAGE * pMsg);
void OnButtonClicked_5(WM_MESSAGE * pMsg);
void OnButtonClicked_4(WM_MESSAGE * pMsg);
void OnButtonClicked_3(WM_MESSAGE * pMsg);
void OnButtonClicked_2(WM_MESSAGE * pMsg);
void OnButtonClicked_1(WM_MESSAGE * pMsg);
void OnButtonClicked_0(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


#define GUI_ID_BUTTON10   GUI_ID_USER+0
#define GUI_ID_BUTTON11   GUI_ID_USER+1
#define GUI_ID_BUTTON12   GUI_ID_USER+2
#define GUI_ID_BUTTON13   GUI_ID_USER+3
#define GUI_ID_BUTTON14   GUI_ID_USER+4

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "ADF4351_Control_Softwae        Deg By Xie",0,                       0,  0,  320,240,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "Cry Fre",           GUI_ID_TEXT1,            181,24, 46, 16, 0,0},
    { TEXT_CreateIndirect,      "Mhz",               GUI_ID_TEXT2,            269,25, 24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            233,18, 30, 22, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT1,            81, 18, 60, 26, 0,0},
    { BUTTON_CreateIndirect,    "RF_OUT",            GUI_ID_BUTTON0,          9,  18, 66, 26, 0,0},
    { BUTTON_CreateIndirect,    "START_Fre",         GUI_ID_BUTTON1,          9,  77, 66, 26, 0,0},
    { BUTTON_CreateIndirect,    "STOP_Fre",          GUI_ID_BUTTON2,          9,  126,66, 26, 0,0},
    { BUTTON_CreateIndirect,    "Delta_Fre",         GUI_ID_BUTTON3,          161,77, 66, 26, 0,0},
    { BUTTON_CreateIndirect,    "Ramp_Clk",          GUI_ID_BUTTON4,          161,127,66, 26, 0,0},
    { BUTTON_CreateIndirect,    "START_Sweep",       GUI_ID_BUTTON5,          31, 179,91, 26, 0,0},
    { BUTTON_CreateIndirect,    "STOP_Sweep",        GUI_ID_BUTTON6,          192,179,91, 26, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT2,            81, 77, 52, 26, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT3,            81, 126,52, 26, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT4,            233,77, 52, 26, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT5,            233,126,52, 26, 0,0},
    { TEXT_CreateIndirect,      "uS",                GUI_ID_TEXT6,            291,137,16, 16, 0,0},
    { TEXT_CreateIndirect,      "Khz",               GUI_ID_TEXT0,            147,29, 17, 15, 0,0},
    { TEXT_CreateIndirect,      "Mhz",               GUI_ID_TEXT3,            136,87, 19, 16, 0,0},
    { TEXT_CreateIndirect,      "Mhz",               GUI_ID_TEXT5,            135,135,20, 17, 0,0},
    { TEXT_CreateIndirect,      "Khz",               GUI_ID_TEXT4,            289,87, 23, 16, 0,0},
    { TEXT_CreateIndirect,      "min:100K",          GUI_ID_TEXT7,            233,106,50, 12, 0,0},
    { TEXT_CreateIndirect,      "min:100uS",         GUI_ID_TEXT8,            233,154,50, 12, 0,0}
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Key[] = {
    { FRAMEWIN_CreateIndirect,  "Key Board",         0,                       0+63,  0+38,  193,163,FRAMEWIN_CF_MOVEABLE,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            18, 4,  149,30, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON0,          4,  40, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON1,          41, 40, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON2,          78, 40, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON3,          115,40, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON4,          152,40, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON5,          4,  74, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON6,          41, 74, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON7,          78, 74, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON8,          115,74, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON9,          152,74, 31, 28, 0,0},
    { BUTTON_CreateIndirect,    ".",                 GUI_ID_BUTTON10,         4,  108,31, 28, 0,0},
    { BUTTON_CreateIndirect,    "C",                 GUI_ID_BUTTON11,         41, 108,31, 28, 0,0},
    { BUTTON_CreateIndirect,    "+/-",               GUI_ID_BUTTON12,         78, 108,31, 28, 0,0},
    { BUTTON_CreateIndirect,    "Ent",               GUI_ID_BUTTON13,         115,108,31, 28, 0,0},
    { BUTTON_CreateIndirect,    "Bck",               GUI_ID_BUTTON14,         152,108,31, 28, 0,0}
};

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    GUI_SetColor(0x00c000);
    GUI_FillRect(0,58,316,59);

}

void PaintDialog_Key(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetBarColor(hWin,1,0xff80ff);
    FRAMEWIN_SetClientColor(hWin,0xc0ffc0);
    FRAMEWIN_SetTextColor(hWin,0xff0000);
    FRAMEWIN_SetFont(hWin,&GUI_Font16B_ASCII);
    FRAMEWIN_SetTitleHeight(hWin,16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xc0ffc0);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font16B_ASCII);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xc0ffc0);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT0),0,0xe0e0e0);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT0),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT0),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT0),"30");
    //
    //GUI_ID_EDIT1
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT1),0,0xffff00);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT1),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT1),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT1),7);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT1),"200000");
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_Font13B_ASCII);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_Font13B_ASCII);
    //
    //GUI_ID_EDIT2
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT2),0,0xffff00);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT2),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT2),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT2),4);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT2),"100");
    //
    //GUI_ID_EDIT3
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT3),0,0xffff00);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT3),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT3),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT3),4);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT3),"4300");
    //
    //GUI_ID_EDIT4
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT4),0,0xffff00);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT4),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT4),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT4),5);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT4),"100");
    //
    //GUI_ID_EDIT5
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT5),0,0xffff00);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT5),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT5),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT5),6);
    EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT5),"1000");
    //
    //GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xc0ffc0);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0xc0ffc0);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xc0ffc0);
    //
    //GUI_ID_TEXT5
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT5),0xc0ffc0);
    //
    //GUI_ID_TEXT4
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xc0ffc0);
    //
    //GUI_ID_TEXT7
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT7),0xc0ffc0);
    //
    //GUI_ID_TEXT8
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT8),0xc0ffc0);

}

void InitDialog_Key(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0xffff80);
    FRAMEWIN_SetFont(hWin,&GUI_Font16B_ASCII);
    //FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_SetTitleHeight(hWin,16);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_EDIT0),0,0xff80ff);
    EDIT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_EDIT0),0,0xff0000);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT0),&GUI_Font16B_ASCII);
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT0),GUI_TA_VCENTER|GUI_TA_RIGHT);
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT0),7);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON9
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON10
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON10),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON10),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON11
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON11),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON11),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON12
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON12),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON12),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON13
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON13),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON13),&GUI_Font16B_ASCII);
    //
    //GUI_ID_BUTTON14
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON14),BUTTON_CI_UNPRESSED,0x0080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON14),&GUI_Font16B_ASCII);

}


/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Key(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
	WM_HWIN hEdit_Item= WM_GetDialogItem(hWin, GUI_ID_EDIT0);

    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_Key(pMsg);
			Number_Index=0;
			EDIT_SetDecMode(hEdit_Item, 0,   0, 4400000, 0, 0);
            break;
        case WM_INIT_DIALOG:
            InitDialog_Key(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_0(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_1(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_2(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_3(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON4:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_4(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON5:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_5(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON6:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_6(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON7:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_7(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON8:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_8(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON9:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_9(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON10:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_D(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON11:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_C(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON12:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Symbol(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON13:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Enter(pMsg);
							Key_Return_Flag=1;
							GUI_EndDialog(hWin, 0);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON14:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Back_Key(pMsg);
							Key_Return_Flag=1;
							GUI_EndDialog(hWin, 0);
                            break;
                    }
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
		WM_HWIN hDlg;
		WM_HWIN	hEdit0_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT0);
		WM_HWIN	hEdit1_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT1);
		WM_HWIN	hEdit2_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT2);
		WM_HWIN	hEdit3_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT3);
		WM_HWIN	hEdit4_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT4);
		WM_HWIN	hEdit5_Item = WM_GetDialogItem(hWin, GUI_ID_EDIT5);
	
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
				        EDIT_SetDecMode(hEdit1_Item, Register_Buf[6],   100, 4400000, 0, 0);
								EDIT_SetDecMode(hEdit2_Item, Register_Buf[7],   35, 4400, 0, 0);
								EDIT_SetDecMode(hEdit3_Item, Register_Buf[8],   35, 4400, 0, 0);
								EDIT_SetDecMode(hEdit4_Item, Register_Buf[9],   100, 50000, 0, 0);
								EDIT_SetDecMode(hEdit5_Item, Register_Buf[10],   100, 100000, 0, 0);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;  
						if(Key_Return_Flag)	
						{
							Key_Return_Flag=0;
							EDIT_SetValue(hEdit1_Item, Register_Buf[6]);
							EDIT_SetValue(hEdit2_Item, Register_Buf[7]);
							EDIT_SetValue(hEdit3_Item, Register_Buf[8]);
							EDIT_SetValue(hEdit4_Item, Register_Buf[9]);
							EDIT_SetValue(hEdit5_Item, Register_Buf[10]);
							Key_SW_Flag=1;
							Register_Index=0;
						}  
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_EDIT1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_RF_Out(pMsg);
														if(Key_SW_Flag==0)
														{
																Key_SW_Flag=1;
																Register_Index=1;//Freq0
																hDlg = GUI_CreateDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, WM_HBKWIN, 0, 0); 
																WM_MakeModal(hDlg);
																GUI_ExecCreatedDialog(hDlg);
																WM_MakeModal(hWin);
																WM_SetFocus(hWin);
														}
														else
																Key_SW_Flag=0;												
                            break;
                    }
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_RF_OUT(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Start_F(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Stop_F(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Delta_F(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON4:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Ramp_Clk(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON5:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Start_SW(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON6:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Stop_SW(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_EDIT2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_GOT_FOCUS://case WM_NOTIFICATION_CLICKED:
                            OnEditClicked_Start_F(pMsg);
														if(Key_SW_Flag==0)
														{
																Key_SW_Flag=2;
																Register_Index=2;//Freq0
																hDlg = GUI_CreateDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, WM_HBKWIN, 0, 0); 
																WM_MakeModal(hDlg);
																GUI_ExecCreatedDialog(hDlg);
																WM_MakeModal(hWin);
																WM_SetFocus(hWin);
														}
														else
																Key_SW_Flag=0;													
                            break;
                    }
                    break;
                case GUI_ID_EDIT3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_GOT_FOCUS://case WM_NOTIFICATION_CLICKED:
                            OnEditClicked_Stop_F(pMsg);
														if(Key_SW_Flag==0)
														{
																Key_SW_Flag=3;
																Register_Index=3;//Freq0
																hDlg = GUI_CreateDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, WM_HBKWIN, 0, 0); 
																WM_MakeModal(hDlg);
																GUI_ExecCreatedDialog(hDlg);
																WM_MakeModal(hWin);
																WM_SetFocus(hWin);
														}
														else
																Key_SW_Flag=0;													
                            break;
                    }
                    break;
                case GUI_ID_EDIT4:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_GOT_FOCUS://case WM_NOTIFICATION_CLICKED:
                            OnEditClicked_Delta_F(pMsg);
														if(Key_SW_Flag==0)
														{
																Key_SW_Flag=4;
																Register_Index=4;//Freq0
																hDlg = GUI_CreateDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, WM_HBKWIN, 0, 0); 
																WM_MakeModal(hDlg);
																GUI_ExecCreatedDialog(hDlg);
																WM_MakeModal(hWin);
																WM_SetFocus(hWin);
														}
														else
																Key_SW_Flag=0;													
                            break;
                    }
                    break;
                case GUI_ID_EDIT5:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_GOT_FOCUS://case WM_NOTIFICATION_CLICKED:
                            OnEditClicked_Ramp_Clk(pMsg);
														if(Key_SW_Flag==0)
														{
																Key_SW_Flag=5;
																Register_Index=5;//Freq0
																hDlg = GUI_CreateDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, WM_HBKWIN, 0, 0); 
																WM_MakeModal(hDlg);
																GUI_ExecCreatedDialog(hDlg);
																WM_MakeModal(hWin);
																WM_SetFocus(hWin);
														}
														else
																Key_SW_Flag=0;	
                            break;
                    }
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{ 
    GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
	while(1)
	{
        GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
	}
}
