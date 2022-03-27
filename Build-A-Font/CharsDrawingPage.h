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
    CharsDrawingPage(RenderWindow& window, bool isUser, module_& pythonModule,
        map<string, Screen*>& screens, Screen*& currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    module_ pythonModule;
    DrawingBoard* drawingBoard;
    map<string, Screen*>* screens;
    Screen** currentScreen;
    Button<DrawingBoard&>* btnClearBoard;
    Button<DrawingBoard&, CharacterSet&>* btnCaptureBoard;
    Button<map<string, Screen*>&, Screen*&>* btnToStartPage;
    CharacterSet* characterSet;
};

