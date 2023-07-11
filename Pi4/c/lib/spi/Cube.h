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
#include <bcm2835.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int
/***************SPI***************
Connections (for pi4)
cube ------- pi4
DIN  ------- GPIO 10
SH_C ------- GPIO 11
ST_C ------- GPIO 8
VCC  ------- 5V
GND  ------- GND
*********************************/

// The parameters of a cube
#define LAYER1 0xFE
#define LAYER2 0xFD
#define LAYER3 0xFB
#define LAYER4 0xF7


void Spi_write_data(uchar l_dat, uchar h_dat, uchar layer);

void MosiwiCubeInit(uchar _cube);
void MosiwiCubeClearAll(void);
void MosiwiCubeUpdateLayer(uchar _cube, uchar layer, uint dat);
void MosiwiCubeXYZ(uchar _cube, uchar x, uchar y, uchar z, uchar OnOff);

#endif
