#pragma once
#include "DrawingBoard.h"

class UserBoard :
    public DrawingBoard
{
public:
    UserBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocationRatio);
    void Capture(map<string, vector<RectangleShape>*>* charactersData);
private:
};

