#include "Program.h"

//------------------------ BUTTON FUNCTIONS ------------------------

void ClearBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}

//------------------------------------------------------------------

Program::Program()
{
    currentWindow = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    drawingBoard = new DrawingBoard(currentWindow);
    //------------------------------------------------------------
    //                          Buttons
    //                          -------
    btnClearBoard = new Button<DrawingBoard&>(currentWindow, Vector2f(WIDTH / 2, (HEIGHT / 3) * 2), &ClearBoard);
    //------------------------------------------------------------
    btnClearBoard->AddText("CLEAR", DEFAULT_FONT, 30);
}

void Program::Run()
{
    while (currentWindow->isOpen())
    {
        sf::Event event;
        while (currentWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                currentWindow->close();
        }
        Update(event);
        currentWindow->clear(DEFAULT_GRAY_BGROUND);
        Draw();
        currentWindow->display();
    }
}

void Program::Update(Event& event)
{
    drawingBoard->Update(event);
    UpdateButtons(event);

}

void Program::Draw()
{
    DrawButtons();
    drawingBoard->Draw();
}

void Program::UpdateButtons(Event event)
{
    btnClearBoard->Update(event, *drawingBoard);
}

void Program::DrawButtons()
{
    btnClearBoard->Draw();
}
