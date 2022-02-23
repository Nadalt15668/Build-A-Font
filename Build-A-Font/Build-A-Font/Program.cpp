#include "Program.h"

//------------------------ BUTTON FUNCTIONS ------------------------
void ClearBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}
void CaptureBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Capture("file.png");
}
//------------------------------------------------------------------

Program::Program()
{
    currentWindow = new RenderWindow(sf::VideoMode(PROGRAM_DIM.x, PROGRAM_DIM.y), "SFML works!");
    drawingBoard = new DrawingBoard(currentWindow);
    pythonModule = module_::import("python"); // Importing the module from 'python.py'
    //------------------------------------------------------------
    //                          Buttons
    //                          -------
    btnClearBoard = new Button<DrawingBoard&>(currentWindow, Vector2f(PROGRAM_DIM.x / 2 + DEFAULT_BUTTON_SIZE.x /2.2, (PROGRAM_DIM.y / 3) *1.65), &ClearBoard,
                                Vector2f(DEFAULT_BUTTON_SIZE.x / 1.3, 50));
    btnCaptureBoard = new Button<DrawingBoard&>(currentWindow, Vector2f(PROGRAM_DIM.x / 2 - DEFAULT_BUTTON_SIZE.x / 2.2, (PROGRAM_DIM.y / 3) * 1.65), &CaptureBoard,
        Vector2f(DEFAULT_BUTTON_SIZE.x / 1.3, 50));
    //------------------------------------------------------------
    btnClearBoard->AddText("CLEAR", DEFAULT_FONT, 30);
    btnCaptureBoard->AddText("CAPTURE", DEFAULT_FONT, 30);
}

void Program::Run()
{
    InitCharacters();
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
    drawingBoard->Update(event);
    UpdateButtons(event);

}

void Program::Draw()
{
    drawingBoard->Draw();
    for (auto& character : characters)
        character->Draw(currentWindow);
    DrawButtons();
}

void Program::UpdateButtons(Event event)
{
    btnClearBoard->Update(event, *drawingBoard);
    btnCaptureBoard->Update(event, *drawingBoard);
}

void Program::DrawButtons()
{
    btnClearBoard->Draw();
    btnCaptureBoard->Draw();
}

vector<string> Program::FindTemplateNames()
{
    auto FilenamesRetriever = pythonModule.attr("retrieve_filenames");
    pybind11::list filenames_list = FilenamesRetriever();
    vector<std::string> filenames;
    for (auto& filename : filenames_list)
        filenames.push_back("Templates/" + pybind11::cast<string>(filename));
    return filenames;
}

void Program::InitCharacters()
{
    vector<string> templateFilenames = FindTemplateNames();
    vector<float> x = CHARACTER_X_AXIS;
    vector<float> y = CHARACTER_Y_AXIS;
    for (int i = 0; i < x.size(); i++)
    { // Starts in 150, 8 characters in a row with a clean distance of 40.5
        for (int j = 0; j < y.size(); j++)
        {
            characters.push_back(new Character(Vector2f(x[i], y[j])));
            characters.back()->SetTemplateSprite(templateFilenames[i + x.size()*j]);
        }
    }
}
