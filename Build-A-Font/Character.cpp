#include "Character.h"

void LoadCharacter(DrawingBoard& board, string templateFilename, vector<RectangleShape>& mainLines, string charFilename)
{
	board.Clear();
	board.SetCurrentCharacter(templateFilename, mainLines, charFilename);
}

Character::Character(Vector2f pos, RenderWindow& window)
{
	btnCharacter = new Button<DrawingBoard&, string, vector<RectangleShape>&, string>(&window, pos, &LoadCharacter,
		Vector2f(CHARACTER_DIM.x /2, CHARACTER_DIM.y / 2));
	characterRect.setSize(CHARACTER_DIM);
	characterRect.setOutlineThickness(2);
	characterRect.setOutlineColor(Color::Black);
	characterRect.setOrigin(characterRect.getLocalBounds().width / 2,
		characterRect.getGlobalBounds().height / 2);
	characterRect.setPosition(pos);
	characterSprite.setScale(Vector2f(0.5, 0.5));
	characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2, characterSprite.getLocalBounds().height / 2);
	characterSprite.setPosition(pos);
}

void Character::SetTemplateSprite(string templateFilename, vector<RectangleShape>& mainLines, string charFilename)
{
	if (charFilename != "")
	{
		if (!characterTex.loadFromFile(charFilename))
			cout << "Couldn't Load File" << endl;
		characterSprite.setTexture(characterTex);
		characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2,
			characterSprite.getLocalBounds().height / 2);
	}
	else
	{
		if (!characterTex.loadFromFile(BLANK_CHARACTER))
			cout << "Couldn't Load File" << endl;
		characterSprite.setTexture(characterTex);
		characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2,
			characterSprite.getLocalBounds().height / 2);
	}
	if (!templateTex.loadFromFile(templateFilename))
		cout << "Couldn't Load File" << endl;
	characterRect.setTexture(&templateTex);
	characterRect.setScale(Vector2f(0.5, 0.5));
	this->templateFilename = templateFilename;
	this->mainLines = &mainLines;
	this->charFilename = charFilename;
}

void Character::Draw(RenderWindow* window)
{
	window->draw(characterRect);
	window->draw(characterSprite);
}

void Character::Update(Event& event, DrawingBoard& board)
{
	btnCharacter->Update(event, board, templateFilename, *mainLines, charFilename);
}
