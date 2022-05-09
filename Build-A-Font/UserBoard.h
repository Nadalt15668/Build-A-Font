#pragma once
#include "DrawingBoard.h"

class UserBoard :
    public DrawingBoard
{
public:
    UserBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocationRatio);
    void Capture(std::map<std::string, std::vector<RectangleShape>*>* charactersData);
private:
};

