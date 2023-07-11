/*  FILE:    Mosiwi_Cube_Buffer.ino
	DATE:    29/05/23
	VERSION: 0.1
	AUTHOR:  Mosiwi	
	Note: The cube code uses timer2 to refresh the data.
*/
/* Include the cube library */
#include "Mosiwi_4x4x4cube.h"

/*************Software************
Connections 
cube ------- UNO or nano
DIN  ------- 11
SH_C ------- 13
ST_C ------- 10
VCC  ------- 5V
GND  ------- GND
*********************************/
// UNO and nano pins
#define pin_dat    11 
#define pin_st_c   10 
#define pin_sh_c   13   

 // The number of cubes.
 // Up to 20 cubes can be connected in series, at which time all cubes update data at a frequency of 50Hz.
 // The relationship between the data refresh frequency of the cube internal program and the number of cubes: 50Hz * 10/cubes
#define cube_num   1  

void setup(){
	// Initialise the ports and the timer 
	// Parameter 1: Store the clock pin.
	// Parameter 2: Shift clock pin.
	// Parameter 3: Data pin.
	// Parameter 4: The number of cubes, maximum 10.
	MosiwiCubeInit_Software(pin_st_c, pin_sh_c, pin_dat, cube_num);

	// Light up all cubes.
	for(char cube = 0; cube < cube_num; cube++){
		for(char layer = 0; layer < 4; layer++){
			// Update the buffer
			// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
			// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

			// Parameter 1: Select the cube that you want to control.
			// Parameter 2: Select the layer where you want to control the cube.
			// Parameter 3: The control data is mapped to the 16 leds of the layer with an unsigned integer binary data.
			MosiwiCubeUpdateLayer(cube, layer, 0b1111111111111111);
			delay(500);
		}
	}

	// Clean up all display buffers
	MosiwiCubeClearAll();
}

// Main sketch
void loop(){
	for(char cube = 0; cube < cube_num; cube++){
		for(char layer = 0; layer < 4; layer++){
			unsigned int ledx = 0b0000000000000001;
			for(char led = 0; led < 16; led++){
				MosiwiCubeUpdateLayer(cube, layer, ledx);
				ledx = ledx << 1;

				delay(200);
			}
		}
	}
	MosiwiCubeClearAll();
}
