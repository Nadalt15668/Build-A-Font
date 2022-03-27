#pragma once
#include "DrawingBoard.h"
class UserBoard :
    public DrawingBoard
{
public:
    UserBoard(RenderWindow* window);
    void Capture();
};

