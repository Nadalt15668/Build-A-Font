#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "DrawingBoard.h"

using namespace sf;
using namespace std;

class Program
{
public:
	Program();
	void Run();
	void Update(Event& event);
	void Draw();
	void UpdateButtons(Event event);
	void DrawButtons();

private:
	RenderWindow* currentWindow;
	DrawingBoard* drawingBoard;
	Button<DrawingBoard&>* btnClearBoard;
};


