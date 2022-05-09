#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Button.h"

using namespace sf;

#define BACKSPACE 8
#define ELAPSED_TIME_FOR_INPUT 0.3
#define ELAPSED_TIME_FOR_BACKSPACE 0.2
#define CHARARCTER_INPUT static_cast<char>(event.text.unicode)

class TextBox :
    public UIElement
{
public:
    TextBox(RenderWindow& window, Vector2f pos, Vector2f size, std::string hintText, int textSize,std::string fontPath = DEFAULT_FONTPATH);
    void Draw(RenderWindow& window);
    void Update(Event& event);
    void MoveTextBox(Vector2f offset) { this->Move(offset); this->btnTextBox->Move(offset); };
    std::string GetText() { return this->totalText; };
    bool IsFilled() { return (this->totalText != "") ? true : false; };
    ~TextBox();
private:
    RenderWindow* window;
    Font* font;
    int numOfShownCharacters;
    int textSize;
    std::string shownText = ""; // The text that is actually shown
    std::string totalText = ""; // The total written text
    std::string hintText = ""; // A hint text of the textbox
    Button<bool&>* btnTextBox;
    bool isWritable = false;
    Clock* lastInputClock;
};

