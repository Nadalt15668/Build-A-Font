#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <map>
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
	void FillMap();
	void LoadCharactersData();
	void Update(Event& event, DrawingBoard& board);
	void Draw(RenderWindow& window);
	vector<Character*>& GetCharacters() 
	{ return this->characters; };
private:
	module_ pythonModule;
	int currentPage;
	vector<Character*> characters;
	vector<string> templateFilenames;
	vector<RectangleShape>* currentLines;
	map<string, string> drawingFilenames;
	Button<int&>* btnNextPage;
	Button<int&>* btnLastPage;
};

