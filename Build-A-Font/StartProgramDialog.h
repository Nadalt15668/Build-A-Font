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
}DrawingPagePars;

class StartProgramDialog :
    public Dialog
{
public:
    StartProgramDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, DrawingPagePars* parameters,
        string dialogTitle = "", Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    void Update(Event& event);

private:
    sf::Text* sttcNewFileName;
    sf::Text* sttcOr;
    TextBox* newFileName;
    sf::Text* chosenFileName;
    Button<string&, sf::Text*&>* btnChooseFile;
    Button<string&, sf::Text*&>* btnCancelChoice;
    Button<DrawingPagePars*>* btnUserProgram;
    Button<DrawingPagePars*>* btnAIProgram;
    DrawingPagePars* parameters;
    string filePath;
};

