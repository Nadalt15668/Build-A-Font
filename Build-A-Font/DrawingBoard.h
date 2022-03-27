#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream> 
#include "Brush.h"

using namespace sf;
using namespace std;

class DrawingBoard
{
public:
	DrawingBoard(RenderWindow* window);
	void CreateLine();
	void Update(Event& event);
	virtual void Capture() = 0;
	void RemoveBackground();
	void SetTemplate(string filename);
	void SetCurrentCharacter(string templateFilename, vector<RectangleShape>& mainLines, string charFilename);
	void Draw();
	void Clear();
protected:
	RenderTexture drawingTex;
	RenderWindow* baseWindow;
	Brush brush;
	string templateFilename, charFilename;
	vector<RectangleShape> mainLines; // Actual mouse input
	vector<RectangleShape> texLines; // Lines for final character output
	vector<RectangleShape> viewLines; //Lines in the View
	View drawingView;
	RectangleShape viewTemplate;
};

