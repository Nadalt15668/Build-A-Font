#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <functional>

using namespace std;
using namespace sf;

// A class template for a button.
// Recieves an unknown number of parameters for its OnPress function
// ASSUMPTIONS:
// 1. The OnPress function has to be a non-returning (void) function
// 2. Cannot use the OnPress function for altering other buttons
template <class... Args>
class Button
{
	// The button's function typedef
	typedef void(*ButtonFunction)(Args...);

public:
	Button(RenderWindow* currentWindow,
		Vector2f position,
		ButtonFunction funcPtr,
		Vector2f size = DEFAULT_BUTTON_DIM,
		Color color = DEFAULT_BUTTON_COLOR) {
		this->currentWindow = currentWindow;
		button.setSize(size);
		button.setOrigin(button.getLocalBounds().width / 2, button.getLocalBounds().height / 2);
		button.setPosition(position);
		button.setFillColor(color);
		button.setOutlineThickness(2);
		button.setOutlineColor(Color::Black);
		this->onPressFunction = funcPtr;
		this->size = size;
		this->position = position;
		this->idleColor = color;
		this->hoverColor = DarkenedColors(color);
		this->pressColor = DarkenedColors(hoverColor);
	};
	void AddText(String message, String fontPath, float textSize, Color textColor = Color::Black) 
	{
		if (!this->hasText)
		{
			font.loadFromFile(fontPath);
			text.setString(message);
			text.setCharacterSize(textSize);
			text.setFillColor(textColor);
			text.setFont(font);
			text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2 + 5);
			text.setPosition(position.x, position.y);
			this->hasText = true;
		}
	};
	void Update(Event& event, const Args&... args) 
	{
		bool inBorders = CheckBorders();
		if (event.type == Event::MouseButtonReleased && clickedLastFrame)
		{
			clickedLastFrame = false;
			if (inBorders)
				button.setFillColor(hoverColor);
			else
				button.setFillColor(idleColor);
		}
		// Outer if checks if the mouse is above the button
		if (inBorders && !clickedLastFrame)
		{
			button.setFillColor(hoverColor);
			// Inner if checks if the button is pressed
			if (Mouse::isButtonPressed(Mouse::Left) && isClickable)
			{
				clickedLastFrame = true;
				button.setFillColor(pressColor);
				if (this->onPressFunction != NULL) // Checks if the button has functionality
					(onPressFunction)(args...);
			}
		}
		if (inBorders)
			button.setFillColor(pressColor);
		else
			button.setFillColor(idleColor);
	};
	void Draw() 
	{
		currentWindow->draw(button);
		if (hasText)
			currentWindow->draw(text);
	};
	void SetColor(Color color) 
	{
		button.setFillColor(color);
		this->idleColor = color;
		this->hoverColor = DarkenedColors(color);
		this->pressColor = DarkenedColors(hoverColor);
	};
	void SetWindow(RenderWindow* window)
	{
		this->currentWindow = window;
	};

private:
	// Private Functions
	bool CheckBorders()
	{
		Vector2i pixelPos = Mouse::getPosition(*currentWindow);
		Vector2f worldPos = currentWindow->mapPixelToCoords(pixelPos); // Current position of mouse in our window
		if (worldPos.x > position.x - size.x / 2 && worldPos.x < position.x + size.x / 2 &&
			worldPos.y > position.y - size.y / 2 && worldPos.y < position.y + size.y / 2)
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
	// Data Members
	ButtonFunction onPressFunction; // Function for clicking
	RenderWindow* currentWindow;
	bool clickedLastFrame = false; // For disabling hold
	bool isClickable = true;
	// Button
	RectangleShape button;
	Vector2f size;
	Vector2f position;
	Color idleColor, hoverColor, pressColor;
	// Button's text
	bool hasText = false;
	Font font;
	Text text;
};
