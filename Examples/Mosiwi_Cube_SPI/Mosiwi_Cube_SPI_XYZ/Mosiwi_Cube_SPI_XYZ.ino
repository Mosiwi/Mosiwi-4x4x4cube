/*  FILE:    Mosiwi_Cube_Buffer.ino
	DATE:    29/05/23
	VERSION: 0.1
	AUTHOR:  Mosiwi	
	Note: The cube code uses timer2 to refresh the data.
*/

/* Include the cube library */
#include "Mosiwi_4x4x4cube.h"

/***************SPI***************
cube ------- UNO or nano
DIN  ------- 11/SCK
SH_C ------- 13/MOSI
ST_C ------- 10/CS
VCC  ------- 5V
GND  ------- GND
*********************************/

#define ON   1
#define OFF  0

 // The number of cubes.
 // Up to 25 cubes can be connected in series, at which time all cubes update data at a frequency of 50Hz.
 // The relationship between the data refresh frequency of the cube internal program and the number of cubes: 50Hz * 25/cubes
#define cube_num   1  

void setup(){
	// Initialise the SPI, ports and the timer2 
	// Parameter 1: SPI chip select pin.
	// Parameter 2: The number of cubes, maximum ?.
	MosiwiCubeInit_SPI(10, cube_num);

	// Clean up all display buffers
	MosiwiCubeClearAll();
}

// Main sketch
void loop(){
	for(char cube = 0; cube < cube_num; cube++){
		for(char z = 0; z < 4; z++){
			for(char y = 0; y < 4; y++){
				for(char x = 0; x < 4; x++){
					// Update the buffer
					// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
					// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

					// Parameter 1: Select the cube that you want to control.
					// Parameter 2: The X-axis coordinates of the cube.
					// Parameter 3: The Y-axis coordinates of the cube.
					// Parameter 4: The Z-axis coordinates of the cube.
					// Parameter 5: The LED at the coordinate point is off(0) or on(1).
					MosiwiCubeXYZ(cube, x, y, z, ON);
					delay(200);
				}
			}
		}
	}
	MosiwiCubeClearAll();
}
