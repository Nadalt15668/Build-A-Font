#pragma once
#include "UIElement.h"

template <class... Args>
class Button :
    public UIElement
{
    // The button's function typedef
    typedef void(*ButtonFunction)(Args...);

public:
    Button(RenderWindow& window,
        Vector2f pos,
        ButtonFunction funcPtr,
        sf::Shape* shape,
        Color color = DEFAULT_BUTTON_COLOR) : UIElement(pos, shape, color)
    {
        this->window = &window;
        button.setOutlineThickness(2);
        button.setOutlineColor(Color::Black);
        this->onPressFunction = funcPtr;
        this->idleColor = color;
        this->hoverColor = DarkenedColors(this->idleColor);
        this->pressColor = DarkenedColors(this->hoverColor);
    };
    void AddText(String message, float textSize, String fontPath = DEFAULT_FONTPATH, Color textColor = Color::Black)
    {
        if (!this->hasText)
        {
            this->SetText(message, fontPath, textSize, textColor);
            this->hasText = true;
        }
    };
    bool Update(Event& event, const Args&... args)
    {
        Vector2i pixelPos = Mouse::getPosition(*this->window);
        // Current position of mouse in our window
        Vector2f worldPos = this->window->mapPixelToCoords(pixelPos);
        bool inBorders = CheckBorders(worldPos);
        if (event.type == Event::MouseButtonReleased && this->clickedLastFrame)
        {
            this->clickedLastFrame = false;
            if (inBorders)
                button.setFillColor(this->hoverColor);
            else
                button.setFillColor(this->idleColor);
        }
        // Outer if checks if the mouse is above the button
        if (inBorders && !this->clickedLastFrame)
        {
            button.setFillColor(this->hoverColor);
            // Inner if checks if the button is pressed
            if (event.type == Event::MouseButtonPressed && this->isClickable)
            {
                this->clickedLastFrame = true;
                button.setFillColor(pressColor);
                if (this->onPressFunction != NULL) // Checks if the button has functionality
                {
                    (this->onPressFunction)(args...);
                    Event newEvent;
                    newEvent.type = Event::MouseButtonReleased;
                    event = newEvent;
                }
                return true;
            }
        }
        if (inBorders)
            button.setFillColor(pressColor);
        else
            button.setFillColor(idleColor);
        return false;
    };
    void Draw(RenderWindow& window)
    {
        window.draw(button);
        if (hasText)
            window.draw(this->text);
    };
    void SetColor(Color color)
    {
        button.setFillColor(color);
        this->idleColor = color;
        this->hoverColor = DarkenedColors(this->idleColor);
        this->pressColor = DarkenedColors(this->hoverColor);
    };
    void SetWindow(RenderWindow& window)
    {
        this->window = window;
    };
private:
    // Private Functions
    bool CheckBorders(Vector2f worldPos)
    {
        Vector2f buttonSize(button.getLocalBounds().width,
            button.getLocalBounds().height);
        if (worldPos.x > this->pos.x - buttonSize.x / 2 && worldPos.x < this->pos.x + buttonSize.x / 2 &&
            worldPos.y > this->pos.y - buttonSize.y / 2 && worldPos.y < this->pos.y + buttonSize.y / 2)
            return true;
        return false;
    };
    Color DarkenedColors(Color color)
    {
        int newR = color.r - GRAY_SUB,
            newG = color.g - GRAY_SUB,
            newB = color.b - GRAY_SUB;
        if (newR < 0)
            newR = 0;
        if (newG < 0)
            newG = 0;
        if (newB < 0)
            newB = 0;
        return Color(newR, newG, newB);
    };
    // General Attributes
    RenderWindow* window;
    ButtonFunction onPressFunction;
    bool clickedLastFrame = false;
    bool isClickable = true;
    // Button's Atrributes
    sf::Shape& button = *this->shape;
    Color idleColor, hoverColor, pressColor;
    // Button's Text's Atrributes
    bool hasText;
};

