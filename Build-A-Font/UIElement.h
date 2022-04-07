#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;
using namespace std;

typedef enum { Shape, Sprite, Text } ElementType;
typedef enum { LEFT, CENTER } TextOrigin;
typedef enum { MARGIN_LEFT, MARGIN_RIGHT, MARGIN_TOP, MARGIN_BOTTOM } Margin;
class UIElement
{
public:
	// For a clean Shape
	UIElement(Vector2f pos, sf::Shape* shape, Color shapeColor = DEFAULT_BUTTON_COLOR);
	// For a clean Text
	UIElement(Vector2f pos, string text, int textSize, string fontPath = DEFAULT_FONTPATH);
	// For a clean Sprite
	UIElement(Vector2f pos, string filename);
	bool SetText(string text, string fontPath, int textSize, Color textColor = Color::Black, TextOrigin textOrigin = CENTER);
	bool SetText(string text, Font* font, int textSize, Color textColor = Color::Black, TextOrigin textOrigin = CENTER);
	bool SetText(string text, Color textColor);
	bool SetRotation(float rotation);
	bool SetSprite(string filename);
	bool SetShapeTex(string filename);
	bool SetPosition(Vector2f newPos);
	bool SetShapeOutline(float outlineThickness, Color outlineColor);
	FloatRect GetTextBounds() { return this->text.getLocalBounds(); };
	bool SetTextMargin(Margin marginDirection, float margin);
	void Move(Vector2f offset);
	virtual ~UIElement();
	virtual void Draw(RenderWindow& window) = 0;
private:
	void InitElementTypes();
protected:
	sf::Shape* shape;
	sf::Sprite sprite;
	sf::Text text;
	TextOrigin textOrigin;
	Vector2f pos;
	map<ElementType, bool> elementTypes;
};



