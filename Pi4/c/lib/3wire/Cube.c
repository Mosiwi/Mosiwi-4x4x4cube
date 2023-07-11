/*
 * Project: 4*4*4cube for raspberry pi 4B
 * Wiki: https://mosiwi-wiki.readthedocs.io
 * Web: http://mosiwi.com
 * Engineer: Jalen
 * date: 2023-5-5
 */

#include "Cube.h"

// Cube parameters
struct { 
	unsigned char num;
	unsigned char *buffer;
	unsigned int buffer_index;
	unsigned char LastLayer;
}cube; 

// Control pins
struct { 
	char st_cl;
	char sh_cl;
	char d_in; 
}pin; 

////////////////////////////////////////////
// Send data to 74hc595 via software.
void ShiftOut(uchar l_dat, uchar h_dat, uchar layer){
	uchar bit;
	ulong temp_buf;
	ulong send_bit = 0x80000;
	uchar current_cube = cube.buffer_index/8;
	uint bit_cube_f = current_cube*24;
	uint bit_cube_b = (cube.num - current_cube)*24;
	
	temp_buf = (layer << 16) + (h_dat << 8) + l_dat;

	digitalWrite(pin.st_cl, 0);              // st_cl pin output low level.
	for (bit = 0; bit < 20; bit++) {	
		if(temp_buf & send_bit) 
			digitalWrite(pin.d_in, 1);       // d_in pin output high level.	
		else 
			digitalWrite(pin.d_in, 0);       // d_in pin output low level.
			
		send_bit >>= 1;

		// sh_cl of 74HC595 Maximum clock frequency is 30MHZ(25MHz is recommended).
		digitalWrite(pin.sh_cl, 1);          // sh_cl pin output high level.
		delayMicroseconds(1);
		digitalWrite(pin.sh_cl, 0);          // sh_cl pin output low level.	
	}
	for(bit = 0; bit < bit_cube_f; bit++){  
		digitalWrite(pin.sh_cl, 1);          // sh_cl pin output high level.
		delayMicroseconds(1);
		digitalWrite(pin.sh_cl, 0);          // sh_cl pin output low level.
		delayMicroseconds(1);
	}
	digitalWrite(pin.st_cl, 1);              // st_cl pin output high level.
	
	digitalWrite(pin.st_cl, 0);              // st_cl pin output low level.
	for(bit = 0; bit < bit_cube_b; bit++){  
		digitalWrite(pin.sh_cl, 1);          // sh_cl pin output high level.
		delayMicroseconds(1);
		digitalWrite(pin.sh_cl, 0);          // sh_cl pin output low level.
		delayMicroseconds(1);
	}
}


////////////////////////////////////////////
// Thread function
PI_THREAD (ShiftOutThread){
	while(1){
		switch(cube.LastLayer){
			case(LAYER1):
				ShiftOut(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER1);
				cube.LastLayer = LAYER2;
				break;
			case(LAYER2):
				ShiftOut(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER2);
				cube.LastLayer = LAYER3;
				break;
			case(LAYER3):
				ShiftOut(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER3);
				cube.LastLayer = LAYER4;
				break;
			case(LAYER4):
				ShiftOut(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER4);
				cube.LastLayer = LAYER1;
				break;
		}
		cube.buffer_index += 2;
		if(cube.buffer_index == cube.num*8) cube.buffer_index = 0;
	}
}


////////////////////////////////////////////
// Initialise the ports and the thread 
// Parameter 1: Store the clock pin.
// Parameter 2: Shift clock pin.
// Parameter 3: Data pin.
// Parameter 4: The number of cubes, maximum 10.
void MosiwiCubeInit(char st_cl, char sh_cl, char d_in, uchar _cube){ 
	pin.st_cl = st_cl;
	pin.sh_cl = sh_cl;
	pin.d_in  = d_in;

	wiringPiSetup();
	pinMode(pin.st_cl, OUTPUT);
	pinMode(pin.sh_cl, OUTPUT);
	pinMode(pin.d_in, OUTPUT);
	
	if(_cube > 10) cube.num = 10;
	else cube.num = _cube;
	cube.LastLayer = LAYER1;
	
	// Dynamically generates the buffer of the cube.
	cube.buffer = (unsigned char*)malloc(cube.num*8*(sizeof(unsigned char)));
	
	char x = piThreadCreate(ShiftOutThread);
	if (x != 0){
		printf ("Thread initialization failed! \n");
		return;
	}
}



// Update the buffer
// Parameter 1: Select the cube that you want to control.
// Parameter 2: Select the layer where you want to control the cube.
// Parameter 3: The control data is mapped to the 16 leds of the layer with an unsigned integer binary data.
void MosiwiCubeUpdateLayer(uchar _cube, uchar layer, uint dat){
	if(_cube > (cube.num-1) || layer > 3) return;

	cube.buffer[(_cube*8) + layer*2] = dat & 0xff;
	cube.buffer[(_cube*8) + layer*2 +1] = (dat >> 8) & 0xff;
}


// Clean up all display buffers
void MosiwiCubeClearAll(void){
	int i;
	for(i = 0; i < cube.num*8; i++) cube.buffer[i] = 0;
}



// Update the buffer
// Parameter 1: Select the cube that you want to control.
// Parameter 2: The X-axis coordinates of the cube.
// Parameter 3: The Y-axis coordinates of the cube.
// Parameter 4: The Z-axis coordinates of the cube.
// Parameter 5: The LED at the coordinate point is off(0) or on(1).
void MosiwiCubeXYZ(uchar _cube, uchar x, uchar y, uchar z, uchar OnOff){
	if(_cube > (cube.num-1) || x > 3 || y > 3 || z > 3) return;
	uchar index = _cube*8 + z*2;
	uchar led = y*4 + x;
	
	if(OnOff == 1){
		if(y < 2)
			cube.buffer[index] |= 1 << led;
		else
			cube.buffer[index + 1] |= 1 << led;
	}
	if(OnOff == 0){
		if(y < 2)
			cube.buffer[index] &= (~(1 << led))&0xff;
		else
			cube.buffer[index + 1] &= (~(1 << led))&0xff;
	}
}

























