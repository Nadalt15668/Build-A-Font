#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "DrawingBoard.h"

using namespace sf;
using namespace std;

typedef struct
{
	vector<RectangleShape> mainLines;
	string templateFilename;
	string charFilename;
}CharacterInfo;

class Character
{
public:
	Character(Vector2f pos);
	void ShowCharacter(CharacterInfo information);
	void SetTemplateSprite(string templateFilename, string charFilename = "");
	void LoadToBoard(DrawingBoard& drawingBoard);
	void Draw(RenderWindow* window);
	void Update();
private:
	RectangleShape characterRect;
	Texture templateTex;
	Vector2f  position;
	Texture characterTex;
	Sprite characterSprite;
	CharacterInfo information;
};

