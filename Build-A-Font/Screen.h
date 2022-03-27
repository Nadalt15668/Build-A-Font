#pragma once
#include <SFML/Graphics.hpp>
#include "UIElement.h"

using namespace sf;
using namespace std;

class Screen
{
public:
	Screen();
	virtual void Draw() = 0;
	virtual void Update(Event& event) = 0;
private:
	string screenName;
};

