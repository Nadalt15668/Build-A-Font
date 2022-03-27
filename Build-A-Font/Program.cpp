#include "Program.h"

Program::Program()
{
    currentWindow = new RenderWindow(sf::VideoMode(PROGRAM_DIM.x, PROGRAM_DIM.y), "Build-A-Font");
    pythonModule = module_::import("python"); // Importing the module from 'python.py'
    InitScreensMap();
    LoadCurrentPage(STARTING_PAGE);
}

void Program::InitScreensMap()
{
    this->screens = {   {CHARS_DRAWING_PAGE, nullptr},
                        {STARTING_PAGE, new StartPage(*this->currentWindow,
                            this->pythonModule, this->screens, this->currentPage)} 
                    };
}

void Program::LoadCurrentPage(string pageName)
{
    this->currentPage = this->screens[pageName];
}

void Program::Run()
{
    while (currentWindow->isOpen())
    {
        sf::Event event;
        while (currentWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                currentWindow->close();
        }
        Update(event);
        currentWindow->clear(DEFAULT_GRAY_BGROUND);
        Draw();
        currentWindow->display();
    }
}

void Program::Update(Event& event)
{
    this->currentPage->Update(event);
}

void Program::Draw()
{
    this->currentPage->Draw();
}


