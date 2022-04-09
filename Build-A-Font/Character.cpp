#include "Character.h"

void LoadCharacter(DrawingBoard& board, string templateFilename, vector<RectangleShape>& mainLines)
{
	board.Clear();
	board.SetCurrentCharacter(templateFilename, mainLines);
}

Character::Character(RenderWindow& window, Vector2f pos, sf::Shape* characterRect) :
	UIElement(pos, characterRect, Color::White)
{
	btnCharacter = new Button<DrawingBoard&, string, vector<RectangleShape>&>
		(window, pos, &LoadCharacter, characterRect, Color::White);
	this->characterRect.setOutlineThickness(1);
	this->characterRect.setOutlineColor(Color::Black);
	this->characterRect.setPosition(pos);
}

void Character::SetCharacterData(string templateFilename, vector<RectangleShape>& mainLines)
{
	RenderTexture drawingRenderTex;
	this->SetShapeTex(templateFilename);
	this->mainLines = &mainLines;
	this->templateFilename = templateFilename;
	vector<RectangleShape> texLines = mainLines;
	for (int i = 0; i < mainLines.size(); i++)
	{
		texLines[i].setScale(0.5, 0.5);
		texLines[i].move(-DRAWING_POS.x + DRAWING_DIM.x / 2, -DRAWING_POS.y + DRAWING_DIM.y / 2);
		drawingRenderTex.draw(texLines[i]);
	}
	drawingRenderTex.display();
	Texture* drawingTex = new Texture(drawingRenderTex.getTexture());
	SetSprite(drawingTex);
}

void Character::Update(Event& event, DrawingBoard& board)
{
	btnCharacter->Update(event, board, this->templateFilename, *mainLines);
}

void Character::Draw(RenderWindow& window)
{
	window.draw(characterRect);
	window.draw(drawingSprite);
}
