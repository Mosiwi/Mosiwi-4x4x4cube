'''
FILE:    spi.py
DATE:    29/06/23
VERSION: 0.1
AUTHOR:  Mosiwi

Wiring diagram:
Cube   ------   Pico
GND    ------   GND
VCC    ------   VUSB
SH_C   ------   18
ST_C   ------   17
DIN    ------   19
'''
import time
from machine import Timer
from machine import Timer, SPI, Pin

cs = 0
spi = 0
layer = 0
cube_num = 0
cnbe_buffer = 0
cnbe_buffer_len = 0
cnbe_buffer_index = 0

buf_dat = bytearray(3)
buf_push = bytearray([0, 0, 0])

def spi_write(l_dat, h_dat, f_dat):
    buf_dat[0] = f_dat
    buf_dat[1] = h_dat
    buf_dat[2] = l_dat
    current_cube = cnbe_buffer_index//8
    cs(0)
    spi.write(buf_dat)
    for i in range(0, current_cube):
        spi.write(buf_push)
    cs(1)
    cs(0)
    for i in range(0, cube_num - current_cube):
        spi.write(buf_push)


def mycallback(t):
    global layer
    global cnbe_buffer_index

    if layer == 0: 
        spi_write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xE)
    elif layer == 1: 
        spi_write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xD)
    elif layer == 2: 
        spi_write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xB)
    elif layer == 3: 
        spi_write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0x7)
    
    layer += 1
    if layer > 3:
        layer = 0
    
    cnbe_buffer_index = cnbe_buffer_index + 2
    if cnbe_buffer_index == cnbe_buffer_len:
        cnbe_buffer_index = 0

'''
Initialise the SPI, ports and the timer 
Parameter 2: The number of cubes, maximum 12.
'''
def MosiwiCube_init(cube_n):
    global cs
    global spi
    global cube_num
    global cnbe_buffer
    global cnbe_buffer_len

    # Up to 10 cubes can be connected in series.
    if cube_n > 10:
        return
    cube_num = cube_n
    cnbe_buffer_len = cube_num*8
    cnbe_buffer = bytearray(cnbe_buffer_len)
    # The LED refresh frequency of the cube is 50Hz.
    Timer(freq=200*cube_num, mode=Timer.PERIODIC, callback=mycallback)
    cs = Pin(17, mode=Pin.OUT, value=0)
    spi = SPI(0,baudrate=25_000_000,
                polarity=1,
                phase=1,
                bits=8,
                firstbit=SPI.MSB,
                sck=Pin(18),
                mosi=Pin(19),
                miso=Pin(16))

# Clean up all display buffers
def MosiwiCubeClearAll():
    for i in range(0, cnbe_buffer_len):
        cnbe_buffer[i] = 0

'''
Update the buffer
Parameter 1: Select the cube that you want to control.
Parameter 2: Select the layer where you want to control the cube.
Parameter 3: The control data is mapped to the 16 leds of the layer with an unsigned integer binary data(0bxxxxxxxxxxxxxxxx).
'''
def MosiwiCubeUpdateLayer(cube, layer, dat):
    if cube > cube_num-1 or layer > 3:
        return
    cnbe_buffer[cube*8 + layer*2] = dat & 0xff
    cnbe_buffer[cube*8 + layer*2 + 1] = (dat>>8) & 0xff


'''
// Update the buffer
// Parameter 1: Select the cube that you want to control.
// Parameter 2: The X-axis coordinates of the cube.
// Parameter 3: The Y-axis coordinates of the cube.
// Parameter 4: The Z-axis coordinates of the cube.
// Parameter 5: The LED at the coordinate point is off(0) or on(1).
'''
def MosiwiCubeXYZ(cube, x, y, z, OnOff):
    if OnOff == 1:
        if y < 2:
            cnbe_buffer[cube*8 + z*2] |= 1 << (y*4 + x)
        else:
            cnbe_buffer[cube*8 + z*2 + 1] |= 1 << ((y-2)*4 + x)
    if OnOff == 0:
        if y <  2:
            cnbe_buffer[cube*8 + z*2] &= ~(1 << (y*4 + x))
        else:
            cnbe_buffer[cube*8 + z*2 + 1] &= ~(1 << ((y-2)*4 + x))


MosiwiCube_init(1)
MosiwiCubeClearAll()
while True:
    for cube in range(0, cube_num):
        for i in range(0, 4):
            MosiwiCubeUpdateLayer(cube, i, 0b1111100110011111)
            time.sleep_ms(1000//cube_num)
    for cube in range(0, cube_num):
        for i in range(0, 4):
            MosiwiCubeUpdateLayer(cube, i, 0b0000000000000000)
            time.sleep_ms(1000//cube_num)
        
    for cube in range(0, cube_num):
        for z in range(0, 4):
            for y in range(0, 4):
                for x in range(0, 4):
                    MosiwiCubeXYZ(cube, x, y, z, 1);
                    time.sleep_ms(200//cube_num)
    for cube in range(0, cube_num):
        for z in range(0, 4):
            for y in range(0, 4):
                for x in range(0, 4):
                    MosiwiCubeXYZ(cube, x, y, z, 0);
                    time.sleep_ms(200//cube_num)
    
