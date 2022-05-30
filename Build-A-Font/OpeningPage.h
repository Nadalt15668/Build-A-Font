#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "StartProgramDialog.h"
#include "Constants.h"
#include "UserPage.h"
#include "Animation.h"

using namespace sf;

class OpeningPage :
    public Screen
{
public:
    OpeningPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule, std::map<std::string, Screen*>& screens, Screen*& currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    sf::Sprite logo;
    sf::Text title;
    module_* pythonModule;
    std::map<std::string, Screen*>* screens;
    Screen** currentScreen;
    Button<StartProgramDialog*&, IShellItem*&, RenderWindow*&, module_*&, std::map<std::string, Screen*>*&, Screen**&>* btnStartProgram;
    Button<>* btnQuitProgram;
    StartProgramDialog* startDialog = nullptr;
    IShellItem* loadedProject;
};

