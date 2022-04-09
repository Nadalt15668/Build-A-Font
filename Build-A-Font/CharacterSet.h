#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <map>
#include <Python.h>
#include <pybind11/embed.h>
#include "Character.h"
#include "FileDialog.h"
#include "Button.h"

using namespace pybind11;
using namespace sf;
using namespace std;

class CharacterSet
{
public:
	CharacterSet(RenderWindow& window, module_& module, IShellItem** loadedProject);
	void CreateMaps();
	void CaptureCharacter(string characterName, vector<RectangleShape> mainLines);
	void ReadProjectFile();
	void UpdateCharacters();
	void Update(Event& event, DrawingBoard& board);
	void Draw(RenderWindow& window);
	map<string, vector<RectangleShape>*>* GetCharactersDataPtr()
	{
		return &charactersData;
	}
private:
	module_ pythonModule;
	int currentPage;
	vector<string> mapsKeys;
	vector<Character*> characters;
	std::map<string, vector<RectangleShape>*> charactersData;
	std::map<string, string> templates;
	IShellItem** loadedProject;
	vector<RectangleShape>* currentLines;
	Button<int&>* btnNextPage;
	Button<int&>* btnPreviousPage;
};

