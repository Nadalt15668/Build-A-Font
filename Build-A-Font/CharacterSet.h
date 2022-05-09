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


class CharacterSet
{
public:
	CharacterSet(RenderWindow& window, module_& module, IShellItem** loadedProject);
	void CreateMaps();
	void CaptureCharacter(std::string characterName, std::vector<RectangleShape> mainLines);
	void ReadProjectFile();
	void UpdateCharacters();
	void Update(Event& event, DrawingBoard& board);
	void Draw(RenderWindow& window);
	std::map<std::string, std::vector<RectangleShape>*>* GetCharactersDataPtr()
	{
		return &charactersData;
	}
	std::vector<std::string>* GetMapsKeys()
	{
		return &mapsKeys;
	}
private:
	module_ pythonModule;
	int currentPage;
	std::vector<std::string> mapsKeys;
	std::vector<Character*> characters;
	std::map<std::string, std::vector<RectangleShape>*> charactersData;
	std::map<std::string, std::string> templates;
	IShellItem** loadedProject;
	std::vector<RectangleShape>* currentLines;
	Button<int&>* btnNextPage;
	Button<int&>* btnPreviousPage;
};

