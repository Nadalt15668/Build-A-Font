#pragma once
#include <SFML/Graphics.hpp>
#include<Python.h>
#include <pybind11/embed.h>
#include "Button.h"
#include "DrawingBoard.h"
#include "CharacterSet.h"

using namespace sf;
using namespace std;
using namespace pybind11;
// Each state enables certain functions
enum ProgramStates{MENU, CHOOSE_CHARACTER, DRAWING};

class Program
{
public:
	Program();
	void Run();
	void Update(Event& event);
	void RunStates();
	void Draw();
	void UpdateButtons(Event event);
	void DrawButtons();
	vector<string> FindTemplateNames();
	void InitCharacters();
private:
	module_ pythonModule;
	RenderWindow* currentWindow;
	ProgramStates currentState;
	DrawingBoard* drawingBoard;
	Button<DrawingBoard&>* btnClearBoard;
	Button<DrawingBoard&>* btnCaptureBoard;
	CharacterSet* characterSet;
};

