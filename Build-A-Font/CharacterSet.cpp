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

CharacterSet::CharacterSet(RenderWindow& window, module_& module, IShellItem** loadedProject)
{
    this->loadedProject = loadedProject;
    this->pythonModule = module;
    btnNextPage = new Button<int&>(window, NXT_CHR_PGE_POS, &NextPage, new CircleShape(30, 3));
    btnNextPage->SetRotation(90);
    btnPreviousPage = new Button<int&>(window, PRVS_CHR_PGE_POS, &LastPage, new CircleShape(30, 3));
    btnPreviousPage->SetRotation(-90);
    CreateMaps();
    vector<float> x = CHARACTER_X_AXIS;
    vector<float> y = CHARACTER_Y_AXIS;
    for (int i = 0; i < y.size(); i++)
    { // Starts in 150, 8 characters in a row with a clean distance of 40.5
        for (int j = 0; j < x.size(); j++)
        {
            characters.push_back(new Character(window, Vector2f(x[j], y[i])));
        }
    }
    auto FilenamesRetriever = pythonModule.attr("retrieve_clean_filenames");
    pybind11::list filenamesPylist = FilenamesRetriever();
    for (int i = 0; i < filenamesPylist.size(); i++)
        mapsKeys.push_back(cast<string>(filenamesPylist[i]));
    ReadProjectFile();
}

void CharacterSet::CreateMaps()
{
    int index = 0;
    auto FilenamesRetriever = pythonModule.attr("retrieve_templates");
    pybind11::list templatesPylist = FilenamesRetriever();
    string filename;
    for (index; index < CHARACTERS_IN_SET; index++) // Adds characters
    {
        filename = cast<string>(templatesPylist[index]);
        filename.replace(filename.find_last_of('.'), 4, "");
        templates.insert_or_assign(filename, TEMPLATES_CHARACTERS + 
            (string)"Characters/" + filename + (string)".png");
        charactersData.insert_or_assign(filename,  new vector<RectangleShape>);
    }
    for (index; index < CHARACTERS_IN_SET + NUMBERS_IN_SET; index++) // Adds numbers
    {
        filename = cast<string>(templatesPylist[index]);
        filename.replace(filename.find_last_of('.'), 4, "");
        templates.insert_or_assign(filename, TEMPLATES_CHARACTERS + 
            (string)"Numbers/" + filename + (string)".png");
        charactersData.insert_or_assign(filename, new vector<RectangleShape>);
    }
    for (index; index < TOTALS_IN_SET; index++) // Adds symbols
    {
        filename = cast<string>(templatesPylist[index]);
        filename.replace(filename.find_last_of('.'), 4, "");
        templates.insert_or_assign(filename, TEMPLATES_CHARACTERS + 
            (string)"Symbols/" + filename + (string)".png");
        charactersData.insert_or_assign(filename, new vector<RectangleShape>);
    }
}

void CharacterSet::CaptureCharacter(string characterName, vector<RectangleShape> mainLines)
{
    this->charactersData[characterName]->clear();
    for (auto line : mainLines)
        this->charactersData[characterName]->push_back(line);
}

void CharacterSet::ReadProjectFile()
{
#define NUM_OF_FIELDS 5
    char* fileData = new char;
    fileData = CDialogEventHandler::ReadFromFile(this->loadedProject);
    if (fileData != nullptr)
    {
        char* token;
        vector<string> splittedFile;
        token = strtok(fileData, FILE_DELIM);
        while (token != NULL)
        {
            splittedFile.push_back(token);
            token = strtok(NULL, FILE_DELIM);
        }
        vector<RectangleShape>* characterData;
        int numOfLines = 0;
        for (int i = 0; i < splittedFile.size() - 1;)
        {
            characterData = charactersData[splittedFile[i++]];
            numOfLines = stoi(splittedFile[i++]);
            for (int j = 0; j < numOfLines; j++)
            {
                RectangleShape curLine;
                curLine.setFillColor(Color::Black);
                curLine.setOrigin(Vector2f(0, BRUSH_THICKNESS / 2));
                curLine.setSize(Vector2f(stof(splittedFile[i]), stof(splittedFile[i+1])));
                i += 2;
                curLine.setPosition(Vector2f(stof(splittedFile[i]), stof(splittedFile[i+1])));
                i += 2;
                curLine.setRotation(stof(splittedFile[i]));
                i++;
                characterData->push_back(curLine);
            }
        }
    }
    UpdateCharacters();
}


void CharacterSet::UpdateCharacters()
{
#define LOCATION_IN_MAP mapsKeys[CHARACTERS_IN_PAGE*currentPage+i*CHARACTERS_IN_ROW+j]
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        for (int j = 0; j < CHARACTERS_IN_ROW; j++)
        {
            characters[i * CHARACTERS_IN_ROW + j]->
                SetCharacterData(LOCATION_IN_MAP, templates[LOCATION_IN_MAP],
                    *charactersData[LOCATION_IN_MAP]);
        }
    }
}

void CharacterSet::Update(Event& event, DrawingBoard& board)
{
    if (btnPreviousPage->Update(event, currentPage) ||
        btnNextPage->Update(event, currentPage))
        UpdateCharacters();
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        for (int j = 0; j < CHARACTERS_IN_ROW; j++)
        {
            // Checks for button interaction of each character (for loading on drawing board)
            characters[j + CHARACTERS_IN_ROW * i]->Update(event, board);
        }
    }
}

void CharacterSet::Draw(RenderWindow& window)
{
    for (auto& character : characters)
        character->Draw(window);
    btnNextPage->Draw(window);
    btnPreviousPage->Draw(window);
}
