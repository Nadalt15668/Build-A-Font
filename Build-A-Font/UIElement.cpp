#include "UIElement.h"

UIElement::UIElement(Vector2f pos, sf::Shape* shape, Color shapeColor)
{
	InitElementTypes();
	this->shape = shape;
	this->shape->setOrigin(this->shape->getLocalBounds().width / 2,
		this->shape->getLocalBounds().height / 2);
	this->pos = pos;
	this->shape->setPosition(this->pos);
	this->shape->setFillColor(shapeColor);
	this->elementTypes.insert_or_assign(ElementType::Shape, true);
}

UIElement::UIElement(Vector2f pos, string text, int textSize, string fontPath)
{
	InitElementTypes();
	this->text.setString(text);
	this->text.setCharacterSize(textSize);
	Font* font = new Font;
	if (!font->loadFromFile(fontPath))
	{
		// Handle Error
	}
	this->text.setFont(*font);
	this->text.setOrigin(this->text.getLocalBounds().width / 2,
		this->text.getLocalBounds().height / 2);
	this->pos = pos;
	this->text.setPosition(this->pos);
	this->elementTypes.insert_or_assign(ElementType::Text, true);
}

UIElement::UIElement(Vector2f pos, string filename)
{
	InitElementTypes();
	Texture* texture = new Texture;
	if (!texture->loadFromFile(filename))
	{
		// Handle Error
	}
	this->sprite.setTexture(*texture);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 1.5);
	this->pos = pos;
	this->sprite.setPosition(this->pos);
	this->elementTypes.insert_or_assign(ElementType::Sprite, true);
}

void UIElement::InitElementTypes()
{
	elementTypes.insert_or_assign(ElementType::Shape, false);
	elementTypes.insert_or_assign(ElementType::Sprite, false);
	elementTypes.insert_or_assign(ElementType::Text, false);
}

bool UIElement::SetText(string text, string fontPath, int textSize, Color textColor, TextOrigin textOrigin)
{
	Font* font = new Font;
	if (!font->loadFromFile(fontPath))
	{
		// Handle Error
		return false;
	}
	this->text.setFont(*font);
	this->text.setCharacterSize(textSize);
	this->text.setString(text);
	this->textOrigin = textOrigin;
	if (textOrigin == CENTER)
	{
		this->text.setOrigin(this->text.getLocalBounds().width / 2,
			this->text.getLocalBounds().height);
		this->text.setPosition(this->pos);

	}
	else if (textOrigin == MARGIN_LEFT)
	{
		this->text.setOrigin(0, this->text.getLocalBounds().height);
		this->text.setPosition(Vector2f(this->pos.x - this->shape->getLocalBounds().width / 2, this->pos.y));
	}
	this->text.setFillColor(textColor);
	this->elementTypes.insert_or_assign(ElementType::Text, true);
	return true;
}

bool UIElement::SetText(string text, Font* font, int textSize, Color textColor, TextOrigin textOrigin)
{
	this->text.setFont(*font);
	this->text.setCharacterSize(textSize);
	this->text.setString(text);
	this->textOrigin = textOrigin;
	if (textOrigin == CENTER)
	{
		this->text.setOrigin(this->text.getLocalBounds().width / 2,
			this->text.getLocalBounds().height / 2);
		this->text.setPosition(this->pos);

	}
	else if (textOrigin == MARGIN_LEFT)
	{
		this->text.setOrigin(0, this->text.getLocalBounds().height / 2);
		this->text.setPosition(Vector2f(this->pos.x - this->shape->getLocalBounds().width / 2, this->pos.y));
	}
	this->text.setFillColor(textColor);
	this->elementTypes.insert_or_assign(ElementType::Text, true);
	return true;
}

bool UIElement::SetText(string text, Color textColor)
{
	this->text.setString(text);
	this->text.setFillColor(textColor);
	return true;
}

bool UIElement::SetRotation(float rotation)
{
	this->shape->setRotation(rotation);
	return true;
}

bool UIElement::SetSprite(string filename)
{
	Texture* texture = new Texture();
	if (!texture->loadFromFile(filename))
	{
		// Handle Error
		return false;
	}
	this->sprite.setTexture(*texture);
	this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 2);
	this->SetPosition(this->pos);
	this->elementTypes.insert_or_assign(ElementType::Sprite, true);
	return true;
}

bool UIElement::SetShapeTex(string filename)
{
	Texture* texture = new Texture;
	if (!texture->loadFromFile(filename))
	{
		// Handle Error
		return false;
	}
	this->shape->setTexture(texture);
	return true;
}

bool UIElement::SetPosition(Vector2f newPos)
{
	this->pos.x = newPos.x;
	this->pos.y = newPos.y;
	if (this->elementTypes.at(ElementType::Shape))
		this->shape->setPosition(newPos);
	if (this->elementTypes.at(ElementType::Sprite))
		this->sprite.setPosition(newPos);
	if (this->elementTypes.at(ElementType::Text))
		this->text.setPosition(newPos);
	return true;
}

bool UIElement::SetShapeOutline(float outlineThickness, Color outlineColor)
{
	this->shape->setOutlineThickness(outlineThickness);
	this->shape->setOutlineColor(outlineColor);
	return true;
}

bool UIElement::SetTextMargin(Margin marginDirection, float margin)
{
	switch (marginDirection)
	{
	case MARGIN_LEFT:
		this->text.move(Vector2f(margin, 0));
		return true;
	case MARGIN_RIGHT:
		this->text.move(Vector2f(-margin, 0));
		return true;
	case MARGIN_TOP:
		this->text.move(Vector2f(0, -margin));
		return true;
	case MARGIN_BOTTOM:
		this->text.move(Vector2f(0, margin));
		return true;
	}
	return true;
}

void UIElement::Move(Vector2f offset)
{
	this->pos.x += offset.x;
	this->pos.y += offset.y;
	if (this->elementTypes.at(ElementType::Shape))
		this->shape->move(offset);
	if (this->elementTypes.at(ElementType::Sprite))
		this->sprite.move(offset);
	if (this->elementTypes.at(ElementType::Text))
		this->text.move(offset);
}

UIElement::~UIElement()
{
	if (this->elementTypes.at(ElementType::Shape))
		delete shape;
}

