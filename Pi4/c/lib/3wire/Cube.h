/*
 * Project: BC7278 hardware spi
 * Function: Display 8 segments of nixie tube and read key values
 * Wiki: https://mosiwi-wiki.readthedocs.io
 * Web: http://mosiwi.com
 * Engineer: Jalen
 * date: 2023-7-3
 */

#ifndef Cube_h
#define Cube_h

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
/***************SPI***************
Connections (for pi4)
cube ------- pi4
DIN  ------- GPIO x
SH_C ------- GPIO x
ST_C ------- GPIO x
VCC  ------- 5V or 3V3
GND  ------- GND
*********************************/

// The parameters of a cube
#define LAYER1 0xFE
#define LAYER2 0xFD
#define LAYER3 0xFB
#define LAYER4 0xF7


void ShiftOut(uchar l_dat, uchar h_dat, uchar layer);

void MosiwiCubeInit(char st_cl, char sh_cl, char d_in, uchar _cube);
void MosiwiCubeClearAll(void);
void MosiwiCubeUpdateLayer(uchar _cube, uchar layer, uint dat);
void MosiwiCubeXYZ(uchar _cube, uchar x, uchar y, uchar z, uchar OnOff);

#endif
