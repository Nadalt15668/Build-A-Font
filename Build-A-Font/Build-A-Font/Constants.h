#pragma once
// ----- Dimensions -----
#define PROGRAM_DIM Vector2f(1280, 720)
#define DRAWING_DIM Vector2f(199, 216)
#define CHARACTER_DIM Vector2f(199, 216)
#define PAGE_BTN_DIM Vector2f(50, 50)
// ----- Positions -----
#define DRAWING_POS Vector2f(PROGRAM_DIM.x /2, PROGRAM_DIM.y / 3)
// If changing quantity, also change udner - Character Set - CHARACTERS_IN_ROW
#define CHARACTER_X_AXIS {150, 290, 430, 570, 710, 850, 990, 1130} 
// If changing quantity, also change udner - Character Set - NUM_OF_ROWS
#define CHARACTER_Y_AXIS {(PROGRAM_DIM.y / 5) * 3.5f, (PROGRAM_DIM.y / 5) * 3.5f + PROGRAM_DIM.y / 6} 
#define NXT_PGE_POS Vector2f(1220, (PROGRAM_DIM.y / 15) * 12)
#define LST_PGE_POS Vector2f(60, (PROGRAM_DIM.y / 15) * 12)
// ----- Sizes -----
#define BRUSH_THICKNESS 4
#define DEFAULT_BUTTON_SIZE Vector2f(180, 90)
// ----- Colors -----
#define DEFAULT_GRAY_BGROUND Color(211, 211, 211)
#define GRAY_SUB 30
#define DEFAULT_BUTTON_COLOR Color(143, 143, 143)// ----- Files ------
#define BLANK_TEMPLATE "Templates/blank.png"
#define DEFAULT_FONT "Fonts/default.ttf"
// ----- Characet Set -----
#define CHARACTERS_IN_PAGE 16
#define CHARACTERS_IN_ROW 8
#define CHARACTERS_IN_SET 52
#define NUMBERS_IN_SET 10
#define SYMBOLS_IN_SET 18
#define TOTALS_IN_SET 80
#define NUM_OF_PAGES 5
#define NUM_OF_ROWS 2
// ----- Other -----
