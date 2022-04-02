#pragma once
#include "UIElement.h"
#include "Button.h"

using namespace sf;
using namespace std;

#define BAR_THICKNESS 20
#define DEFAULT_BAR_COLOR Color(60, 60, 60)

class Dialog
{
public:
    Dialog(RenderWindow& window, Vector2f size, string dialogTitle, Color bgroundColor);
    virtual void Draw() = 0;
    bool isDialogOpen() { return this->isOpen; };
protected:
    void DrawEssentials();
    RenderWindow* window;
    RectangleShape* bar;
    RectangleShape* dialogBground;
    Vector2f dialogPos;
    sf::Text* dialogTitle;
    Button<bool&>* btnCloseDialog;
    bool isOpen;
    Vector2f lastMouseHeldPos; // For dragging purposes 
};

