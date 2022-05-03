#pragma once
#include "Screen.h"
#include "Button.h"
#include "UserBoard.h"
#include "CharacterSet.h"
#include "MenuDialog.h"
#include "ExportingDialog.h"

using namespace sf;
using namespace std;

class UserPage :
    public Screen
{
public:
    UserPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule,
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
    Button<MenuDialog**, ExportingDialog**, pybind11::module_&, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, string>* btnLaunchMenu;
    MenuDialog* menuDialog = nullptr;
    ExportingDialog* exportDialog = nullptr;
    Button<map<string, Screen*>&, Screen*&>* btnToStartPage;
    CharacterSet* characterSet;
    IShellItem** loadedProject;
};

