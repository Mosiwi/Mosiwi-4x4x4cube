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
from machine import Timer, Pin

st_c = 0
sh_c = 0
dout = 0
layer = 0
timer = 0
cube_num = 0
cnbe_buffer = 0
cnbe_buffer_len = 0
cnbe_buffer_index = 0

def write(l_dat, h_dat, f_dat):
    global st_c
    global sh_c
    global dout

    send_bit = 0x80000
    buf_dat = (f_dat << 16) + (h_dat << 8) + l_dat
    current_cube = cnbe_buffer_index//8
    st_c(0)
    for i in range(20):
        dout(buf_dat & send_bit)
        send_bit >>= 1
        sh_c(1)
        sh_c(0)
    for i in range(0, current_cube):
        for i in range(24):
            sh_c(1)
            sh_c(0)
    st_c(1)
    st_c(0)
    for i in range(0, cube_num - current_cube):
        for i in range(24):
            sh_c(1)
            sh_c(0)


def mycallback(t):
    global layer
    global cnbe_buffer_index
    
    if layer == 0: 
        write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xE)
    elif layer == 1: 
        write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xD)
    elif layer == 2: 
        write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0xB)
    elif layer == 3: 
        write(cnbe_buffer[cnbe_buffer_index], cnbe_buffer[cnbe_buffer_index+1], 0x7)

    layer = layer + 1
    if layer > 3:
        layer = 0
    
    cnbe_buffer_index = cnbe_buffer_index + 2
    if cnbe_buffer_index == cnbe_buffer_len:
        cnbe_buffer_index = 0

'''
Initialise the SPI, ports and the timer 
Parameter 2: The number of cubes, maximum 3.
'''
def MosiwiCube_init(cube_n):
    global st_c
    global sh_c
    global dout
    global timer
    global cube_num
    global cnbe_buffer
    global cnbe_buffer_len

    # Up to 3 cubes can be connected in series.
    if cube_n > 3:
        return
    cube_num = cube_n
    cnbe_buffer_len = cube_num*8
    cnbe_buffer = bytearray(cnbe_buffer_len)
    # The refresh frequency of the cube led lamp is 50Hz
    timer = Timer(freq=200*cube_num, mode=Timer.PERIODIC, callback=mycallback)
    st_c = Pin(17, mode=Pin.OUT, value=0)
    sh_c = Pin(18, mode=Pin.OUT, value=0)
    dout = Pin(19, mode=Pin.OUT, value=0)

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
    
    