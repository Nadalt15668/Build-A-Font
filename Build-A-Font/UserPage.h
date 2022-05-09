#pragma once
#include "Screen.h"
#include "Button.h"
#include "UserBoard.h"
#include "CharacterSet.h"
#include "MenuDialog.h"
#include "ExportingDialog.h"

using namespace sf;


class UserPage :
    public Screen
{
public:
    UserPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule,
        std::map<std::string, Screen*>& screens, Screen*& currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    module_ pythonModule;
    DrawingBoard* drawingBoard;
    std::map<std::string, Screen*>* screens;
    Screen** currentScreen;
    Button<DrawingBoard&>* btnClearBoard;
    Button<DrawingBoard&, CharacterSet&>* btnCaptureBoard;
    Button<MenuDialog**, ExportingDialog**, pybind11::module_&, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, std::string>* btnLaunchMenu;
    MenuDialog* menuDialog = nullptr;
    ExportingDialog* exportDialog = nullptr;
    Button<std::map<std::string, Screen*>&, Screen*&>* btnToStartPage;
    CharacterSet* characterSet;
    IShellItem** loadedProject;
};

