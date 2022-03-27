#pragma once
#include "Screen.h"
#include "Button.h"
#include "UserBoard.h"
#include "CharacterSet.h"

using namespace sf;
using namespace std;

class CharsDrawingPage :
    public Screen
{
public:
    CharsDrawingPage(RenderWindow& window, module_& pythonModule);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    module_ pythonModule;
    DrawingBoard* drawingBoard;
    Button<DrawingBoard&>* btnClearBoard;
    Button<DrawingBoard&, CharacterSet&>* btnCaptureBoard;
    CharacterSet* characterSet;
};

