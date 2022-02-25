#pragma once
#include <Python.h>
#include <pybind11/embed.h>
#include "Character.h"
#include "Button.h"

using namespace pybind11;
using namespace sf;
using namespace std;

class CharacterSet
{
public:
	CharacterSet(RenderWindow& window, module_& module);
	vector<string> FindTemplateNames();
	void Update(Event& event, DrawingBoard& board);
	void Draw(RenderWindow& window);
private:
	module_ pythonModule;
	vector<Character*> characters;
	int currentPage;
	vector<string> templateFilenames;
	Button<int&>* btnNextPage;
	Button<int&>* btnLastPage;
};

