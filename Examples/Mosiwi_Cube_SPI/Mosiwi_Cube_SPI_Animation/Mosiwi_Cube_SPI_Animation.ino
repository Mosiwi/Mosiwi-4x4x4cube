/* FILE:    Mosiwi_Cube_Animation.ino
   DATE:    29/05/23
   VERSION: 0.1
   AUTHOR:  Mosiwi
   Note: The cube code uses timer2 to refresh the data.
*/

/* Include the cube library */
#include "Mosiwi_4x4x4cube.h"
/* Include the predefined patterns */
#include "Mosiwi_Cube_Animation.h"

/***************SPI***************
cube ------- UNO or nano
DIN  ------- 11/SCK
SH_C ------- 13/MOSI
ST_C ------- 10/CS
VCC  ------- 5V
GND  ------- GND
*********************************/

 // The number of cubes.
 // Up to 25 cubes can be connected in series, at which time all cubes update data at a frequency of 50Hz.
 // The relationship between the data refresh frequency of the cube internal program and the number of cubes: 50Hz * 25/cubes
#define cube_num   1  

// Set the default speed for all animations in ms.
// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the 1/2 cube internal program; 
// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.
#define SPEED 200

void setup(){
	// Initialise the SPI, ports and the timer2 
	// Parameter 1: SPI chip select pin.
	// Parameter 2: The number of cubes, maximum 25.
	MosiwiCubeInit_SPI(10, cube_num);

	// Clean up all display buffers
	MosiwiCubeClearAll();
}



void loop(){
	// Step through each predefined LED pattern
	for(char cube = 0; cube < cube_num; cube++){
		// Parameter 1: Select the cube that you want to control.
		// Parameter 2: Select the animation.
		// Parameter 3: The delay time of each animation.
		// Parameter 4: The number of times each animation is executed.
		MosiwiCubePlayPattern(cube, LayerBounce, SPEED, 2);

		MosiwiCubePlayPattern(cube, LayerRotate, SPEED, 10);
		MosiwiCubePlayPattern(cube, Spiral, SPEED, 1);
		MosiwiCubePlayPattern(cube, BorderLoop, SPEED, 3);
		MosiwiCubePlayPattern(cube, BorderFlash, SPEED, 5);
		MosiwiCubePlayPattern(cube, BorderWipe, SPEED, 1);
		MosiwiCubePlayPattern(cube, Block4Random, SPEED, 5);
		MosiwiCubePlayPattern(cube, Block4Corners, SPEED, 3);
		MosiwiCubePlayPattern(cube, Rise, SPEED, 5);
		MosiwiCubePlayPattern(cube, FourRotate, SPEED, 5);
		MosiwiCubePlayPattern(cube, SpiralLayers, SPEED, 2);
		MosiwiCubePlayPattern(cube, Snake, SPEED, 5);
		MosiwiCubePlayPattern(cube, Upright, SPEED, 5);
		MosiwiCubePlayPattern(cube, RandomFill, SPEED, 5);
		MosiwiCubePlayPattern(cube, Cube, SPEED, 5);
	}
}




