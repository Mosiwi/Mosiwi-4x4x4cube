/*  FILE:    Mosiwi_4x4x4cube.cpp
	DATE:    29/05/23
	VERSION: 0.1
	AUTHOR:  Mosiwi
*/

#include "Arduino.h"
#include "Mosiwi_4x4x4cube.h"
#include <avr/interrupt.h>
#include <SPI.h>

// Initialise the SPI, ports and the timer2 
// Parameter 1: SPI chip select pin.
// Parameter 2: The number of cubes, maximum 25.
void MosiwiCubeInit_SPI(char cs, unsigned char _cube){
	pin.st_cl = cs;
	pinMode(pin.st_cl, OUTPUT);
	// The following Settings make the IO(st_cl) port faster.
	pin.st_cl_bit = digitalPinToBitMask(pin.st_cl);
	pin.st_cl_port = digitalPinToPort(pin.st_cl);
	pin.st_cl_out = portOutputRegister(pin.st_cl_port);
	
	SPI.begin();
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	cube.mode = 0;   //SPI
	
	if(_cube > 25) cube.num = 25;
	else cube.num = _cube;
	cube.layers = cube.num*LAYER;

	// Dynamically generates the buffer of the cube.
	cube.buffer = (unsigned int*)malloc(cube.layers*(sizeof(unsigned int)));

	// Initialise hardware 8bit-Timer2 with a 0.2mS interval.
    // Up to 25 cubes can be connected in series, at which time all cubes update data at a frequency of 50Hz. 
	// 50hz = 1000ms/(0.2ms*25cubes*4layers) --->  Due to error, the frequency value is 50Hz.
	// The relationship between the data refresh frequency of the cube internal program and the number of cubes: 50Hz * 25/cubes
	MosiwiCubeTimer2Init(T2_CLK_DIV_32, 100);   
}

// Initialise the ports and the timer2 
// Parameter 1: Store the clock pin.
// Parameter 2: Shift clock pin.
// Parameter 3: Data pin.
// Parameter 4: The number of cubes, maximum 10.
void MosiwiCubeInit_Software(char st_cl, char sh_cl, char d_in, unsigned char _cube){
	pin.st_cl = st_cl;
	pin.sh_cl = sh_cl;
	pin.d_in  = d_in;

	pinMode(pin.st_cl, OUTPUT);
	// The following Settings make the IO(st_cl) port faster.
	pin.st_cl_bit = digitalPinToBitMask(pin.st_cl);
	pin.st_cl_port = digitalPinToPort(pin.st_cl);
	pin.st_cl_out = portOutputRegister(pin.st_cl_port);
	// *pin.st_cl_out |= pin.st_cl_bit;   // Output high level.
	// *pin.st_cl_out &= ~pin.st_cl_bit;  // Output low level.

	pinMode(pin.sh_cl, OUTPUT);
	// The following Settings make the IO(sh_cl) port faster.
	pin.sh_cl_bit = digitalPinToBitMask(pin.sh_cl);
	pin.sh_cl_port = digitalPinToPort(pin.sh_cl);
	pin.sh_cl_out = portOutputRegister(pin.sh_cl_port);
	// *pin.sh_cl_out |= pin.sh_cl_bit;   // Output high level.
	// *pin.sh_cl_out &= ~pin.sh_cl_bit;  // Output low level.
	
	pinMode(pin.d_in, OUTPUT);
	// The following Settings make the IO(d_in) port faster.
	pin.d_in_bit = digitalPinToBitMask(pin.d_in);
	pin.d_in_port = digitalPinToPort(pin.d_in);
	pin.d_in_out = portOutputRegister(pin.d_in_port);
	// *pin.d_in_out |= pin.d_in_bit;   // Output high level.
	// *pin.d_in_out &= ~pin.d_in_bit;  // Output low level.
	
	cube.mode = 1;   //Software
	
	if(_cube > 10) cube.num = 10;
	else cube.num = _cube;
	cube.layers = cube.num*LAYER;

	// Dynamically generates the buffer of the cube.
	cube.buffer = (unsigned int*)malloc(cube.layers*(sizeof(unsigned int)));

	// Initialise hardware 8bit-Timer2 with a 0.4mS interval.
    // Up to 10 cubes can be connected in series, at which time all cubes update data at a frequency of 62.5Hz. 
	// 62.5hz = 1000ms/(0.4ms*10cubes*4layers) --->  Due to error, the frequency value is 50Hz.
	// The relationship between the data refresh frequency of the cube internal program and the number of cubes: 50Hz * 10/cubes
	MosiwiCubeTimer2Init(T2_CLK_DIV_64, 100);   
}


// Send data to 74hc595 via SPI. --> faster
void shiftOut(unsigned int l_dat, unsigned char h_dat){
	unsigned int push;
	unsigned char current_cube_f = cube.buffer_index/4;
	unsigned char current_cube_b = cube.num - current_cube_f;
	
	*pin.st_cl_out &= ~pin.st_cl_bit;  			// st_cl pin output low level.
	SPI.transfer(h_dat);
	SPI.transfer16(l_dat);
	
	for(push = 0; push < current_cube_f; push++){  
		SPI.transfer(0);
		SPI.transfer16(0);
	}
	*pin.st_cl_out |= pin.st_cl_bit;            // st_cl pin output high level.
	
	*pin.st_cl_out &= ~pin.st_cl_bit;           // st_cl pin output low level.
	for(push = 0; push < current_cube_b; push++){  
		SPI.transfer(0);
		SPI.transfer16(0);
	}
}

// Send data to 74hc595 via software. --> slowish
void ShiftOut(unsigned int l_dat, unsigned char h_dat){
	unsigned char bit;
	unsigned int  push;
	unsigned long temp_buf;
	unsigned long send_bit = 0x80000;
	unsigned char current_cube = cube.buffer_index/4;
	unsigned int  bit_cube_f = current_cube*24;
	unsigned int  bit_cube_b = (cube.num - current_cube)*24;
	
	temp_buf = h_dat*65536 + l_dat;

	*pin.st_cl_out &= ~pin.st_cl_bit;  // st_cl pin output low level.
	for (bit = 0; bit < 20; bit++) {	
		if(temp_buf & send_bit) 
			*pin.d_in_out |= pin.d_in_bit;   // d_in pin output high level.	
		else 
			*pin.d_in_out &= ~pin.d_in_bit;  // d_in pin output low level.
			
		send_bit >>= 1;

		// sh_cl of 74HC595 Maximum clock frequency is 30MHZ(25MHz is recommended).
		*pin.sh_cl_out |= pin.sh_cl_bit;     // sh_cl pin output high level.
		//delayMicroseconds(1);
		*pin.sh_cl_out &= ~pin.sh_cl_bit;    // sh_cl pin output low level.	
	}
	for(bit = 0; bit < bit_cube_f; bit++){  
		*pin.sh_cl_out |= pin.sh_cl_bit;     	// sh_cl pin output high level.
		*pin.sh_cl_out &= ~pin.sh_cl_bit;    	// sh_cl pin output low level.
	}
	*pin.st_cl_out |= pin.st_cl_bit;            // st_cl pin output high level.
	
	*pin.st_cl_out &= ~pin.st_cl_bit;           // st_cl pin output low level.
	for(bit = 0; bit < bit_cube_b; bit++){  
		*pin.sh_cl_out |= pin.sh_cl_bit;     	// sh_cl pin output high level.
		*pin.sh_cl_out &= ~pin.sh_cl_bit;    	// sh_cl pin output low level.
	}
}


/* Reconfigures the hardware 8bit-timer2. Used to automatically refresh the matrix */
void MosiwiCubeTimer2Init(unsigned char prescaler, unsigned char compare){
	/* Turn off interrupts whilst we setup the timer */
	cli();
	/* Set timer mode to clear timer on compare match (mode 2)*/
	TCCR2A = (1<<WGM21);

	/* Set the prescaler */
	TCCR2B = prescaler;

	/* Clear timer 2 counter */
	TCNT2 = 0;

	/* Set the compare match register */
	OCR2A = compare;

	/* Enable timer 2 interrupt on compare match */
	TIMSK2 = (1<<OCIE2A);

  	/* Turn interrupts back on */
  	sei();
}

// Interrupt service routine for 8bit-Timer2 compare match 
// The interrupt function program scans a layer of leds in all cubes each time it is executed.
ISR(TIMER2_COMPA_vect){
	if(cube.mode){  //software --> slowish
		switch(cube.LastLayer){
			case(LAYER1):
				ShiftOut(cube.buffer[cube.buffer_index], LAYER1);
				cube.LastLayer = LAYER2;
				break;
			case(LAYER2):
				ShiftOut(cube.buffer[cube.buffer_index], LAYER2);
				cube.LastLayer = LAYER3;
				break;
			case(LAYER3):
				ShiftOut(cube.buffer[cube.buffer_index], LAYER3);
				cube.LastLayer = LAYER4;
				break;
			case(LAYER4):
				ShiftOut(cube.buffer[cube.buffer_index], LAYER4);
				cube.LastLayer = LAYER1;
				break;
		}
	}else{  //SPI --> faster
		switch(cube.LastLayer){
			case(LAYER1):
				shiftOut(cube.buffer[cube.buffer_index], LAYER1);
				cube.LastLayer = LAYER2;
				break;
			case(LAYER2):
				shiftOut(cube.buffer[cube.buffer_index], LAYER2);
				cube.LastLayer = LAYER3;
				break;
			case(LAYER3):
				shiftOut(cube.buffer[cube.buffer_index], LAYER3);
				cube.LastLayer = LAYER4;
				break;
			case(LAYER4):
				shiftOut(cube.buffer[cube.buffer_index], LAYER4);
				cube.LastLayer = LAYER1;
				break;
		}
	}

	cube.buffer_index ++;
	if(cube.buffer_index == cube.layers) cube.buffer_index = 0;
}

// 建议用户的数据刷新频率小于立方体内部程序的数据刷新频率，否则可能会出现立方体内部程序的数据刷新频率跟不上用户的数据刷新频率。
// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

// Update the buffer
// Parameter 1: Select the cube that you want to control.
// Parameter 2: Select the layer where you want to control the cube.
// Parameter 3: The control data is mapped to the 16 leds of the layer with an unsigned integer binary data.
void MosiwiCubeUpdateLayer(unsigned char _cube, unsigned char layer, unsigned int dat){
	if(_cube > (cube.num-1) || layer > 3) return;

	cube.buffer[(_cube*4) + layer] = dat;
}


// Clean up all display buffers
void MosiwiCubeClearAll(void){
	int i;
	for(i = 0; i < cube.layers; i++) cube.buffer[i] = 0;
}


// 建议用户的数据刷新频率小于立方体内部程序的数据刷新频率，否则可能会出现立方体内部程序的数据刷新频率跟不上用户的数据刷新频率。
// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

// Parameter 1: Select the cube that you want to control.
// Parameter 2: Select the animation.
// Parameter 3: The delay time of each animation.
// Parameter 4: The number of times each animation is executed.
void MosiwiCubePlayPattern(unsigned char _cube, _Pattern_info Pattern, unsigned int cycledelay, unsigned char cycles){
	unsigned char index;
	const unsigned int *ptr;

	if(_cube > (cube.num-1)) return;
	
	while(cycles){
		ptr = Pattern.PatternArray;
		for (index = 0; index < Pattern.AnimationLength; index++){
			cube.buffer[_cube*4] = pgm_read_word_near(ptr);
			ptr++;
			cube.buffer[(_cube*4)+1] = pgm_read_word_near(ptr);
			ptr++;
			cube.buffer[(_cube*4)+2] = pgm_read_word_near(ptr);
			ptr++;
			cube.buffer[(_cube*4)+3] = pgm_read_word_near(ptr);
			ptr++;
			delay(cycledelay);
		}
		cycles--;
	} 
}


// 建议用户的数据刷新频率小于立方体内部程序的数据刷新频率，否则可能会出现立方体内部程序的数据刷新频率跟不上用户的数据刷新频率。
// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

// Parameter 1: Synchronously control the number of cubes.
// Parameter 2: Select the animation.
// Parameter 3: The delay time of each animation.
// Parameter 4: The number of times each animation is executed.
void MosiwiCubeSyncPlayPattern(unsigned char _cube, _Pattern_info Pattern, unsigned int cycledelay, unsigned char cycles){
	unsigned char index;
	const unsigned int *ptr;

	if(_cube > (cube.num)) return;

	while(cycles){
		ptr = Pattern.PatternArray;
		for (index = 0; index < Pattern.AnimationLength; index++){
			for(char i=0; i<_cube; i++){
				cube.buffer[i*4] = pgm_read_word_near(ptr);
				cube.buffer[(i*4)+1] = pgm_read_word_near(ptr+1);
				cube.buffer[(i*4)+2] = pgm_read_word_near(ptr+2);
				cube.buffer[(i*4)+3] = pgm_read_word_near(ptr+3);
			}
			ptr += 4;
			delay(cycledelay);
		}
		cycles--;
	} 
}


// 建议用户的数据刷新频率小于立方体内部程序的数据刷新频率，否则可能会出现立方体内部程序的数据刷新频率跟不上用户的数据刷新频率。
// It is recommended that the user's data refresh frequency be less than the data refresh frequency of the cube internal program; 
// otherwise, the data refresh frequency of the cube internal program may not keep up with the user's data refresh frequency.

// Update the buffer
// Parameter 1: Select the cube that you want to control.
// Parameter 2: The X-axis coordinates of the cube.
// Parameter 3: The Y-axis coordinates of the cube.
// Parameter 4: The Z-axis coordinates of the cube.
// Parameter 5: The LED at the coordinate point is off(0) or on(1).
void MosiwiCubeXYZ(unsigned char _cube, unsigned char x, unsigned char y, unsigned char z, unsigned char OnOff){
	if(_cube > (cube.num-1) || x > 3 || y > 3 || z > 3) return;
	unsigned int index = _cube*4 + z;
	unsigned char led = y*4 + x;
	
	if(OnOff == 1)
		cube.buffer[index] |= 1 << led;
	if(OnOff == 0)
		cube.buffer[index] &= (~(1 << led))&0xffff;
}







