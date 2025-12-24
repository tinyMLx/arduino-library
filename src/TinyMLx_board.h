
#pragma once

#ifdef USE_TinyMLx_custom_board
#include "TinyMLx_custom_board.h"
#else

#define OV7670_VSYNC 8
#define OV7670_HREF  A1
#define OV7670_PLK   A0
#define OV7670_XCLK  9
#define OV7670_D0    10
#define OV7670_D1    1
#define OV7670_D2    0
#define OV7670_D3    2
#define OV7670_D4    3
#define OV7670_D5    5
#define OV7670_D6    6
#define OV7670_D7    4

#define BUTTON_PIN 13

#endif