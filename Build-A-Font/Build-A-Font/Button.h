#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <functional>

using namespace std;
using namespace sf;

bool CheckBorders(RenderWindow& window, Vector2f size, Vector2f position)
{
	Vector2i pixelPos = sf::Mouse::getPosition(window);
	Vector2f worldPos = window.mapPixelToCoords(pixelPos); // Current position of mouse in our window
	if (worldPos.x > position.x && worldPos.x < position.x + size.x &&
		worldPos.y > position.y && worldPos.y < position.y + size.y)
		return true;
	return false;
}

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
}

// A class template for a button.
// Recieves an unknown number of parameters for its OnPress function
// AXIOMS:
// 1. The OnPress function has to be a non-returning (void) function
// 2. Cannot use the OnPress function for altering other buttons
template <class... Args >
class Button
{
	// The button's function typedef
	typedef void(*buttonFunction)(Args...);
public:
	Button(RenderWindow* currentWindow,
		Vector2f position,
		buttonFunction funcPtr,
		Vector2f size = DEFAULT_BUTTON_SIZE,
		Color color = DEFAULT_BUTTON_COLOR)
	{
		this->currentWindow = currentWindow;
		button.setSize(size);
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

	void AddText(String message, Font& font, float textSize, Color textColor = Color::Black)
	{
		if (!this->hasText)
		{
			text.setString(message);
			text.setPosition((size.x / 2) + position.x, (size.y / 2) + position.y);
			text.setOrigin(text.getLocalBounds().width / 2, 0);
			text.setCharacterSize(textSize);
			text.setFillColor(textColor);
			this->hasText = true;
		}
	};

	void Update(Event event, const Args&... args) {
		bool inBorders = CheckBorders(*currentWindow, size, position);
		if (event.type == Event::MouseButtonReleased && clickedLastFrame)
		{
			clickedLastFrame = false;
			if (inBorders)
				button.setFillColor(hoverColor);
			else
				button.setFillColor(idleColor);
		}
		// Outer if checks if the mouse is above the button
		else if (inBorders && !clickedLastFrame)
		{
			button.setFillColor(hoverColor);
			// Inner if checks if the button is pressed
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				clickedLastFrame = true;
				button.setFillColor(pressColor);
				if (this->onPressFunction != NULL) // Checks if the button has functionality
					(onPressFunction)(args...);
			}
		}
		else if (inBorders)
			button.setFillColor(pressColor);
		else
			button.setFillColor(idleColor);
	}
	void Draw()
	{
		currentWindow->draw(button);
		if (hasText)
			currentWindow->draw(text);
	};
//-------- Optional For Future --------
//	void SetLocation(Vector2f location);
//	void SetSize(Vector2f size);
	void SetColor(Color color)
	{
		button.setFillColor(color);
		this->idleColor = color;
		this->hoverColor = DarkenedColors(color);
		this->pressColor = DarkenedColors(hoverColor);
	};
//	void SetTextColor(Color color);

private:
	buttonFunction onPressFunction; // Function for clicking
	RenderWindow* currentWindow;
	bool clickedLastFrame = false; // For disabling hold
	// Button
	RectangleShape button;
	Vector2f size;
	Vector2f position;
	Color idleColor, hoverColor, pressColor;
	// Button's text
	bool hasText = false;
	Text text;
};
