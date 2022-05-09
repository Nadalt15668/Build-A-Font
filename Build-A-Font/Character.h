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
    void SetCharacterData(std::string characterName, std::string templateFilename, std::vector<RectangleShape>& mainLines);
    void Update(Event& event, DrawingBoard& board);
    void Draw(RenderWindow& window);
private:
    sf::Shape& characterRect = *this->shape;
    std::vector<RectangleShape>* mainLines;
    std::string templateFilename;
    std::string characterName;
    Button<DrawingBoard&, std::string, std::string, std::vector<RectangleShape>&>* btnCharacter;
    Texture templateTex;
    sf::Sprite& drawingSprite = sprite;
};

