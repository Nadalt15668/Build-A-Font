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
	void SetTemplate(string filename);
	void Draw();
	void Clear();
private:
	RenderTexture drawingTex;
	RenderWindow* baseWindow;
	Brush brush;
	vector<RectangleShape> mainLines; // Actual mouse input
	vector<RectangleShape> texLines; // Lines for final character output
	vector<RectangleShape> viewLines; //Lines in the View
	View drawingView;
	RectangleShape viewTemplate;
};

