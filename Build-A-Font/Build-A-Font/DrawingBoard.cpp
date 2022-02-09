#include "DrawingBoard.h"

bool CheckBorders(Vector2f worldPos)
{
    if (!(worldPos.x > DRAWING_POS.x - DRAWING_SIZE.x / 2 && worldPos.x < DRAWING_POS.x + DRAWING_SIZE.x / 2) ||
        !(worldPos.y > DRAWING_POS.y - DRAWING_SIZE.y / 2 && worldPos.y < DRAWING_POS.y + DRAWING_SIZE.y / 2))
        return false;
    return true;
}

DrawingBoard::DrawingBoard(RenderWindow* window)
{
	this->window = window;
    board.setFillColor(Color::White);
    board.setOutlineColor(Color::Black);
    board.setOutlineThickness(2);
    board.setSize(DRAWING_SIZE);
    board.setOrigin(board.getLocalBounds().width / 2, board.getLocalBounds().height / 2);
    board.setPosition(DRAWING_POS);
}

void DrawingBoard::Update(Event& event)
{
    Vector2i pixelPos = sf::Mouse::getPosition(*window);
    Vector2f worldPos = window->mapPixelToCoords(pixelPos); // Current position of mouse in our window

    if (event.type == Event::MouseButtonReleased ||
        (Mouse::isButtonPressed(Mouse::Left) &&  !CheckBorders(worldPos)))
        brush.ResetPositions();
    if (Mouse::isButtonPressed(Mouse::Left) &&
        (brush.curPos.x == NULL || brush.curPos.y == NULL) &&
        CheckBorders(worldPos))
    {
        brush.curPos.x = worldPos.x;
        brush.curPos.y = worldPos.y;
    }
    else if (Mouse::isButtonPressed(Mouse::Left) &&
        (worldPos.x != brush.curPos.x || worldPos.y != brush.curPos.y) &&
        CheckBorders(worldPos))
    {
        brush.NewPosition(worldPos);
        CreateLine();
    }
}

void DrawingBoard::CreateLine()
{
    float length = brush.CalculateLength() + 4;
    float angle = brush.CalculateAngle();
    RectangleShape newLine;
    newLine.setOrigin(Vector2f(0, BRUSH_THICKNESS / 2));
    newLine.setRotation(angle);
    newLine.setFillColor(Color::Black);
    newLine.setPosition(brush.prevPos);
    newLine.setSize(Vector2f(BRUSH_THICKNESS, length));
    lines.push_back(newLine);
}

void DrawingBoard::Draw()
{
    window->draw(board);
    for (int i = 0; i < lines.size(); i++)
        window->draw(lines[i]);
}

void DrawingBoard::Clear()
{
    lines.clear();
}
