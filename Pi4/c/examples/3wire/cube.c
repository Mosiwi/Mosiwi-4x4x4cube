/*
 Web: http://mosiwi.com
 Wiki: https://mosiwi-wiki.readthedocs.io
 Designer: jalen
 Date：2023-7-4
 */
//Include library file
#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../lib/3wire/Cube.h"

/**************3wire**************
Connections (for pi4)
cube ------- pi4(wiringpi)
DIN  ------- 12 --> GPIO 10
SH_C ------- 14 --> GPIO 11
ST_C ------- 10 --> GPIO 8
VCC  ------- 5V
GND  ------- GND
*********************************/

int main(void){
	//wiringPiSetup();
	//pinMode(5, OUTPUT);
	//digitalWrite(5, 0);


	// Initialise the ports and the thread
	// Parameter 1: Store the clock pin.
	// Parameter 2: Shift clock pin.
	// Parameter 3: Data pin.
	// Parameter 4: The number of cubes, maximum 10.
	MosiwiCubeInit(10, 14, 12, 1);
	// Clean up all display buffers
	MosiwiCubeClearAll();
	while(1){
		// Update the buffer
		// Parameter 1: Select the cube that you want to control.
		// Parameter 2: Select the layer where you want to control the cube.
		// Parameter 3: The control data is mapped to the 16 leds of the layer with an unsigned integer binary data.
		MosiwiCubeUpdateLayer(0, 0, 0b1111111111111111);
		// Update the buffer
		// Parameter 1: Select the cube that you want to control.
		// Parameter 2: The X-axis coordinates of the cube.
		// Parameter 3: The Y-axis coordinates of the cube.
		// Parameter 4: The Z-axis coordinates of the cube.
		// Parameter 5: The LED at the coordinate point is off(0) or on(1).
		MosiwiCubeXYZ(0, 0, 0, 1, 1);
		delay(1000);
		MosiwiCubeUpdateLayer(0, 0, 0b000000000000000);
		MosiwiCubeXYZ(0, 0, 0, 1, 0);
		delay(1000);
	}
}


