#ifndef Mosiwi_Cube_Animation_h
#define Mosiwi_Cube_Animation_h


const PROGMEM unsigned int aLayerBounce[][4] = {{0xFFFF, 0x0000, 0x0000, 0x0000},
                                                {0x0000, 0xFFFF, 0x0000, 0x0000},
                                                {0x0000, 0x0000, 0xFFFF, 0x0000},
                                                {0x0000, 0x0000, 0x0000, 0xFFFF},
                                                {0x0000, 0x0000, 0xFFFF, 0x0000},
                                                {0x0000, 0xFFFF, 0x0000, 0x0000},
                                                {0xFFFF, 0x0000, 0x0000, 0x0000},
                                                
                                                {0xF000, 0xF000, 0xF000, 0xF000},
                                                {0x0F00, 0x0F00, 0x0F00, 0x0F00},
                                                {0x00F0, 0x00F0, 0x00F0, 0x00F0},
                                                {0x000F, 0x000F, 0x000F, 0x000F},
                                                {0x00F0, 0x00F0, 0x00F0, 0x00F0},
                                                {0x0F00, 0x0F00, 0x0F00, 0x0F00},
                                                {0xF000, 0xF000, 0xF000, 0xF000},
                                                
                                                {0x8888, 0x8888, 0x8888, 0x8888},
                                                {0x4444, 0x4444, 0x4444, 0x4444},
                                                {0x2222, 0x2222, 0x2222, 0x2222},
                                                {0x1111, 0x1111, 0x1111, 0x1111},
                                                {0x2222, 0x2222, 0x2222, 0x2222},
                                                {0x4444, 0x4444, 0x4444, 0x4444},
                                                {0x8888, 0x8888, 0x8888, 0x8888}};
											
const _Pattern_info LayerBounce = {21,aLayerBounce[0]};												
												


const PROGMEM unsigned int aLayerRotate[][4] = {{0x03C0, 0x03C0, 0x03C0, 0x03C0},		
                                                {0x1248, 0x1248, 0x1248, 0x1248},		
                                                {0x2244, 0x2244, 0x2244, 0x2244},		
                                                {0x4422, 0x4422, 0x4422, 0x4422},		
                                                {0x8421, 0x8421, 0x8421, 0x8421},		
                                                {0x0C30, 0x0C30, 0x0C30, 0x0C30}};

const _Pattern_info LayerRotate = {6,aLayerRotate[0]};		
	
												

												
const PROGMEM unsigned int aSpiral[][4] = {{0x0000, 0x0000, 0x0000, 0x0000},		
                                            {0x0040, 0x0040, 0x0040, 0x0040},		
                                            {0x0060, 0x0060, 0x0060, 0x0060},		
                                            {0x0260, 0x0260, 0x0260, 0x0260},		
                                            {0x0660, 0x0660, 0x0660, 0x0660},		
                                            {0x0E60, 0x0E60, 0x0E60, 0x0E60},		
                                            {0x0EE0, 0x0EE0, 0x0EE0, 0x0EE0},		
                                            {0x0EE8, 0x0EE8, 0x0EE8, 0x0EE8},		
                                            {0x0EEC, 0x0EEC, 0x0EEC, 0x0EEC},		
                                            {0x0EEE, 0x0EEE, 0x0EEE, 0x0EEE},		
                                            {0x0EEF, 0x0EEF, 0x0EEF, 0x0EEF},		
                                            {0x0EFF, 0x0EFF, 0x0EFF, 0x0EFF},		
                                            {0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF},		
                                            {0x1FFF, 0x1FFF, 0x1FFF, 0x1FFF},		
                                            {0x3FFF, 0x3FFF, 0x3FFF, 0x3FFF},		
                                            {0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF},		
                                            {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}};

const _Pattern_info Spiral = {17,aSpiral[0]};	



const PROGMEM unsigned int aBorderLoop[][4] = { {0xF000, 0x0000, 0x0000, 0x0000},		
                                                {0x0F00, 0x0000, 0x0000, 0x0000},		
                                                {0x00F0, 0x0000, 0x0000, 0x0000},		
                                                {0x000F, 0x0000, 0x0000, 0x0000},		
                                                {0x0000, 0x000F, 0x0000, 0x0000},		
                                                {0x0000, 0x0000, 0x000F, 0x0000},		
                                                {0x0000, 0x0000, 0x0000, 0x000F},		
                                                {0x0000, 0x0000, 0x0000, 0x00F0},		
                                                {0x0000, 0x0000, 0x0000, 0x0F00},		
                                                {0x0000, 0x0000, 0x0000, 0xF000},		
                                                {0x0000, 0x0000, 0xF000, 0x0000},		
                                                {0x0000, 0xF000, 0x0000, 0x0000}};		

const _Pattern_info BorderLoop = {12,aBorderLoop[0]};

	

const PROGMEM unsigned int aBorderFlash[][4] = {{0xF99F, 0x9009, 0x9009, 0xF99F},		
                                                {0x0000, 0x0000, 0x0000, 0x0000},		
                                                {0xF99F, 0x9009, 0x9009, 0xF99F},		
                                                {0x0000, 0x0000, 0x0000, 0x0000},		
                                                {0xF99F, 0x9009, 0x9009, 0xF99F},		
                                                {0x0000, 0x0000, 0x0000, 0x0000}};	

const _Pattern_info BorderFlash = {6,aBorderFlash[0]};	



const PROGMEM unsigned int aBorderWipe[][4] = { {0xF99F, 0x9009, 0x9009, 0xF99F},		
                                                {0xF99F, 0x9009, 0xF009, 0x0F9F},		
                                                {0xF99F, 0xF009, 0x0F09, 0x00FF},		
                                                {0xF99F, 0x0F09, 0x00F9, 0x000F},		
                                                {0x0F9F, 0x00F9, 0x000F, 0x0000},		
                                                {0x00FF, 0x000F, 0x0000, 0x0000},		
                                                {0x000F, 0x0000, 0x0000, 0x0000},		
                                                {0x0000, 0x0000, 0x0000, 0x0000}};		

const _Pattern_info BorderWipe = {8,aBorderWipe[0]};	



const PROGMEM unsigned int aBlock4Random[][4] = { {0x0033, 0x0033, 0x0000, 0x0000},		
                                                  {0x0000, 0x0000, 0xCC00, 0xCC00},		
                                                  {0x0000, 0x0000, 0x00CC, 0x00CC},		
                                                  {0x3300, 0x3300, 0x0000, 0x0000},		
                                                  {0x00CC, 0x00CC, 0x0000, 0x0000},		
                                                  {0x0000, 0x0000, 0x3300, 0x3300},		
                                                  {0x0000, 0x0000, 0x0033, 0x0033},		
                                                  {0xCC00, 0xCC00, 0x0000, 0x0000}};	

const _Pattern_info Block4Random = {8,aBlock4Random[0]};	



const PROGMEM unsigned int aBlock4Corners[][4] = {{0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC},		
                                                  {0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC},		
                                                  {0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC},		
                                                  {0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC},		
                                                  {0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC},		
                                                  {0x0033, 0x0033, 0xCC00, 0xCC00},		
                                                  {0x00CC, 0x00CC, 0x3300, 0x3300},		
                                                  {0xCC00, 0xCC00, 0x0033, 0x0033},		
                                                  {0x3300, 0x3300, 0x00CC, 0x00CC}};	
												  
const _Pattern_info Block4Corners = {24,aBlock4Corners[0]};	



const PROGMEM unsigned int aRise[][4] = { {0xFFFF, 0x0000, 0x0000, 0x0000},		
                                          {0x0660, 0x0660, 0x0660, 0x0660},		
                                          {0x0000, 0x0660, 0x0660, 0x0660},		
                                          {0x0000, 0x0000, 0x0660, 0x0660},		
                                          {0x0000, 0x0000, 0x0000, 0x0660},		
                                          {0x0000, 0x0000, 0x0000, 0xFFFF},		
                                          {0x0000, 0x0000, 0x0000, 0x0000}};		

const _Pattern_info Rise = {7,aRise[0]};



const PROGMEM unsigned int aFourRotate[][4] = { {0x4002, 0x0000, 0x0000, 0x4002},		
                                                {0x2004, 0x0000, 0x0000, 0x2004},		
                                                {0x1008, 0x0000, 0x0000, 0x1008},		
                                                {0x0180, 0x0000, 0x0000, 0x0180},		
                                                {0x0810, 0x0000, 0x0000, 0x0810},		
                                                {0x8001, 0x0000, 0x0000, 0x8001}};	

const _Pattern_info FourRotate = {6,aFourRotate[0]};



const PROGMEM unsigned int aSpiralLayers[][4] = { {0x0040, 0x0000, 0x0000, 0x0000},		
                                                  {0x0060, 0x0000, 0x0000, 0x0000},		
                                                  {0x0260, 0x0000, 0x0000, 0x0000},		
                                                  {0x0660, 0x0000, 0x0000, 0x0000},		
                                                  {0x0E60, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EE0, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EE8, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EEC, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EEE, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EEF, 0x0000, 0x0000, 0x0000},		
                                                  {0x0EFF, 0x0000, 0x0000, 0x0000},		
                                                  {0x0FFF, 0x0000, 0x0000, 0x0000},		
                                                  {0x1FFF, 0x0000, 0x0000, 0x0000},		
                                                  {0x3FFF, 0x0000, 0x0000, 0x0000},		
                                                  {0x7FFF, 0x0000, 0x0000, 0x0000},		
                                                  {0xFFFF, 0x0000, 0x0000, 0x0000},		
                                                  {0x0000, 0x0040, 0x0000, 0x0000},		
                                                  {0x0000, 0x0060, 0x0000, 0x0000},		
                                                  {0x0000, 0x0260, 0x0000, 0x0000},		
                                                  {0x0000, 0x0660, 0x0000, 0x0000},		
                                                  {0x0000, 0x0E60, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EE0, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EE8, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EEC, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EEE, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EEF, 0x0000, 0x0000},		
                                                  {0x0000, 0x0EFF, 0x0000, 0x0000},		
                                                  {0x0000, 0x0FFF, 0x0000, 0x0000},		
                                                  {0x0000, 0x1FFF, 0x0000, 0x0000},		
                                                  {0x0000, 0x3FFF, 0x0000, 0x0000},		
                                                  {0x0000, 0x7FFF, 0x0000, 0x0000},		
                                                  {0x0000, 0xFFFF, 0x0000, 0x0000},		
                                                  {0x0000, 0x0000, 0x0040, 0x0000},		
                                                  {0x0000, 0x0000, 0x0060, 0x0000},		
                                                  {0x0000, 0x0000, 0x0260, 0x0000},		
                                                  {0x0000, 0x0000, 0x0660, 0x0000},		
                                                  {0x0000, 0x0000, 0x0E60, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EE0, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EE8, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EEC, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EEE, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EEF, 0x0000},		
                                                  {0x0000, 0x0000, 0x0EFF, 0x0000},		
                                                  {0x0000, 0x0000, 0x0FFF, 0x0000},		
                                                  {0x0000, 0x0000, 0x1FFF, 0x0000},		
                                                  {0x0000, 0x0000, 0x3FFF, 0x0000},		
                                                  {0x0000, 0x0000, 0x7FFF, 0x0000},		
                                                  {0x0000, 0x0000, 0xFFFF, 0x0000},		
                                                  {0x0000, 0x0000, 0x0000, 0x0040},		
                                                  {0x0000, 0x0000, 0x0000, 0x0060},		
                                                  {0x0000, 0x0000, 0x0000, 0x0260},		
                                                  {0x0000, 0x0000, 0x0000, 0x0660},		
                                                  {0x0000, 0x0000, 0x0000, 0x0E60},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EE0},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EE8},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EEC},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EEE},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EEF},		
                                                  {0x0000, 0x0000, 0x0000, 0x0EFF},		
                                                  {0x0000, 0x0000, 0x0000, 0x0FFF},		
                                                  {0x0000, 0x0000, 0x0000, 0x1FFF},		
                                                  {0x0000, 0x0000, 0x0000, 0x3FFF},		
                                                  {0x0000, 0x0000, 0x0000, 0x7FFF},		
                                                  {0x0000, 0x0000, 0x0000, 0xFFFF}};	

const _Pattern_info SpiralLayers = {64,aSpiralLayers[0]};



const PROGMEM unsigned int aSnake[][4] = {{0x0088, 0x0000, 0x0000, 0x0000},		
                                          {0x0888, 0x0000, 0x0000, 0x0000},		
                                          {0x8888, 0x0000, 0x0000, 0x0000},		
                                          {0xC880, 0x0000, 0x0000, 0x0000},		
                                          {0xE800, 0x0000, 0x0000, 0x0000},		
                                          {0xE000, 0x2000, 0x0000, 0x0000},		
                                          {0x6000, 0x3000, 0x0000, 0x0000},		
                                          {0x2000, 0x3100, 0x0000, 0x0000},		
                                          {0x0000, 0x3110, 0x0000, 0x0000},		
                                          {0x0000, 0x1111, 0x0000, 0x0000},		
                                          {0x0000, 0x0113, 0x0000, 0x0000},		
                                          {0x0000, 0x0017, 0x0000, 0x0000},		
                                          {0x0000, 0x000F, 0x0000, 0x0000},		
                                          {0x0000, 0x000E, 0x0008, 0x0000},		
                                          {0x0000, 0x000C, 0x0088, 0x0000},		
                                          {0x0000, 0x0008, 0x00C8, 0x0000},		
                                          {0x0000, 0x0000, 0x00E8, 0x0000},		
                                          {0x0000, 0x0000, 0x00F0, 0x0000},		
                                          {0x0000, 0x0000, 0x0170, 0x0000},		
                                          {0x0000, 0x0000, 0x1130, 0x0000},		
                                          {0x0000, 0x0000, 0x1110, 0x1000},		
                                          {0x0000, 0x0000, 0x1100, 0x3000},		
                                          {0x0000, 0x0000, 0x1000, 0x7000},		
                                          {0x0000, 0x0000, 0x0000, 0xF000},		
                                          {0x0000, 0x0000, 0x0000, 0xE800},		
                                          {0x0000, 0x0000, 0x0000, 0xCC00},		
                                          {0x0000, 0x0000, 0x0000, 0x8E00},		
                                          {0x0000, 0x0000, 0x0000, 0x0F00},		
                                          {0x0000, 0x0000, 0x0100, 0x0700},		
                                          {0x0000, 0x0100, 0x0100, 0x0300},		
                                          {0x0100, 0x0100, 0x0100, 0x0100},		
                                          {0x1100, 0x0100, 0x0100, 0x0000}};	

const _Pattern_info Snake = {32,aSnake[0]};



const PROGMEM unsigned int aUpright[][4] = {{0xFFFF, 0x0000, 0x0000, 0x0000},	
                                            {0x7777, 0x8888, 0x0000, 0x0000},		
                                            {0x3333, 0x4444, 0x8888, 0x0000},		
                                            {0x1111, 0x2222, 0x4444, 0x8888},		
                                            {0x1111, 0x1111, 0x2222, 0x4444},		
                                            {0x1111, 0x1111, 0x1111, 0x2222},		
                                            {0x1111, 0x1111, 0x1111, 0x1111},		
                                            {0x1111, 0x1111, 0x1111, 0x2222},		
                                            {0x1111, 0x1111, 0x2222, 0x4444},
                                            {0x1111, 0x2222, 0x4444, 0x8888},
                                            {0x3333, 0x4444, 0x8888, 0x0000}};
                                    
const _Pattern_info Upright = {11,aUpright[0]};



const PROGMEM unsigned int aRandomFill[][4] = { {0x0000, 0x0000, 0x0000, 0x0000},
                                                {0x0420, 0x0000, 0x0000, 0x0000},		
                                                {0x0660, 0x0420, 0x0000, 0x0000},		
                                                {0x9669, 0x0660, 0x0420, 0x0000},		
                                                {0xD7EB, 0x9669, 0x0660, 0x0420},		
                                                {0xFFFF, 0xD7EB, 0x9669, 0x0660},		
                                                {0xFFFF, 0xFFFF, 0xD7EB, 0x9669},		
                                                {0xFFFF, 0xFFFF, 0xFFFF, 0xD7EB},		
                                                {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
                                                {0xFFFF, 0xFFFF, 0xFFFF, 0xD7EB},
                                                {0xFFFF, 0xFFFF, 0xD7EB, 0x9669},
                                                {0xFFFF, 0xD7EB, 0x9669, 0x0660},	
                                                {0xD7EB, 0x9669, 0x0660, 0x0420},
                                                {0x9669, 0x0660, 0x0420, 0x0000},	
                                                {0x0660, 0x0420, 0x0000, 0x0000},
                                                {0x0420, 0x0000, 0x0000, 0x0000}};	

const _Pattern_info RandomFill = {16,aRandomFill[0]};



const PROGMEM unsigned int aCube[][4] = { {0x0000, 0x0000, 0x0000, 0x0000},		
                                          {0x8000, 0x0000, 0x0000, 0x0000},		
                                          {0xCC00, 0xCC00, 0x0000, 0x0000},		
                                          {0xEAE0, 0xA0A0, 0xEAE0, 0x0000},	
                                          {0xF99F, 0x9009, 0x9009, 0xF99F},		
                                          {0x0000, 0x0757, 0x0055, 0x0757},			
                                          {0x0000, 0x0000, 0x0033, 0x0033},		
                                          {0x0000, 0x0000, 0x0000, 0x0001},
                                          {0x0000, 0x0000, 0x0033, 0x0033},
                                          {0x0000, 0x0757, 0x0055, 0x0757},		
                                          {0xF99F, 0x9009, 0x9009, 0xF99F},	
                                          {0xEAE0, 0xA0A0, 0xEAE0, 0x0000},
                                          {0xCC00, 0xCC00, 0x0000, 0x0000},
                                          {0x8000, 0x0000, 0x0000, 0x0000}};

const _Pattern_info Cube = {14,aCube[0]};												
#endif