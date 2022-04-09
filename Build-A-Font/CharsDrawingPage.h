#pragma once
#include "Screen.h"
#include "Button.h"
#include "UserBoard.h"
#include "CharacterSet.h"
#include "MenuDialog.h"

using namespace sf;
using namespace std;

class CharsDrawingPage :
    public Screen
{
public:
    CharsDrawingPage(RenderWindow& window, IShellItem** loadedProject, bool isUser, module_& pythonModule,
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
    Button<MenuDialog**, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, string>* btnLaunchMenu;
    MenuDialog* menuDialog = nullptr;
    Button<map<string, Screen*>&, Screen*&>* btnToStartPage;
    CharacterSet* characterSet;
    IShellItem** loadedProject;
};

