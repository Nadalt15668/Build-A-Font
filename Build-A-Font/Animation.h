#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"

using namespace sf;

class Animation :
	public UIElement
{
public:
	Animation(Vector2f size, std::string filename, Vector2u imageCount, float switchTime, Vector2f pos);
	~Animation();
	void Update(int row);
	void Draw(RenderWindow& window);
private:
	Clock clock;
	IntRect uvRect;
	Texture* texture;
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
};

