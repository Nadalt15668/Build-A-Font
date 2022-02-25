#include "Program.h"

//------------------------ BUTTON FUNCTIONS ------------------------
void ClearBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}
void CaptureBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Capture("file.png");
}
//------------------------------------------------------------------

Program::Program()
{
    currentWindow = new RenderWindow(sf::VideoMode(PROGRAM_DIM.x, PROGRAM_DIM.y), "SFML works!");
    drawingBoard = new DrawingBoard(currentWindow);
    pythonModule = module_::import("python"); // Importing the module from 'python.py'
    characterSet = new CharacterSet(*currentWindow, pythonModule);
    currentState = CHOOSE_CHARACTER;
    //------------------------------------------------------------
    //                          Buttons
    //                          -------
    btnClearBoard = new Button<DrawingBoard&>(currentWindow, Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_SIZE.x /2.2, (PROGRAM_DIM.y / 3) *1.65), &ClearBoard,
                                Vector2f(DEFAULT_BUTTON_SIZE.x / 1.3, 50));
    btnCaptureBoard = new Button<DrawingBoard&>(currentWindow, Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_SIZE.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65), &CaptureBoard,
        Vector2f(DEFAULT_BUTTON_SIZE.x / 1.3, 50));
    //------------------------------------------------------------
    btnClearBoard->AddText("CLEAR", DEFAULT_FONT, 30);
    btnCaptureBoard->AddText("CAPTURE", DEFAULT_FONT, 30);
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
    characterSet->Update(event, *drawingBoard);
}

void Program::RunStates()
{
    // MENU, CHOOSE_CHARACTER, DRAWING
    switch (currentState)
    {
    case 1:
        break;
    }
}

void Program::Draw()
{
    drawingBoard->Draw();
    characterSet->Draw(*currentWindow);
    DrawButtons();
}

void Program::UpdateButtons(Event event)
{
    btnClearBoard->Update(event, *drawingBoard);
    btnCaptureBoard->Update(event, *drawingBoard);
}

void Program::DrawButtons()
{
    btnClearBoard->Draw();
    btnCaptureBoard->Draw();
}

