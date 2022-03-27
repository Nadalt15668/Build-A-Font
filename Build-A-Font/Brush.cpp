#include "Brush.h"

Brush::Brush()
{
    prevPos.x = NULL;
    prevPos.y = NULL;
    curPos.x = NULL;
    curPos.y = NULL;
}

//-----------------------------------------------------------------
//                      Calculate Length
//                      ----------------
// 
// Calculates the length between the previous position of the mouse
// and its current position.
//-----------------------------------------------------------------
float Brush::CalculateLength()
{
    return sqrt((prevPos.x - curPos.x) * (prevPos.x - curPos.x) +
        (prevPos.y - curPos.y) * (prevPos.y - curPos.y));
}

//-----------------------------------------------------------------
//                        Calculate Angle
//                        ----------------
// 
// Calculates the angle between the previous position of the mouse
// and its current position.
// Doing so by calculating the inverse tangent of the adjacent and
// opposite sides of a triangle created with the two points.
// Then checks the direction of the drawn line in order to rotate
// the drawn rectangle correctly. 
//-----------------------------------------------------------------
float Brush::CalculateAngle()
{
    float adjacentSide = curPos.x - prevPos.x;
    float oppositeSide = curPos.y - prevPos.y;
    if (adjacentSide != 0)
    {
        float finalAngle = atan(abs(oppositeSide) / abs(adjacentSide)) * (180 / M_PI);

        if (adjacentSide < 0 && oppositeSide < 0 ||
            adjacentSide > 0 && oppositeSide > 0) // From top left to bottom right or the opposite
            finalAngle += (adjacentSide > 0) ? -90 : 90;

        if (adjacentSide < 0 && oppositeSide > 0) // From top right to bottom left
            finalAngle = -finalAngle + 90;
        if (adjacentSide > 0 && oppositeSide < 0) // From bottom left to top right
            finalAngle = -finalAngle - 90;

        if (oppositeSide == 0) // From left to right or the opposite
            finalAngle = (adjacentSide > 0) ? -90 : 90;

        return finalAngle;
    }
    return (oppositeSide > 0) ? 0 : 180; // From top to bottom or the opposite
}

// Resets the previous and current saved positions of the mouse
void Brush::ResetPositions()
{
    prevPos.x = 0;
    prevPos.y = 0;
    curPos.x = 0;
    curPos.y = 0;
}

// Sets a new current position and changes the previous position to the last current one
void Brush::NewPosition(Vector2f newPos)
{
    prevPos.x = curPos.x;
    prevPos.y = curPos.y;
    curPos.x = newPos.x;
    curPos.y = newPos.y;
}
