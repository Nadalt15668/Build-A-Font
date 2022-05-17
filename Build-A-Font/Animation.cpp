#include "Animation.h"

Animation::Animation(Vector2f size, std::string filename, Vector2u imageCount, float switchTime, Vector2f pos) :
	UIElement(pos, new RectangleShape(size), Color::White)
{
	SetShapeTex(filename);
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x = 0;
	shape->setTextureRect(uvRect);
	uvRect.width =	size.x;
	uvRect.height = size.y;
}

Animation::~Animation() {

}

void Animation::Update(int row)
{
	float deltaTime = clock.restart().asSeconds();
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
			currentImage.x = 0;
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
	shape->setTextureRect(uvRect);
}

void Animation::Draw(RenderWindow& window)
{
	window.draw(*shape);
}

