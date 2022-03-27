#pragma once
#include "UIElement.h"
#include "Button.h"
#include "DrawingBoard.h"

class Character :
    public UIElement
{
public:
    Character(RenderWindow& window,
        Vector2f pos,
        sf::Shape* characterRect = new RectangleShape(Vector2f(CHARACTER_DIM.x / 2, CHARACTER_DIM.y / 2)));
    void SetTemplateSprite(string templateFilename, vector<RectangleShape>& mainLines, string charFilename = "");
    void Update(Event& event, DrawingBoard& board);
    void Draw(RenderWindow& window);
private:
    sf::Shape& characterRect = *this->shape;
    vector<RectangleShape>* mainLines;
    string templateFilename;
    string charFilename;
    Button<DrawingBoard&, string, vector<RectangleShape>&, string>* btnCharacter;
    Texture templateTex;
    Texture characterTex;
    sf::Sprite& characterSprite = this->sprite;
};

