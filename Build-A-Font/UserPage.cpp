#include "UserPage.h"

void ClearBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}
void CaptureBoard(DrawingBoard& drawingBoard, CharacterSet& characterSet)
{
    drawingBoard.Capture((characterSet.GetCharactersDataPtr()));
    characterSet.UpdateCharacters();
}
void ToStartPage(map<string, Screen*>& screens, Screen*& currentScreen)
{
    currentScreen = screens[STARTING_PAGE];
}
void LaunchMenu(MenuDialog** menuDialog, RenderWindow& window, CharacterSet** characterSet, IShellItem** loadedProject,
    Screen*& parentScreen, Vector2f size, string dialogTitle)
{
    *menuDialog = new MenuDialog(window, characterSet, loadedProject, parentScreen, size, dialogTitle);
    (*menuDialog)->OpenDialog(parentScreen->GetInteractability());
}


UserPage::UserPage(RenderWindow& window, IShellItem** loadedProject,
    module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen) 
    : Screen()
{
    this->loadedProject = loadedProject;
    this->window = &window;
    characterSet = new CharacterSet(window, pythonModule, loadedProject);
    drawingBoard = new UserBoard
    (
        window,
        Vector2f(PROGRAM_DIM.x + (DRAWING_DIM.x / 2),
            (DRAWING_DIM.y / 2)),
        Vector2f(DRAWING_DIM.x, DRAWING_DIM.y),
        Vector2f(DRAWING_DIM.x / PROGRAM_DIM.x,
            DRAWING_DIM.y / PROGRAM_DIM.y),
        Vector2f(0.5 - (DRAWING_DIM.x / 2) / PROGRAM_DIM.x,
            0.333 - (DRAWING_DIM.y / 2) / PROGRAM_DIM.y)
    );
    this->screens = &screens;
    this->currentScreen = &currentScreen;
    btnClearBoard = new Button<DrawingBoard&>(window, CLEAR_POS, &ClearBoard,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnCaptureBoard = new Button<DrawingBoard&, CharacterSet&>(window, CAPTURE_POS, &CaptureBoard,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnToStartPage = new Button<map<string, Screen*>&, Screen*&>(window, TOP_LEFT_BTN_POS, &ToStartPage, new RectangleShape(Vector2f(50, 50)), DEFAULT_GRAY_BGROUND);
    btnLaunchMenu = new Button< MenuDialog**, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, string>(window, Vector2f(PROGRAM_DIM.x / 17 * 16, PROGRAM_DIM.y / 15), &LaunchMenu, new RectangleShape(Vector2f(50, 50)));
    btnLaunchMenu->SetShapeTex("Assets/menu.png");
    btnToStartPage->SetShapeTex("Assets/back_arrow.png");
    btnClearBoard->AddText("CLEAR", 30);
    btnCaptureBoard->AddText("CAPTURE", 30);
    btnToStartPage->SetShapeOutline(0, Color::Transparent);
}

void UserPage::Draw()
{
    this->drawingBoard->Draw();
    this->btnCaptureBoard->Draw(*this->window);
    this->btnClearBoard->Draw(*this->window);
    this->btnToStartPage->Draw(*this->window);
    this->characterSet->Draw(*this->window);
    this->btnLaunchMenu->Draw(*this->window);
    if (menuDialog != nullptr)
        menuDialog->Draw();
}

void UserPage::Update(Event& event)
{
    if (isInteractable)
    {
        drawingBoard->Update(event);
        btnCaptureBoard->Update(event, *this->drawingBoard, *this->characterSet);
        btnClearBoard->Update(event, *this->drawingBoard);
        characterSet->Update(event, *this->drawingBoard);
        btnToStartPage->Update(event, *this->screens, *this->currentScreen);
        this->btnLaunchMenu->Update(event, &menuDialog, *window, &characterSet, loadedProject,
            *currentScreen, Vector2f(270, 350), "Menu");
    }
    if (menuDialog != nullptr)
    {
        if (!menuDialog->Update(event))
        {
            delete menuDialog;
            menuDialog = nullptr;
            isInteractable = true;
        }
    }
}
