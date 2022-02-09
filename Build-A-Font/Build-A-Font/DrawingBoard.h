#pragma once
#include "Brush.h"
class DrawingBoard
{
public:
	DrawingBoard(RenderWindow* window);
	void CreateLine();
	void Update(Event& event);
	void Draw();
	void Clear();
private:
	RenderWindow* window;
	Brush brush;
	RectangleShape board;
	vector<RectangleShape> lines;
};

