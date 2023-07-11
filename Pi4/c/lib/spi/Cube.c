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

////////////////////////////////////////////
// The host writes data to the slave.
void Spi_write_data(uchar l_dat, uchar h_dat, uchar layer){
	uchar push = 0;
	const char push_buf[3] = {0, 0, 0};
	const char buf[3] = {layer, h_dat, l_dat};
	
	bcm2835_gpio_write(8, LOW);
	bcm2835_spi_writenb (buf, 3);
	for(push = 0; push < cube.buffer_index/8; push++){  
		bcm2835_spi_writenb (push_buf, 3);
	}
	bcm2835_gpio_write(8, HIGH);                // st_cl pin output high level.
	bcm2835_gpio_write(8, LOW);
	for(push = 0; push < cube.num-cube.buffer_index/8; push++){  
		bcm2835_spi_writenb (push_buf, 3);
	}
}


////////////////////////////////////////////
// Thread function
PI_THREAD (Spi_write_dataThread){
	while(1){
		switch(cube.LastLayer){
			case(LAYER1):
				Spi_write_data(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER1);
				cube.LastLayer = LAYER2;
				break;
			case(LAYER2):
				Spi_write_data(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER2);
				cube.LastLayer = LAYER3;
				break;
			case(LAYER3):
				Spi_write_data(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER3);
				cube.LastLayer = LAYER4;
				break;
			case(LAYER4):
				Spi_write_data(cube.buffer[cube.buffer_index], cube.buffer[cube.buffer_index+1], LAYER4);
				cube.LastLayer = LAYER1;
				break;
		}
		cube.buffer_index += 2;
		if(cube.buffer_index == cube.num*8) cube.buffer_index = 0;
	}
}


////////////////////////////////////////////
// Initialise the SPI and SPI chip select pin. 
// Parameter 1: The number of cubes, maximum 25.
void MosiwiCubeInit(uchar _cube){ 
    if (!bcm2835_init()){
		printf("bcm2835_init failed. Are you running as root??\n");
		return;
    }
    if (!bcm2835_spi_begin()){
		printf("bcm2835_spi_begin failed. Are you running as root??\n");
		return;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  
    //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // 6.1035156kHz 
	bcm2835_spi_set_speed_hz(25000000);                             // 25MHz	
    bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);                    
    bcm2835_gpio_fsel(8, BCM2835_GPIO_FSEL_OUTP);                   // GPIO8, set chip select pin
    //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
	bcm2835_delay(28);   // Necessary delay, standard is 28ms.
	
	if(_cube > 25) cube.num = 25;
	else cube.num = _cube;
	cube.LastLayer = LAYER1;
	
	// Dynamically generates the buffer of the cube.
	cube.buffer = (unsigned char*)malloc(cube.num*8*(sizeof(unsigned char)));
	
	wiringPiSetup();
	char x = piThreadCreate(Spi_write_dataThread);
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

























