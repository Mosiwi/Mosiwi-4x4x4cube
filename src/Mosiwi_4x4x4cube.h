/*  FILE:    Mosiwi_4x4x4cube.h
	DATE:    29/05/23
	VERSION: 0.1
	AUTHOR:  Mosiwi
*/
#ifndef Mosiwi_h
#define Mosiwi_4x4x4cube_h
#include "Arduino.h"

/***************SPI***************
Connections (for an Arduino Uno)
cube ------- UNO
DIN  ------- 11/MOSI
SH_C ------- 13/SCK
ST_C ------- option/CS
VCC  ------- 5V
GND  ------- GND
*********************************/

/*************software************
Connections (for an Arduino Uno)
cube ------- UNO
DIN  ------- option
SH_C ------- option
ST_C ------- option
VCC  ------- 5V
GND  ------- GND
*********************************/

/*Pin definition of UNO

#define PIN_0_7_DDR DDRD   	    //0bxxxxxxxx; input mode: x = 0, output mode: x = 1
#define PIN_0_7_PORT PORTD	 	//0bxxxxxxxx; input mode -> x = 1 or 0;  output mode -> output 1: x = 1, output 0: x = 0; 

#define PIN_8_13_DDR DDRB
#define PIN_8_13_PORT PORTB

#define PIN_14_19_DDR DDRC
#define PIN_14_19_PORT PORTC 	//pin A0--A5
*/

// The parameters of a cube
#define LAYER1 0xFE
#define LAYER2 0xFD
#define LAYER3 0xFB
#define LAYER4 0xF7
#define LAYER  4

// Structure to contain pattern info for the predefined LED patterns
struct _Pattern_info { 
   unsigned char AnimationLength; 
   const unsigned int *PatternArray; 
}; 

// Cube parameters
struct { 
	unsigned char mode = 0;
	unsigned char num = 0;
	unsigned int layers = 0;
	unsigned int *buffer = NULL;
	unsigned int buffer_index = 0;
	unsigned char LastLayer = LAYER1;
}cube; 


// Control pins
struct { 
	char st_cl;
	char sh_cl;
	char d_in; 
	
	unsigned char st_cl_bit;
	unsigned char st_cl_port;
	volatile unsigned char *st_cl_out;
	
	unsigned char sh_cl_bit;
	unsigned char sh_cl_port;
	volatile unsigned char *sh_cl_out;
	
	unsigned char d_in_bit;
	unsigned char d_in_port;
	volatile unsigned char *d_in_out;
}pin; 


// Timer 2 clock prescalling values
enum MosiwiCubeT2PreScaller {
	T2_CLK_DIV_0    = 1,
	T2_CLK_DIV_8    = 2,
	T2_CLK_DIV_32   = 3,
	T2_CLK_DIV_64   = 4,
    T2_CLK_DIV_128  = 5,
    T2_CLK_DIV_256  = 6,
    T2_CLK_DIV_1024 = 7
};

void MosiwiCubeClearAll(void);
void MosiwiCubeTimer2Init(unsigned char prescaler, unsigned char compare);
void MosiwiCubeInit_SPI(char cs, unsigned char _cube);
void MosiwiCubeInit_Software(char st_cl, char sh_cl, char d_in, unsigned char _cube);
void MosiwiCubeUpdateLayer(unsigned char _cube, unsigned char layer, unsigned int dat);
void MosiwiCubePlayPattern(unsigned char _cube, _Pattern_info Pattern, unsigned int cycledelay, unsigned char cycles);
void MosiwiCubeSyncPlayPattern(unsigned char _cube, _Pattern_info Pattern, unsigned int cycledelay, unsigned char cycles);
void MosiwiCubeXYZ(unsigned char _cube, unsigned char x, unsigned char y, unsigned char z, unsigned char OnOff);

#endif


