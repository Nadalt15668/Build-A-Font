#pragma once
#include <SFML/Graphics.hpp>
#include "CharsDrawingPage.h"
#include "Dialog.h"
#include "FileDialog.h"
#include "TextBox.h"
#include "Button.h"

using namespace std;
using namespace sf;

typedef struct DrawingPagePars
{
    RenderWindow** window;
    module_** pythonModule;
    map<string, Screen*>** screens;
    Screen*** currentScreen;
    IShellItem** chosenItem;
}DrawingPagePars;

class StartProgramDialog :
    public Dialog
{
public:
    StartProgramDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, DrawingPagePars* parameters,
        string dialogTitle = "", Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    bool Update(Event& event);
    ~StartProgramDialog();

private:
    sf::Text* sttcOr;
    sf::Text* sttcStartNewProj;
    sf::Text* chosenFileName;
    Button<string&, IShellItem**, sf::Text*&>* btnChooseFile;
    Button<string&, IShellItem**, sf::Text*&>* btnCancelChoice;
    Button<DrawingPagePars*>* btnUserProgram;
    Button<DrawingPagePars*>* btnAIProgram;
    DrawingPagePars* parameters;
    string filePath;
};

