#include "Character.h"

void LoadCharacter(DrawingBoard& board, string filename)
{
	int start_pos = filename.find("CharacterTemplates");
	filename.replace(0, 28, "");
	string templateFilename = "Templates/DrawingTemplates" + filename;
	//string drawingFilename = " . . . " + filename;
	board.SetTemplate(templateFilename);
}

Character::Character(Vector2f pos, RenderWindow& window)
{
	btnCharacter = new Button<DrawingBoard&, string>(&window, pos, &LoadCharacter,
		Vector2f(CHARACTER_DIM.x /2, CHARACTER_DIM.y / 2));
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

void Character::Draw(RenderWindow* window)
{
	window->draw(characterRect);
	window->draw(characterSprite);
}

void Character::Update(Event& event, DrawingBoard& board, string filename)
{
	btnCharacter->Update(event, board, filename);
}
