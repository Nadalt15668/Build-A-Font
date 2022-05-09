#pragma once
#include <SFML/Graphics.hpp>
#include "AIPage.h"
#include "UserPage.h"
#include "Dialog.h"
#include "FileDialog.h"
#include "TextBox.h"
#include "Button.h"



typedef struct DrawingPagePars
{
    RenderWindow** window;
    module_** pythonModule;
    std::map<std::string, Screen*>** screens;
    Screen*** currentScreen;
    IShellItem** loadedProject;
}DrawingPagePars;

class StartProgramDialog :
    public Dialog
{
public:
    StartProgramDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, DrawingPagePars* parameters,
        std::string dialogTitle = "", Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    bool Update(Event& event);
    ~StartProgramDialog();

private:
    sf::Text* sttcOr;
    sf::Text* sttcStartNewProj;
    sf::Text* chosenFileName;
    Button<std::string&, IShellItem**, sf::Text*&>* btnChooseFile;
    Button<std::string&, IShellItem**, sf::Text*&>* btnCancelChoice;
    Button<DrawingPagePars*>* btnUserProgram;
    Button<DrawingPagePars*>* btnAIProgram;
    DrawingPagePars* parameters;
    std::string filePath;
};

