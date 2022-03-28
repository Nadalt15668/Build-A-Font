#pragma once
// ----- Dimensions -----
#define PROGRAM_DIM Vector2f(1280, 720)
#define DRAWING_DIM Vector2f(199, 216)
#define CHARACTER_DIM Vector2f(199, 216)
#define PAGE_BTN_DIM Vector2f(50, 50)
#define DEFAULT_BUTTON_DIM Vector2f(180, 90)
#define DEFAULT_TEXTBOX_DIM Vector2f(180, 40)
// ----- Positions -----
#define DRAWING_POS Vector2f(PROGRAM_DIM.x /2, PROGRAM_DIM.y / 3)
// If changing quantity, also change udner - Character Set - CHARACTERS_IN_ROW
#define CHARACTER_X_AXIS {150, 290, 430, 570, 710, 850, 990, 1130} 
// If changing quantity, also change udner - Character Set - NUM_OF_ROWS
#define CHARACTER_Y_AXIS {(PROGRAM_DIM.y / 5) * 3.5f, (PROGRAM_DIM.y / 5) * 3.5f + PROGRAM_DIM.y / 6} 
#define NXT_PGE_POS Vector2f(1220, (PROGRAM_DIM.y / 15) * 12)
#define LST_PGE_POS Vector2f(60, (PROGRAM_DIM.y / 15) * 12)
#define LOGO_POS Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.x / 7)
#define TITLE_POS Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.x / 3.5)
#define CAPTURE_POS Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65)
#define CLEAR_POS Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65)
#define USER_PROG_BTN_POS Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_DIM.x / 1.5, (PROGRAM_DIM.y / 1.5))
#define AI_PROG_BTN_POS Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_DIM.x / 1.5, (PROGRAM_DIM.y / 1.5))
#define TOP_LEFT_BTN_POS Vector2f(PROGRAM_DIM.x / 17, PROGRAM_DIM.y / 15)
// ----- Sizes -----
#define BRUSH_THICKNESS 4
#define TEXTBOX_TEXT_SIZE 25
// ----- Colors -----
#define DEFAULT_GRAY_BGROUND Color(211, 211, 211)
#define GRAY_SUB 30
#define DEFAULT_BUTTON_COLOR Color(143, 143, 143)
#define HINT_TEXT_COLOR Color(191, 191, 191)
#define SELECTED_TEXTBOX_COLOR Color(159,193,49)
// ----- Files ------
#define BLANK_TEMPLATE "Templates/blank.png"
#define BLANK_CHARACTER "CharacterDrawings/blank.png"
#define DEFAULT_FONTPATH "Fonts/default.ttf"
#define PROJECT_LOGO "Assets/project_logo.png"
// ----- Directories -----
#define BINARIES "CharacterDrawings/Binaries/"
#define DRAWINGS "CharacterDrawings/Drawings/"
#define TEMPLATES_CHARACTERS "Templates/CharacterTemplates/"
#define TEMPLATES_DRAWING_BOARD 
// ----- Printed Messages -----
#define FILE_SAVED_TO "File successfully saved to "
#define ERROR_WHILE_OPENING "An error has accured while opening the file"
#define ERROR_WHILE_LOADING "An error has accured while loading the file"
#define ERROR_ACCURED "An error has accured"
// ----- Characet Set -----
#define CHARACTERS_IN_PAGE 16
#define CHARACTERS_IN_ROW 8
#define CHARACTERS_IN_SET 52
#define NUMBERS_IN_SET 10
#define SYMBOLS_IN_SET 18
#define TOTALS_IN_SET 80
#define NUM_OF_PAGES 5
#define NUM_OF_ROWS 2
// ----- Pages Names -----
#define CHARS_DRAWING_PAGE "CharsDrawingPage"
#define STARTING_PAGE "StartPage"
// ----- Other -----
#define FILE_TYPE ".txt"