#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Constants.h"
#include "CharsDrawingPage.h"

using namespace sf;
using namespace std;

class StartPage :
    public Screen
{
public:
    StartPage(RenderWindow& window, module_& pythonModule, map<string, Screen*>& screens, Screen* currentScreen);
    void Draw();
    void Update(Event& event);
private:
    RenderWindow* window;
    sf::Sprite logo;
    sf::Text title;
    module_* pythonModule;
    map<string, Screen*>* screens;
    Screen* currentScreen;
    Button<RenderWindow&, module_&, map<string, Screen*>&, Screen*>* userProgamBtn;
    Button<RenderWindow&, module_&, map<string, Screen*>&, Screen*>* aiProgamBtn;
};

