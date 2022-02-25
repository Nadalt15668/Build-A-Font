#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "DrawingBoard.h"
#include "Button.h"

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
	Character(Vector2f pos, RenderWindow& window);
	void ShowCharacter(CharacterInfo information);
	void SetTemplateSprite(string templateFilename, string charFilename = "");
	void Draw(RenderWindow* window);
	void Update(Event& event, DrawingBoard& board, string filename);
private:
	RectangleShape characterRect;
	Button<DrawingBoard&, string>* btnCharacter;
	Texture templateTex;
	Vector2f  position;
	Texture characterTex;
	Sprite characterSprite;
	CharacterInfo information;
};

