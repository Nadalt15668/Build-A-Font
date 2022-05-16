#pragma once
// ----- Dimensions -----
#define PROGRAM_DIM Vector2f(1280, 720)
#define DRAWING_DIM Vector2f(128, 128)
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
#define NXT_CHR_PGE_POS Vector2f(1220, (PROGRAM_DIM.y / 15) * 11.8)
#define PRVS_CHR_PGE_POS Vector2f(60, (PROGRAM_DIM.y / 15) * 11.8)
#define LOGO_POS Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.x / 7)
#define TITLE_POS Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.x / 3.5)
#define CAPTURE_POS Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65)
#define CLEAR_POS Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65)
#define TOP_LEFT_BTN_POS Vector2f(PROGRAM_DIM.x / 17, PROGRAM_DIM.y / 15)
// ----- Sizes -----
#define BRUSH_THICKNESS 5
#define TEXTBOX_TEXT_SIZE 25
// ----- Colors -----
#define DEFAULT_GRAY_BGROUND Color(211, 211, 211)
#define DEFAULT_DIALOG_COLOR Color(240, 240, 240)
#define GRAY_SUB 30
#define DEFAULT_BUTTON_COLOR Color(143, 143, 143)
#define HINT_TEXT_COLOR Color(191, 191, 191)
#define SELECTED_TEXTBOX_COLOR Color(159,193,49)
// ----- Files ------
#define BLANK_TEMPLATE "Templates/blank.png"
#define BLANK_CHARACTER "CharacterDrawings/blank.png"
#define DEFAULT_FONTPATH "Fonts/Teko-Bold.ttf"
#define PROJECT_LOGO "Assets/project_logo.png"
#define TRASH_CAN "Assets/trash_can.png"
#define CONV_SCRIPT "conv_script.bat"
#define SVGS2TTF "svgs2ttf.bat"
#define POTRACE_LOC "C:\\potrace-1.16.win64\\potrace.exe"
#define MENU "Assets/menu.png"
#define UNDO "Assets/undo.png"
#define BACK_ARROW "Assets/back_arrow.png"
// Neural Network:
#define SAVE_FILE "datasave.dat"
#define UPLOAD_FILE "datasave.dat"
#define TRAIN_DATA "Dataset/train_data.idx3-ubyte"
#define TRAIN_LABEL "Dataset/train_labels.idx1-ubyte"
#define TEST_DATA "Dataset/test_data.idx3-ubyte"
#define TEST_LABEL "Dataset/test_labels.idx1-ubyte"
// ----- Directories -----
#define BINARIES "CharacterDrawings/Binaries/"
#define DRAWINGS "CharacterDrawings/Drawings/"
#define TEMPLATES_CHARACTERS "Templates/CharacterTemplates/"
#define TEMPORARY_DIR (std::string)"./Temps"
#define TEMPORARY_DIR_BAT (std::string)".\\Temps"
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
#define CHARS_DRAWING_PAGE "DrawingPage"
#define STARTING_PAGE "StartPage"
// ----- Neural Network -----
#define DRAWING_SIZE 28
#define HIDDEN_LAYERS 3
#define NODES_IN_HIDDEN 20
#define NODES_IN_INPUT DRAWING_SIZE * DRAWING_SIZE
// Nodes for each pixel in the input picture (28X28)
#define NODES_IN_OUTPUT 10
// Nodes for each possible digit
#define SUBSET_SIZE 10
#define NUM_OF_EPOCHS 3
#define LEARNING_RATE 3
// ----- Other -----
#define FILE_DELIM "\n"
