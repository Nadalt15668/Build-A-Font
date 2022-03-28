#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Button.h"

using namespace sf;
using namespace std;

class TextBox :
    public UIElement
{
public:
    TextBox(RenderWindow& window, Vector2f pos, Vector2f size, string hintText, int textSize, string fontPath = DEFAULT_FONTPATH);
    void Draw(RenderWindow& window);
    void Update(Event& event);
private:
    Font* font;
    int textSize;
    string filledText;
    string hintText;
    Button<Vector2f>* btnTextBox;
};

