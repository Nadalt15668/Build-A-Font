#pragma once
#include "UIElement.h"
#include "Screen.h"
#include "Button.h"

using namespace sf;
using namespace std;

#define BAR_THICKNESS 20
#define DEFAULT_BAR_COLOR Color(60, 60, 60)

class Dialog
{
public:
    Dialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor);
    virtual void Draw() = 0;
    virtual void Move(Vector2f offset) = 0;
    void OpenDialog(bool& isInteractable);
    Vector2f CalculateStartingOffset();
    void CheckForDragging(Event& event);
    bool isDialogOpen() { return this->isOpen; };
    ~Dialog();
private:
    void ResetLastPos() { this->lastMouseHeldPos = Vector2f(0, 0); };
protected:
    void MoveEssentials(Vector2f offset);
    void DrawEssentials();
    Screen* parentScreen;
    RenderWindow* window;
    RectangleShape* dialogBar;
    RectangleShape* dialogBground;
    Vector2f dialogPos;
    sf::Text* dialogTitle;
    Button<bool&, bool&>* btnCloseDialog;
    bool isOpen;
    Vector2f lastMouseHeldPos; // For dragging purposes 
};

