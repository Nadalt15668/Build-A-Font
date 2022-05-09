#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

typedef enum { Shape, Sprite, Text } ElementType;
typedef enum { LEFT, CENTER } TextOrigin;
typedef enum { MARGIN_LEFT, MARGIN_RIGHT, MARGIN_TOP, MARGIN_BOTTOM } Margin;
class UIElement
{
public:
	// For a clean Shape
	UIElement(Vector2f pos, sf::Shape* shape, Color shapeColor = DEFAULT_BUTTON_COLOR);
	// For a clean Text
	UIElement(Vector2f pos, std::string text, int textSize, std::string fontPath = DEFAULT_FONTPATH);
	// For a clean Sprite
	UIElement(Vector2f pos, std::string filename);
	bool SetText(std::string text, std::string fontPath, int textSize, Color textColor = Color::Black, TextOrigin textOrigin = CENTER);
	bool SetText(std::string text, Font* font, int textSize, Color textColor = Color::Black, TextOrigin textOrigin = CENTER);
	bool SetText(std::string text, Color textColor);
	bool SetRotation(float rotation);
	bool SetSprite(std::string filename);
	bool SetSprite(Texture* texture);
	bool SetShapeTex(std::string filename);
	bool SetPosition(Vector2f newPos);
	bool SetShapeOutline(float outlineThickness, Color outlineColor);
	FloatRect GetTextBounds() { return this->text.getLocalBounds(); };
	bool SetTextMargin(Margin marginDirection, float margin);
	void Move(Vector2f offset);
	Vector2f GetShapeSize() 
	{ return Vector2f(this->shape->getLocalBounds().width, this->shape->getLocalBounds().height); };
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
	std::map<ElementType, bool> elementTypes;
};



