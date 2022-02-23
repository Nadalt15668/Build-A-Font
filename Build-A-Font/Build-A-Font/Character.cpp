#include "Character.h"

Character::Character(Vector2f pos)
{
	characterRect.setSize(CHARACTER_DIM);
	characterRect.setOutlineThickness(2);
	characterRect.setOutlineColor(Color::Black);
	characterRect.setOrigin(characterRect.getLocalBounds().width / 2,
		characterRect.getGlobalBounds().height / 2);
	characterRect.setPosition(pos);
	SetTemplateSprite(BLANK_TEMPLATE); // Starts empty (only blank templates), after initiating gets filled with character drawings
	characterSprite.setScale(Vector2f(0.5, 0.5));
	characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2, characterSprite.getLocalBounds().height / 2);
	characterSprite.setPosition(pos);
}

void Character::ShowCharacter(CharacterInfo information)
{
	this->information.mainLines = information.mainLines;
	this->information.charFilename = information.charFilename;
	this->information.templateFilename = information.templateFilename;
	SetTemplateSprite(information.charFilename, information.templateFilename);
}

void Character::SetTemplateSprite(string templateFilename, string charFilename)
{
	if (charFilename != "")
	{
		if (!characterTex.loadFromFile(charFilename))
			cout << "Couldn't Load File" << endl;
		characterSprite.setTexture(characterTex);
	}
	if (!templateTex.loadFromFile(templateFilename))
		cout << "Couldn't Load File" << endl;
	characterRect.setTexture(&templateTex);
	characterRect.setScale(Vector2f(0.5, 0.5));
}

void Character::LoadToBoard(DrawingBoard& drawingBoard)
{
	
}

void Character::Draw(RenderWindow* window)
{
	window->draw(characterRect);
	window->draw(characterSprite);
}
