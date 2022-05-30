#include "Character.h"

// Loads current to character to board
void LoadCharacter(DrawingBoard& board, std::string characterName, std::string templateFilename, std::vector<RectangleShape>& mainLines)
{
	board.Clear();
	board.SetCurrentCharacter(characterName, templateFilename, mainLines);
}

// Constructor
Character::Character(RenderWindow& window, Vector2f pos, sf::Shape* characterRect) :
	UIElement(pos, characterRect, Color::White)
{
	btnCharacter = new Button<DrawingBoard&, std::string, std::string, std::vector<RectangleShape>&>
		(window, pos, &LoadCharacter, characterRect, Color::White);
	this->characterRect.setOutlineThickness(1);
	this->characterRect.setOutlineColor(Color::Black);
	this->characterRect.setPosition(pos);
}

// Set character's fields with data from the character set
void Character::SetCharacterData(std::string characterName, std::string templateFilename, std::vector<RectangleShape>& mainLines)
{
	RenderTexture drawingRenderTex;
	drawingRenderTex.create(DRAWING_DIM.x, DRAWING_DIM.y);
	drawingRenderTex.clear(Color::Transparent);
	this->SetShapeTex(templateFilename);
	this->characterName = characterName;;
	this->mainLines = &mainLines;
	this->templateFilename = templateFilename;
	std::vector<RectangleShape> texLines = mainLines;
	for (int i = 0; i < mainLines.size(); i++)
	{
		texLines[i].move(-DRAWING_POS.x + DRAWING_DIM.x / 2, -DRAWING_POS.y + DRAWING_DIM.y / 2);
		drawingRenderTex.draw(texLines[i]);
	}
	drawingRenderTex.display();
	Texture* drawingTex = new Texture(drawingRenderTex.getTexture());
	SetSprite(drawingTex);
}

void Character::Update(Event& event, DrawingBoard& board)
{
	// Updates the button responsible for interaction
	btnCharacter->Update(event, board, this->characterName, this->templateFilename, *mainLines);
}

void Character::Draw(RenderWindow& window)
{
	window.draw(characterRect);
	window.draw(drawingSprite);
}
