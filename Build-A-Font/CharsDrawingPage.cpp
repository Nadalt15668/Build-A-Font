#include "CharsDrawingPage.h"

void ClearBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}
void CaptureBoard(DrawingBoard& drawingBoard, CharacterSet& characterSet)
{
    drawingBoard.Capture();
    characterSet.LoadCharactersData();
}

CharsDrawingPage::CharsDrawingPage(RenderWindow& window, module_& pythonModule) 
    : Screen()
{
    this->window = &window;
    if (1)
        drawingBoard = new UserBoard
        (
            window,
            Vector2f(PROGRAM_DIM.x + (DRAWING_DIM.x / 2),
                (DRAWING_DIM.y / 2)),
            Vector2f(DRAWING_DIM.x, DRAWING_DIM.y),
            Vector2f(DRAWING_DIM.x / PROGRAM_DIM.x,
                DRAWING_DIM.y / PROGRAM_DIM.y),
            Vector2f(0.5 - (DRAWING_DIM.x / 2) / PROGRAM_DIM.x,
                0.333 - (DRAWING_DIM.y / 2) / PROGRAM_DIM.y)
        );
    else {/*Anitiating AIBoard Instead*/ }
    characterSet = new CharacterSet(window, pythonModule);
    characterSet->LoadCharactersData();
    btnClearBoard = new Button<DrawingBoard&>(window, Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65), &ClearBoard,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnCaptureBoard = new Button<DrawingBoard&, CharacterSet&>(window, Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_DIM.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65), &CaptureBoard,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnClearBoard->AddText("CLEAR", 30);
    btnCaptureBoard->AddText("CAPTURE", 30);
}

void CharsDrawingPage::Draw()
{
    this->drawingBoard->Draw();
    this->btnCaptureBoard->Draw(*this->window);
    this->btnClearBoard->Draw(*this->window);
    this->characterSet->Draw(*this->window);
}

void CharsDrawingPage::Update(Event& event)
{
    drawingBoard->Update(event);
    btnCaptureBoard->Update(event, *this->drawingBoard, *this->characterSet);
    btnClearBoard->Update(event, *this->drawingBoard);
    characterSet->Update(event, *this->drawingBoard);
}
