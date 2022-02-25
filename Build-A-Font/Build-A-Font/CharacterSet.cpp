#include "CharacterSet.h"

void NextPage(int& currentPage) 
{
    currentPage++;
    if (currentPage == 5)
        currentPage = 0;
}
void LastPage(int& currentPage)
{
    currentPage--;
    if (currentPage == -1)
        currentPage = 4;
}

CharacterSet::CharacterSet(RenderWindow& window, module_& module)
{
    btnNextPage = new Button<int&>(&window, NXT_PGE_POS, &NextPage, PAGE_BTN_DIM);
    btnNextPage->AddText(">", DEFAULT_FONT, 30);
    btnLastPage = new Button<int&>(&window, LST_PGE_POS, &LastPage, PAGE_BTN_DIM);
    btnLastPage->AddText("<", DEFAULT_FONT, 30);
    currentPage = 0;
    pythonModule = module;
    templateFilenames = FindTemplateNames();
    vector<float> x = CHARACTER_X_AXIS;
    vector<float> y = CHARACTER_Y_AXIS;
    for (int i = 0; i < y.size(); i++)
    { // Starts in 150, 8 characters in a row with a clean distance of 40.5
        for (int j = 0; j < x.size(); j++)
        {
            characters.push_back(new Character(Vector2f(x[j], y[i]), window));
        }
    }
}

vector<string> CharacterSet::FindTemplateNames()
{
    auto FilenamesRetriever = pythonModule.attr("retrieve_filenames");
    pybind11::list filenames_list = FilenamesRetriever();
    vector<std::string> filenames;
    for (int i = 0; i < CHARACTERS_IN_SET; i++) // Adds characters
        filenames.push_back("Templates/CharacterTemplates/Characters/" + pybind11::cast<string>(filenames_list[i]));
    for (int i = CHARACTERS_IN_SET; i < CHARACTERS_IN_SET + NUMBERS_IN_SET; i++) // Adds numbers
        filenames.push_back("Templates/CharacterTemplates/Numbers/" + pybind11::cast<string>(filenames_list[i]));
    for (int i = CHARACTERS_IN_SET + NUMBERS_IN_SET; i < TOTALS_IN_SET; i++) // Adds symbols
        filenames.push_back("Templates/CharacterTemplates/Symbols/" + pybind11::cast<string>(filenames_list[i]));
    return filenames;
}

void CharacterSet::Update(Event& event, DrawingBoard& board)
{
    btnLastPage->Update(event, currentPage);
    btnNextPage->Update(event, currentPage);
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        for (int j = 0; j < CHARACTERS_IN_ROW; j++)
        {
            characters[j + CHARACTERS_IN_ROW * i]->
                SetTemplateSprite(templateFilenames[currentPage * CHARACTERS_IN_PAGE + j + CHARACTERS_IN_ROW * i]);
            characters[j + CHARACTERS_IN_ROW * i]->Update(event, board,
                templateFilenames[currentPage * CHARACTERS_IN_PAGE + j + CHARACTERS_IN_ROW * i]);
        }
    }
}

void CharacterSet::Draw(RenderWindow& window)
{
    for (auto& character : characters)
        character->Draw(&window);
    btnNextPage->Draw();
    btnLastPage->Draw();
}
