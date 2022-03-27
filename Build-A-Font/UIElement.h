#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

typedef enum { Shape, Sprite, Text } ElementType;

class UIElement
{
public:
	// For a clean Shape
	UIElement(Vector2f pos, sf::Shape* shape, Color shapeColor/* = DEFAULT_COLOR*/);
	// For a clean Text
	UIElement(Vector2f pos, string text, int textSize, string fontPath/* = DEFAULT_FONTPATH*/);
	// For a clean Sprite
	UIElement(Vector2f pos, string filename);
	bool SetText(string text, string fontPath, float textSize, Color textColor = Color::Black);
	bool SetSprite(string filename);
	bool SetShapeTex(string filename);
	bool SetPosition(Vector2f newPos);
	void Move(Vector2f offset);
	virtual void Draw(RenderWindow& window) = 0;
private:
	void InitElementTypes();
protected:
	sf::Shape* shape;
	sf::Sprite sprite;
	sf::Text text;
	Vector2f pos;
	map<ElementType, bool> elementTypes;
};



