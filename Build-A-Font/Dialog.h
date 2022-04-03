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
    virtual void Move(Vector2f offset) = 0;
    void OpenDialog();
    void CheckForDragging(Event& event);
    bool isDialogOpen() { return this->isOpen; };
private:
    void ResetLastPos() { this->lastMouseHeldPos = Vector2f(0, 0); };
protected:
    void MoveEssentials(Vector2f offset);
    void DrawEssentials();
    RenderWindow* window;
    RectangleShape* dialogBar;
    RectangleShape* dialogBground;
    Vector2f dialogPos;
    sf::Text* dialogTitle;
    Button<bool&>* btnCloseDialog;
    bool isOpen;
    Vector2f lastMouseHeldPos; // For dragging purposes 
};

