/*==========================================================
//	function:	ADF4530/51 彩屏模块
//	date:		2015/09/18
//	E_Mail:		technicxie@126.com	
==========================================================*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "ADF4350_V1.h"

unsigned char Number_Index;
unsigned long Temp_Value;
extern unsigned int Save_Time;  //用于保存数据
extern unsigned char Charge_Flag[2];//用于标记寄存器被改变，需要保存
extern unsigned char Register_Index;
extern unsigned char Key_Return_Flag;



void OnButtonClicked_0(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据OK
	if(temp_value && Number_Index<9)
	{
		temp_value *=10;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_1(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 1;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_2(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 2;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_3(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 3;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_4(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 4;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_5(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 5;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_6(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 6;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_7(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 7;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_8(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 8;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_9(WM_MESSAGE * pMsg)
{
	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	if(Number_Index<9)
	{
		temp_value *=10;
		temp_value += 9;
		Number_Index++;
	}
	EDIT_SetValue(hEdit_Item, temp_value);
}

void OnButtonClicked_D(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_C(WM_MESSAGE * pMsg)
{
	 WM_HWIN hDlg = pMsg->hWin;
	 WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	 Number_Index=0;
	 EDIT_SetValue(hEdit_Item, 0);
}

void OnButtonClicked_Symbol(WM_MESSAGE * pMsg)
{
}

void OnButtonClicked_Enter(WM_MESSAGE * pMsg)
{
 	double temp_value;
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	temp_value = EDIT_GetValue(hEdit_Item);		//得到控件数据
	switch(Register_Index)
	{
		case 1:
			Register_Buf[6] = (unsigned long)temp_value;
			Charge_Flag[0]=1;Save_Time=0;
			break;
		case 2:
			Register_Buf[7] = (unsigned long)temp_value;
			Charge_Flag[0]=1;Save_Time=0;
			break;
		case 3:
			Register_Buf[8] = (unsigned long)temp_value;
			Charge_Flag[0]=1;Save_Time=0;
			break;
		case 4:
			Register_Buf[9] = (unsigned long)temp_value;
			Charge_Flag[0]=1;Save_Time=0;
			break;
		case 5:
			Register_Buf[10] = (unsigned long)temp_value;
			Charge_Flag[0]=1;Save_Time=0;
			break;		
	}

}

void OnButtonClicked_Back_Key(WM_MESSAGE * pMsg)
{
	WM_HWIN hDlg = pMsg->hWin;
	WM_HWIN	hEdit_Item = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	Temp_Value = EDIT_GetValue(hEdit_Item);		
}

