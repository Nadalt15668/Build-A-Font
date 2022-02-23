#pragma once
// ----- Dimensions -----
#define PROGRAM_DIM Vector2f(1280, 720)
#define DRAWING_DIM Vector2f(199, 216)
#define CHARACTER_DIM Vector2f(199, 216)
// ----- Positions -----
#define DRAWING_POS Vector2f(PROGRAM_DIM.x /2, PROGRAM_DIM.y / 3)
#define CHARACTER_X_AXIS {150, 290, 430, 570, 710, 850, 990, 1130}
#define CHARACTER_Y_AXIS {(PROGRAM_DIM.y / 5) * 3.5f, (PROGRAM_DIM.y / 5) * 3.5f + PROGRAM_DIM.y / 6}
// ----- Sizes -----
#define BRUSH_THICKNESS 4
#define DEFAULT_BUTTON_SIZE Vector2f(180, 90)
// ----- Colors -----
#define DEFAULT_GRAY_BGROUND Color(211, 211, 211)
#define GRAY_SUB 30
#define DEFAULT_BUTTON_COLOR Color(143, 143, 143)// ----- Files ------
#define BLANK_TEMPLATE "Templates/blank.png"
#define DEFAULT_FONT "Fonts/default.ttf"
// ----- Other -----
