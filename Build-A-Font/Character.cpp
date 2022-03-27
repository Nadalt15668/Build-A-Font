#include "Character.h"

void LoadCharacter(DrawingBoard& board, string templateFilename, vector<RectangleShape>& mainLines, string charFilename)
{
	board.Clear();
	board.SetCurrentCharacter(templateFilename, mainLines, charFilename);
}

Character::Character(RenderWindow& window, Vector2f pos, sf::Shape* characterRect) :
	UIElement(pos, characterRect, Color::White)
{
	btnCharacter = new Button<DrawingBoard&, string, vector<RectangleShape>&, string>
		(window, pos, &LoadCharacter, characterRect, Color::White);
	this->characterRect.setOutlineThickness(1);
	this->characterRect.setOutlineColor(Color::Black);
	this->characterRect.setPosition(pos);
	this->characterSprite.setScale(Vector2f(0.5, 0.5));
	this->characterSprite.setPosition(pos);
}

void Character::SetTemplateSprite(string templateFilename, vector<RectangleShape>& mainLines, string charFilename)
{
	this->SetShapeTex(templateFilename);
	if (charFilename != "")
		this->SetSprite(charFilename);
	else
		this->SetSprite(BLANK_CHARACTER);
	this->mainLines = &mainLines;
	this->templateFilename = templateFilename;
	this->charFilename = charFilename;
}

void Character::Update(Event& event, DrawingBoard& board)
{
	btnCharacter->Update(event, board, this->templateFilename, *mainLines, this->charFilename);
}

void Character::Draw(RenderWindow& window)
{
	window.draw(characterRect);
	window.draw(characterSprite);
}
