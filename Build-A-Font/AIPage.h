#pragma once
#include "Screen.h"
#include "Button.h"
#include "AIBoard.h"
#include "CharacterSet.h"
#include "MenuDialog.h"

using namespace sf;
using namespace std;

class AIPage :
    public Screen
{
public:
    AIPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule,
        map<string, Screen*>& screens, Screen*& currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    module_ pythonModule;
    AIBoard* drawingBoard;
    map<string, Screen*>* screens;
    Screen** currentScreen;
    Button<DrawingBoard&>* btnClearBoard;
    Button<DrawingBoard&, CharacterSet&>* btnCaptChar;
    Button<AIBoard&, CharacterSet&>* btnCaptNum;
    Button<AIBoard&, CharacterSet&>* btnUndoNumbers;
    Button<MenuDialog**, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, string>* btnLaunchMenu;
    MenuDialog* menuDialog = nullptr;
    Button<map<string, Screen*>&, Screen*&>* btnToStartPage;
    CharacterSet* characterSet;
    IShellItem** loadedProject;
};

