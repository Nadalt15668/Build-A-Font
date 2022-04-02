#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Button.h"

using namespace sf;
using namespace std;

#define BACKSPACE 8
#define ELAPSED_TIME_FOR_INPUT 0.3
#define ELAPSED_TIME_FOR_BACKSPACE 0.2
#define CHARARCTER_INPUT static_cast<char>(event.text.unicode)

class TextBox :
    public UIElement
{
public:
    TextBox(RenderWindow& window, Vector2f pos, Vector2f size, string hintText, int textSize, string fontPath = DEFAULT_FONTPATH);
    void Draw(RenderWindow& window);
    void Update(Event& event);
    string GetText() { return this->totalText; };
private:
    RenderWindow* window;
    Font* font;
    int numOfShownCharacters;
    int textSize;
    string shownText = ""; // The text that is actually shown
    string totalText = ""; // The total written text
    string hintText = ""; // A hint text of the textbox
    Button<bool&>* btnTextBox;
    bool isWritable = false;
    Clock* lastInputClock;
};

