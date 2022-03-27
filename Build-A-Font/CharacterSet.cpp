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
    btnNextPage = new Button<int&>(window, NXT_PGE_POS, &NextPage, new RectangleShape(PAGE_BTN_DIM));
    btnNextPage->AddText(">", 30);
    btnLastPage = new Button<int&>(window, LST_PGE_POS, &LastPage, new RectangleShape(PAGE_BTN_DIM));
    btnLastPage->AddText("<", 30);
    currentPage = 0;
    pythonModule = module;
    templateFilenames = FindTemplateNames();
    FillMap();
    vector<float> x = CHARACTER_X_AXIS;
    vector<float> y = CHARACTER_Y_AXIS;
    for (int i = 0; i < y.size(); i++)
    { // Starts in 150, 8 characters in a row with a clean distance of 40.5
        for (int j = 0; j < x.size(); j++)
        {
            characters.push_back(new Character(window, Vector2f(x[j], y[i])));
        }
    }
}

vector<string> CharacterSet::FindTemplateNames()
{
    auto FilenamesRetriever = pythonModule.attr("retrieve_templates");
    pybind11::list filenames_list = FilenamesRetriever();
    vector<std::string> filenamesVector;
    for (int i = 0; i < CHARACTERS_IN_SET; i++) // Adds characters
    {
        filenamesVector.push_back(TEMPLATES_CHARACTERS + (string)"Characters/" + cast<string>(filenames_list[i]));
        drawingFilenames.insert_or_assign(cast<string>(filenames_list[i]), "");
    }
    for (int i = CHARACTERS_IN_SET; i < CHARACTERS_IN_SET + NUMBERS_IN_SET; i++) // Adds numbers
    {
        filenamesVector.push_back(TEMPLATES_CHARACTERS + (string)"Numbers/" + cast<string>(filenames_list[i]));
        drawingFilenames.insert_or_assign(cast<string>(filenames_list[i]), "");
    }
    for (int i = CHARACTERS_IN_SET + NUMBERS_IN_SET; i < TOTALS_IN_SET; i++) // Adds symbols
    {
        filenamesVector.push_back(TEMPLATES_CHARACTERS + (string)"Symbols/" + cast<string>(filenames_list[i]));
        drawingFilenames.insert_or_assign(cast<string>(filenames_list[i]), "");
    }
    return filenamesVector;
}

void CharacterSet::FillMap()
{
    auto retrieveCharacters = pythonModule.attr("retrieve_characters");
    pybind11::list characters_list = retrieveCharacters();
    for (auto& character : characters_list)
        drawingFilenames.insert_or_assign(cast<string>(character), cast<string>(character));
}

void ReadFromLinesFile(vector<RectangleShape>& mainLines, string filename)
{
    RectangleShape currentLine;
    currentLine.setFillColor(Color::Black);
    currentLine.setOrigin(Vector2f(0, BRUSH_THICKNESS / 2));
    Vector2f info;
    // Reading lines from file
    filename = BINARIES + filename;
    char* stringBuffer = (char*)malloc(10);
    FILE* txtFile = fopen(filename.c_str(), "r");
    if (txtFile == NULL)
        cout << ERROR_WHILE_OPENING << endl;
    else
    {
        while (!feof(txtFile))
        {
            // line.getSize().x
            fgets(stringBuffer, 100, txtFile);
            if (!feof(txtFile))
            {
                info.x = atof(stringBuffer);
                // line.getSize().y
                fgets(stringBuffer, 100, txtFile);
                info.y = atof(stringBuffer);
                currentLine.setSize(info);
                // line.getPosition().x
                fgets(stringBuffer, 100, txtFile);
                info.x = atof(stringBuffer);
                // line.getPosition().y
                fgets(stringBuffer, 100, txtFile);
                info.y = atof(stringBuffer);
                currentLine.setPosition(info);
                // line.getRotation()
                fgets(stringBuffer, 100, txtFile);
                info.x = atof(stringBuffer);
                currentLine.setRotation(info.x);
                mainLines.push_back(currentLine);
            }
            else
                break;
        }
    }
    fclose(txtFile);
}

void CharacterSet::LoadCharactersData()
{
    FillMap();
    for (int i = 0; i < NUM_OF_ROWS; i++)
    {
        for (int j = 0; j < CHARACTERS_IN_ROW; j++)
        {
            string currentChar, currentTemp;
            currentLines = new vector<RectangleShape>();
            currentTemp = templateFilenames[currentPage * CHARACTERS_IN_PAGE + j + CHARACTERS_IN_ROW * i];
            // For locating the drawing name in the drawings map, we need to remove the directories
            // from currentTemp. After locating the drawing name (if exists) and the lines, the full name is located again.
            currentTemp.replace(0, currentTemp.find_last_of("/") + 1, "");
            if (drawingFilenames[currentTemp] != "")
            {
                currentChar = DRAWINGS + drawingFilenames[currentTemp];
                string binName = drawingFilenames[currentTemp];
                binName.replace(binName.find_last_of("."), binName.length(), FILE_TYPE);
                ReadFromLinesFile(*currentLines, binName);
            }
            else
            {
                // If no drawing is available, will pass an empty string to the function
                currentChar = drawingFilenames[currentTemp];
                currentLines->clear();
            }
            // Locating the full name again:
            currentTemp = templateFilenames[currentPage * CHARACTERS_IN_PAGE + j + CHARACTERS_IN_ROW * i];
            // Updating each character's drawing and template (according to the current page)
            characters[j + CHARACTERS_IN_ROW * i]->SetTemplateSprite(currentTemp, *currentLines, currentChar);
        }
    }
}

void CharacterSet::Update(Event& event, DrawingBoard& board)
{
    if (btnLastPage->Update(event, currentPage) ||
        btnNextPage->Update(event, currentPage))
        LoadCharactersData();
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
    btnLastPage->Draw(window);
}
