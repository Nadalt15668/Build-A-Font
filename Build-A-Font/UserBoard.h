#pragma once
#include "DrawingBoard.h"
#define FILE_SAVED_TO "File successfully saved to "
#define ERROR_WHILE_OPENING "An error has accured while opening the file"
#define ERROR_WHILE_LOADING "An error has accured while loading the file"
#define ERROR_ACCURED "An error has accured"
#define BINARIES "CharacterDrawings/Binaries/"
#define DRAWINGS "CharacterDrawings/Drawings/"
#define FILE_TYPE ".txt"

class UserBoard :
    public DrawingBoard
{
public:
    UserBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocationRatio);
    void Capture(map<string, vector<RectangleShape>*>* charactersData);
private:
};

