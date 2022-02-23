#pragma once
#include <SFML/Graphics.hpp>
#include<Python.h>
#include <pybind11/embed.h>
#include "Button.h"
#include "DrawingBoard.h"
#include "Character.h"

using namespace sf;
using namespace std;
using namespace pybind11;

class Program
{
public:
	Program();
	void Run();
	void Update(Event& event);
	void Draw();
	void UpdateButtons(Event event);
	void DrawButtons();
	vector<string> FindTemplateNames();
	void InitCharacters();
private:
	module_ pythonModule;
	RenderWindow* currentWindow;
	DrawingBoard* drawingBoard;
	Button<DrawingBoard&>* btnClearBoard;
	Button<DrawingBoard&>* btnCaptureBoard;
	vector<Character*> characters;
};

