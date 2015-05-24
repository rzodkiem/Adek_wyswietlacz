//-----------------------------------------------------------------------------
// S1D15705 LCD Controller library
// author  : Radoslaw Kwiecien
// website : http://en.radzio.dxp.pl/s1d15705/
// email   : radek(at)dxp.pl
//-----------------------------------------------------------------------------



#ifndef S1D15705_H
#define S1D15705_H

#define S1D15705_DISPONOFF			0xAE
	#define DISP_ON					1
	#define DISP_OFF				0
#define S1D15705_DISPLAYSTARTLINE	0x40
#define S1D15705_PAGEADDRESSSET		0xB0
#define S1D15705_COLUMNADDRESSSET	0x10
#define S1D15705_ADCSELECT			0xA0
#define S1D15705_DISPLAYNORMAL		0xA6
#define S1D15705_DISPLAYALL			0xA4
	#define DISP_ALL				1
	#define DISP_NORMAL				0
#define S1D15705_LCDBIASSET			0xA2
	#define BIAS7					1
	#define BIAS9					0
	
#define S1D15705_COMMONSTATE		0xC0
#define S1D15705_POWERCTRL			0x28
	#define	BOOSTON					0x04
	#define BOOSTOFF				0
	
	#define VADJON					0x02
	#define VADJOFF					0
	
	#define VFON					0x01
	#define VFOFF					0
	
#define	S1D15705_V5ADJ				0x20
#define S1D15705_ELECTRONICCTRL		0x81
#define S1D15705_OSCON				0xAB
#endif


unsigned char GLCD_ReadStatus(void);
void GLCD_WriteCommand(unsigned char CommandToWrite);
void GLCD_WriteData(unsigned char DataToWrite);
unsigned char GLCD_ReadData(void);
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);
void GLCD_Initialize(void);
void GLCD_Clear(void);
void GLCD_GoTo(unsigned char x, unsigned char y);
void GLCD_WriteChar(char x);
void GLCD_WriteString(char * s);
void GLCD_WriteStringXY(unsigned char x, unsigned char y, char * str);

//-----------------------------------------------------------------------------
// End of file
//-----------------------------------------------------------------------------
