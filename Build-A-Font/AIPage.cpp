#include "AIPage.h"

void ClearAIBoard(DrawingBoard& drawingBoard)
{
    drawingBoard.Clear();
}
void CaptureCharacters(DrawingBoard& drawingBoard, CharacterSet& characterSet)
{
    if (!drawingBoard.CheckIfEmpty())
    {
        drawingBoard.Capture((characterSet.GetCharactersDataPtr()));
        characterSet.UpdateCharacters();
    }
}
void CaptureNumbers(AIBoard& drawingBoard, CharacterSet& characterSet)
{
    drawingBoard.CaptNum(characterSet.GetCharactersDataPtr());
    characterSet.UpdateCharacters();
}
void AIToStartPage(map<string, Screen*>& screens, Screen*& currentScreen)
{
    currentScreen = screens[STARTING_PAGE];
}
void LaunchAIMenu(MenuDialog** menuDialog, RenderWindow& window, CharacterSet** characterSet, IShellItem** loadedProject,
    Screen*& parentScreen, Vector2f size, string dialogTitle)
{
    *menuDialog = new MenuDialog(window, characterSet, loadedProject, parentScreen, size, dialogTitle);
    (*menuDialog)->OpenDialog(parentScreen->GetInteractability());
}

void UndoNum(AIBoard& drawingBoard, CharacterSet& characterSet)
{
    drawingBoard.UndoNum(characterSet.GetCharactersDataPtr());
    characterSet.UpdateCharacters();
}

AIPage::AIPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen)
{
    this->loadedProject = loadedProject;
    this->window = &window;
    characterSet = new CharacterSet(window, pythonModule, loadedProject);
    drawingBoard = new AIBoard
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
    btnClearBoard = new Button<DrawingBoard&>(window, Vector2f(PROGRAM_DIM.x / 2, CLEAR_POS.y),
        &ClearAIBoard, new RectangleShape(Vector2f(50, 50)), Color::Red);
    btnCaptChar = new Button<DrawingBoard&, CharacterSet&>(window,
        Vector2f(PROGRAM_DIM.x / 2 - btnClearBoard->GetShapeSize().x - 5 - DEFAULT_BUTTON_DIM.x / 2.6, CLEAR_POS.y), &CaptureCharacters,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnCaptNum = new Button<AIBoard&, CharacterSet&>(window,
        Vector2f(PROGRAM_DIM.x / 2 + btnClearBoard->GetShapeSize().x + 5 + DEFAULT_BUTTON_DIM.x / 2.6, CLEAR_POS.y), &CaptureNumbers,
        new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM.x / 1.3, 50)));
    btnUndoNumbers = new Button<AIBoard&, CharacterSet&>(window,
        Vector2f(PROGRAM_DIM.x / 2 + btnClearBoard->GetShapeSize().x + 5 + DEFAULT_BUTTON_DIM.x, CLEAR_POS.y), &UndoNum,
        new RectangleShape(Vector2f(30, 30)), Color::Red);
    btnToStartPage = new Button<map<string, Screen*>&, Screen*&>(window, TOP_LEFT_BTN_POS, &AIToStartPage, new RectangleShape(Vector2f(50, 50)), DEFAULT_GRAY_BGROUND);
    btnLaunchMenu = new Button< MenuDialog**, RenderWindow&, CharacterSet**, IShellItem**, Screen*&,
        Vector2f, string>(window, Vector2f(PROGRAM_DIM.x / 17 * 16, PROGRAM_DIM.y / 15), &LaunchAIMenu, new RectangleShape(Vector2f(50, 50)));
    btnLaunchMenu->SetShapeTex(MENU);
    btnToStartPage->SetShapeTex(BACK_ARROW);
    btnClearBoard->SetShapeTex(TRASH_CAN);
    btnUndoNumbers->SetShapeTex(UNDO);
    btnCaptChar->AddText("Manual", 30);
    btnCaptNum->AddText("Numbers", 30);
    btnToStartPage->SetShapeOutline(0, Color::Transparent);
}

void AIPage::Draw()
{
    this->drawingBoard->Draw();
    this->btnCaptChar->Draw(*this->window);
    this->btnCaptNum->Draw(*this->window);
    this->btnClearBoard->Draw(*this->window);
    this->btnToStartPage->Draw(*this->window);
    this->btnUndoNumbers->Draw(*this->window);
    this->characterSet->Draw(*this->window);
    this->btnLaunchMenu->Draw(*this->window);
    if (menuDialog != nullptr)
        menuDialog->Draw();
}

void AIPage::Update(Event& event)
{
    if (isInteractable)
    {
        drawingBoard->Update(event);
        btnUndoNumbers->Update(event, *this->drawingBoard, *this->characterSet);
        btnCaptChar->Update(event, *this->drawingBoard, *this->characterSet);
        btnCaptNum->Update(event, *this->drawingBoard, *this->characterSet);
        btnClearBoard->Update(event, *this->drawingBoard);
        characterSet->Update(event, *this->drawingBoard);
        btnToStartPage->Update(event, *this->screens, *this->currentScreen);
        this->btnLaunchMenu->Update(event, &menuDialog, *window, &characterSet, loadedProject,
            *currentScreen, Vector2f(270, 350), "Menu");
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            LaunchAIMenu(&menuDialog, *window, &characterSet, loadedProject,
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
