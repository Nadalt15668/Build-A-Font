#define _CRT_SECURE_NO_WARNINGS
#include "UserBoard.h"

UserBoard::UserBoard(RenderWindow& window,
    Vector2f center,
    Vector2f size,
    Vector2f vpSizeRatio,
    Vector2f vpLocationRatio) :
    DrawingBoard(window, center, size, vpSizeRatio, vpLocationRatio)
{
}

void UserBoard::Capture(std::map<std::string, std::vector<RectangleShape>*>* charactersData)
{
    (*charactersData)[this->characterName]->clear();
    for (auto line : this->mainLines)
        (*charactersData)[this->characterName]->push_back(line);
}
