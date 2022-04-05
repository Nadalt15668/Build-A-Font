#pragma once
#include <SFML/Graphics.hpp>
#include<Python.h>
#include <pybind11/embed.h>
#include "OpeningPage.h"

using namespace sf;
using namespace std;
using namespace pybind11;

class Program
{
public:
	Program();
	void InitScreensMap();
	void LoadCurrentPage(string pageName);
	void Run();
	void Update(Event& event);
	void Draw();
private:
	module_ pythonModule;
	RenderWindow* currentWindow;
	Screen* currentPage;
	map<string, Screen*> screens;
};

