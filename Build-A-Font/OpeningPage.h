#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "StartProgramDialog.h"
#include "Constants.h"
#include "CharsDrawingPage.h"

using namespace sf;
using namespace std;

class OpeningPage :
    public Screen
{
public:
    OpeningPage(RenderWindow& window, IShellItem** chosenItem, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    sf::Sprite logo;
    sf::Text title;
    module_* pythonModule;
    map<string, Screen*>* screens;
    Screen** currentScreen;
    Button<StartProgramDialog*&, IShellItem**, RenderWindow*&, module_*&, map<string, Screen*>*&, Screen**&>* btnStartProgram;
    Button<>* btnQuitProgram;
    StartProgramDialog* dialogTest = nullptr;
    IShellItem** chosenItem;
};

