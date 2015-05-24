//-----------------------------------------------------------------------------
// S1D15705 LCD Controller library
// author  : Radoslaw Kwiecien
// website : http://en.radzio.dxp.pl/s1d15705/
// email   : radek(at)dxp.pl
//-----------------------------------------------------------------------------
#include <avr/io.h>
#include <util/delay.h>
#include "font5x8.h"
#include "S1D15705.h"
//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
#define S1D15705_DATAPORT		PORTA
#define S1D15705_DATAPORT_DIR 	DDRA
#define S1D15705_DATAPIN		PINA

#define S1D15705_CTRLPORT		PORTB
#define S1D15705_CTRLPORT_DIR	DDRB

#define S1D15705_RD				PB0
#define S1D15705_WR				PB1
#define S1D15705_A0				PB2
#define S1D15705_RES			PB3
#define S1D15705_CS				PB4
//-----------------------------------------------------------------------------
// Function for read display status
//-----------------------------------------------------------------------------
unsigned char GLCD_ReadStatus(void)
{
unsigned char tmp;

S1D15705_CTRLPORT &= ~(1 << S1D15705_CS);
S1D15705_CTRLPORT &= ~(1 << S1D15705_A0);
S1D15705_DATAPORT_DIR = 0x00;
S1D15705_CTRLPORT &= ~(1 << S1D15705_RD);
tmp = PINA;
S1D15705_CTRLPORT |= (1 << S1D15705_RD);
S1D15705_DATAPORT_DIR = 0xFF;
S1D15705_CTRLPORT |= (1 << S1D15705_CS);
return tmp;
}
//-----------------------------------------------------------------------------
// Function for write command
//-----------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char CommandToWrite)
{
//while(GLCD_ReadStatus() & 0x80);
S1D15705_CTRLPORT &= ~(1 << S1D15705_CS);
S1D15705_CTRLPORT &= ~(1 << S1D15705_A0);
S1D15705_DATAPORT = CommandToWrite;
S1D15705_CTRLPORT &= ~(1 << S1D15705_WR);
asm("nop");asm("nop");asm("nop");asm("nop");
S1D15705_CTRLPORT |= (1 << S1D15705_WR);
S1D15705_CTRLPORT |= (1 << S1D15705_CS);
}
//-----------------------------------------------------------------------------
// Function for write data
//-----------------------------------------------------------------------------
void GLCD_WriteData(unsigned char DataToWrite)
{
//while(GLCD_ReadStatus() & 0x80);
S1D15705_CTRLPORT &= ~(1 << S1D15705_CS);
S1D15705_CTRLPORT |= (1 << S1D15705_A0);
S1D15705_DATAPORT = DataToWrite;
S1D15705_CTRLPORT &= ~(1 << S1D15705_WR);
asm("nop");asm("nop");asm("nop");asm("nop");
S1D15705_CTRLPORT |= (1 << S1D15705_WR);
S1D15705_CTRLPORT |= (1 << S1D15705_CS);
}
//-----------------------------------------------------------------------------
// FUnction for read data
//-----------------------------------------------------------------------------
unsigned char GLCD_ReadData(void)
{
unsigned char tmp;
S1D15705_CTRLPORT &= ~(1 << S1D15705_CS);
S1D15705_CTRLPORT |= (1 << S1D15705_A0);
S1D15705_DATAPORT_DIR = 0x00;
S1D15705_CTRLPORT &= ~(1 << S1D15705_RD);
asm("nop");asm("nop");
S1D15705_CTRLPORT |= (1 << S1D15705_RD);
asm("nop");asm("nop");
S1D15705_CTRLPORT &= ~(1 << S1D15705_RD);
asm("nop");asm("nop");
tmp = PINA;
S1D15705_CTRLPORT |= (1 << S1D15705_RD);
S1D15705_CTRLPORT |= (1 << S1D15705_CS);
S1D15705_DATAPORT_DIR = 0xFF;
return tmp;
}
//-----------------------------------------------------------------------------
// Function for setting pixel
//-----------------------------------------------------------------------------
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color)
{
unsigned char tmp;
GLCD_GoTo((unsigned char)x, (unsigned char)(y/8));
tmp = GLCD_ReadData();
if(color)
	tmp |= (1 << (y%8));
else
	tmp &= ~(1 << (y%8));
GLCD_GoTo(x, y/8);
GLCD_WriteData(tmp);
}
//-----------------------------------------------------------------------------
// Function for display initializaton
//-----------------------------------------------------------------------------
void GLCD_Initialize(void)
{

S1D15705_CTRLPORT_DIR = 0xff;
S1D15705_DATAPORT_DIR = 0xff;

S1D15705_CTRLPORT &= ~(1 << S1D15705_RES);
//_delay_ms(150);
S1D15705_CTRLPORT |= (1 << S1D15705_RES);

GLCD_WriteCommand(S1D15705_OSCON);
//_delay_ms(50);
GLCD_WriteCommand(S1D15705_LCDBIASSET | 0);
GLCD_WriteCommand(S1D15705_ADCSELECT);
GLCD_WriteCommand(S1D15705_COMMONSTATE  | 0x08);

GLCD_WriteCommand(S1D15705_V5ADJ | 5);

GLCD_WriteCommand(S1D15705_ELECTRONICCTRL);
GLCD_WriteCommand(42);

GLCD_WriteCommand(S1D15705_POWERCTRL | 1);
//_delay_ms(50);
GLCD_WriteCommand(S1D15705_POWERCTRL | 3);
//_delay_ms(50);
GLCD_WriteCommand(S1D15705_POWERCTRL | 7);
//_delay_ms(50);
GLCD_WriteCommand(S1D15705_DISPONOFF | DISP_ON);

GLCD_WriteCommand(S1D15705_DISPLAYSTARTLINE);
GLCD_WriteCommand(S1D15705_DISPLAYNORMAL | 1);

}
//-----------------------------------------------------------------------------
// Function for clear display memory
//-----------------------------------------------------------------------------
void GLCD_Clear(void)
{
int x, y;

for(y = 0; y < 9; y++)
{
GLCD_GoTo(0, y);
for(x = 0; x < 164; x++)
  {
  GLCD_WriteData(0x00);
  _delay_us(10);
  }
}
}
//-----------------------------------------------------------------------------
// Function for set display coordinates
//-----------------------------------------------------------------------------
void GLCD_GoTo(unsigned char x, unsigned char y)
{
x += 3;
GLCD_WriteCommand(S1D15705_PAGEADDRESSSET | y);
GLCD_WriteCommand(S1D15705_COLUMNADDRESSSET | ((x >> 4) & 0x0F));
GLCD_WriteCommand(x & 0x0F);
}
//-----------------------------------------------------------------------------
// Function for write character to display memory
//-----------------------------------------------------------------------------
void GLCD_WriteChar(char x)
{
char i; 
x -= 32; 
for(i = 0; i < 5; i++) 
  GLCD_WriteData(pgm_read_byte(font5x8 + (5 * x) + i)); 
GLCD_WriteData(0x00); 
}
//-----------------------------------------------------------------------------
// Function for write string to display memory
//-----------------------------------------------------------------------------
void GLCD_WriteString(char * s)
{
while(*s)
  {
  GLCD_WriteChar(*s++);
  }
}
//-----------------------------------------------------------------------------
// Function for wirte string at specified coordinates
//-----------------------------------------------------------------------------
void GLCD_WriteStringXY(unsigned char x, unsigned char y, char * str)
{
GLCD_GoTo(x,y);
GLCD_WriteString(str);
}
//-----------------------------------------------------------------------------
// End of file
//-----------------------------------------------------------------------------




