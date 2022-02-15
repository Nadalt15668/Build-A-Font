#pragma once
#include "Brush.h"
class DrawingBoard
{
public:
	DrawingBoard(RenderWindow* window);
	void CreateLine();
	void Update(Event& event);
	void Capture(string filename);
	void RemoveBackground();
	void Draw();
	void Clear();
private:
	RenderTexture drawingTex;
	RenderWindow* baseWindow;
	Brush brush;
	vector<RectangleShape> mainLines;
	vector<RectangleShape> texLines;
	vector<RectangleShape> viewLines;
	View drawingView;
	RectangleShape viewTemplate;
};

