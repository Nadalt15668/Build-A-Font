#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawingBoard.h"
#include "Constants.h"
#include "Button.h"

using namespace sf;
using namespace std;

class Character
{
public:
	Character(Vector2f pos, RenderWindow& window);
	void SetTemplateSprite(string templateFilename, vector<RectangleShape>& mainLines, string charFilename = "");
	void Draw(RenderWindow* window);
	void Update(Event& event, DrawingBoard& board);
private:
	RectangleShape characterRect;
	vector<RectangleShape>* mainLines;
	string templateFilename;
	string charFilename;
	Button<DrawingBoard&, string, vector<RectangleShape>&, string>* btnCharacter;
	Texture templateTex;
	Vector2f  position;
	Texture characterTex;
	Sprite characterSprite;
};

