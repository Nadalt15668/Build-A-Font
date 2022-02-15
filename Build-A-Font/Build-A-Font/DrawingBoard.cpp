#include "DrawingBoard.h"

void SetBlankBackground(RectangleShape* board)
{
    Texture* blankTex = new Texture();
    blankTex->loadFromFile(BLANK_TEMPLATE);
    board->setTexture(blankTex);

}

bool CheckBorders(Vector2f worldPos)
{
    if (!(worldPos.x > DRAWING_POS.x - DRAWING_DIM.x / 2 && worldPos.x < DRAWING_POS.x + DRAWING_DIM.x / 2) ||
        !(worldPos.y > DRAWING_POS.y - DRAWING_DIM.y / 2 && worldPos.y < DRAWING_POS.y + DRAWING_DIM.y / 2))
        return false;
    return true;
}

DrawingBoard::DrawingBoard(RenderWindow* window)
{
    this->baseWindow = window;
    // -------------------- Drawing Final Texture (for .png later) -------------------- 
    drawingTex.create(DRAWING_DIM.x, DRAWING_DIM.y);
    drawingTex.clear(Color::Transparent);
    // ----------------- Drawing View (The view that actually gets drawn) -----------------
    drawingView.setCenter(Vector2f(PROGRAM_DIM.x + (DRAWING_DIM.x / 2), (DRAWING_DIM.y / 2)));
    drawingView.setSize(DRAWING_DIM.x + 2, DRAWING_DIM.y + 2);
    drawingView.setViewport(FloatRect(0.5 - (DRAWING_DIM.x / 2) / PROGRAM_DIM.x,
                            0.333 - (DRAWING_DIM.y / 2) / PROGRAM_DIM.y,
                            DRAWING_DIM.x / PROGRAM_DIM.x, DRAWING_DIM.y / PROGRAM_DIM.y));
    // ------ View Template (Background of the field, serves as drawing template) -----
    viewTemplate.setSize(DRAWING_DIM);
    viewTemplate.setOrigin(viewTemplate.getLocalBounds().width / 2 , viewTemplate.getLocalBounds().height / 2);
    viewTemplate.setPosition(Vector2f(PROGRAM_DIM.x + (DRAWING_DIM.x / 2), (DRAWING_DIM.y / 2)));
    SetBlankBackground(&viewTemplate);
    // ---------------------------------------------------------------------------------
}

void DrawingBoard::Update(Event& event)
{
    // ----------------- Current position of mouse in our window -----------------
    Vector2i pixelPos = sf::Mouse::getPosition(*baseWindow);
    Vector2f worldPos = baseWindow->mapPixelToCoords(pixelPos);
    // ---------------------------------------------------------------------------
    if (event.type == Event::MouseButtonReleased || !CheckBorders(worldPos))
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

void DrawingBoard::Capture(string filename)
{
    if (drawingTex.getTexture().copyToImage().saveToFile("file.png"))
    {
        cout << "Screenshot saved to " << filename << endl;
    }
    else
        cout << "An error has accured" << endl;
}

void DrawingBoard::RemoveBackground()
{
    viewTemplate.setTexture(NULL);
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
    mainLines.push_back(newLine);
}

void DrawingBoard::Draw()
{
    texLines = mainLines;
    viewLines = mainLines;
    baseWindow->setView(drawingView);
    baseWindow->draw(viewTemplate);
    for (int i = 0; i < mainLines.size(); i++)
    {
        texLines[i].move(-DRAWING_POS.x + DRAWING_DIM.x / 2, -DRAWING_POS.y + DRAWING_DIM.y / 2);
        viewLines[i].move(Vector2f(PROGRAM_DIM.x / 2 + DRAWING_DIM.x / 2, (DRAWING_DIM.y / 2) - (PROGRAM_DIM.y / 3)));
        drawingTex.draw(texLines[i]);
        baseWindow->draw(viewLines[i]);
    }
    drawingTex.display();
    baseWindow->setView(baseWindow->getDefaultView());
}

void DrawingBoard::Clear()
{
    mainLines.clear();
    texLines.clear();
    viewLines.clear();
    drawingTex.clear(Color::Transparent);
}
