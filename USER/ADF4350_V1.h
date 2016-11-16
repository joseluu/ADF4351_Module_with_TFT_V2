#ifndef __ADF4350_H

#define __ADF4350_H

void WriteToADF4350(unsigned char count, unsigned char *buf);
void ReadFromADF4350(unsigned char count, unsigned char *buf);
void ADF4351_Init(void);
void RF_OUT(void);
extern unsigned long Register_Buf[12];

extern unsigned long Start_Fre_value;
extern unsigned long Stop_Fre_value;
extern double Delta_Fre_value;
extern unsigned long Sweep_Time_value;
extern double Current_Fre;
extern double RF_Fre_Value;

#endif
