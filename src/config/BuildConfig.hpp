#pragma once

//*==============================
//* Hardware
//*==============================
#define DISPLAY_TARGET_ST7735
// #define DISPLAY_TARGET_ST7789

#ifdef DISPLAY_TARGET_ST7735
    #define LCD_H_RES          (128)    // LCD horizontal resolution
    #define LCD_V_RES          (160)    // LCD vertical resolution
#else
    #define LCD_H_RES          (128)    // LCD horizontal resolution
    #define LCD_V_RES          (128)    // LCD vertical resolution
#endif

//*==============================
//* Logging
//*==============================

#define ENABLE_BUTTON_LOG
// #define ENABLE_DISPLAY_LOG
// #define ENABLE_EVENT_LOG
// #define ENABLE_FPS_LOG

//*==============================
//* Features
//*==============================

// #define ENABLE_ANIMATION
// #define ENABLE_TOUCH

//*==============================
//* Mesuring
//*==============================

#define ENABLE_MEASURE_SYS_INIT_TIME
#define ENABLE_MEASURE_MODULE_INIT_TIME