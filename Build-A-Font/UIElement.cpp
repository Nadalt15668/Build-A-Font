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

bool UIElement::SetText(string text, string fontPath, float textSize, Color textColor)
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
	this->text.setOrigin(this->text.getLocalBounds().width / 2,
		this->text.getLocalBounds().height / 1.5);
	this->text.setFillColor(textColor);
	this->elementTypes.insert_or_assign(ElementType::Text, true);
	this->text.setPosition(this->pos);
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

