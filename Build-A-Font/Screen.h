#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"

using namespace sf;

class Screen
{
public:
	Screen() {};
	virtual void Draw() = 0;
	virtual void Update(Event& event) = 0;
	bool& GetInteractability() { return isInteractable; };
protected:
	bool isInteractable = true;
};

