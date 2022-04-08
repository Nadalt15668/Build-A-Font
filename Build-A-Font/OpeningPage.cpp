#include "OpeningPage.h"

#define TITLE "Build-A-Font"

template<class Buffer>
Buffer* LoadFromFile(string filename)
{
	Buffer* buffer = new Buffer();
	if (!buffer->loadFromFile(filename))
	{
		// Handle error
		return nullptr;
	}
	return buffer;
}

template<class Object>
void SetCommonAttributes(Object& object, Vector2f pos)
{
	object.setOrigin(object.getLocalBounds().width / 2, object.getLocalBounds().height / 2);
	object.setPosition(pos);
}

void StartProgram(StartProgramDialog*& dialog,IShellItem** chosenItem, RenderWindow*& window, module_*& pythonModule, map<string, Screen*>*& screens,
	Screen**& parentScreen)
{
	//ButtonParameters parameters = {window, pythonModule, screens, currentScreen };
	DrawingPagePars* parameters = (DrawingPagePars*)malloc(sizeof(DrawingPagePars));
	parameters->window = &window;
	parameters->pythonModule = &pythonModule;
	parameters->screens = &screens;
	parameters->currentScreen = &parentScreen;
	dialog = new StartProgramDialog(*window, *parentScreen, Vector2f(500, 400), parameters, "Create Or Load Project");
	dialog->OpenDialog((*parentScreen)->GetInteractability());
}

void QuitProgram()
{
	exit(0);
}


OpeningPage::OpeningPage(RenderWindow& window, IShellItem** chosenItem, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen)
{
	this->chosenItem = chosenItem;
	// Attributes for screen buttons
	this->pythonModule = &pythonModule;
	this->screens = &screens;
	this->currentScreen = &currentScreen;
	// Initiating logo
	this->window = &window;
	this->logo.setTexture(*LoadFromFile<Texture>(PROJECT_LOGO));
	this->logo.setScale(0.5f, 0.5f);
	SetCommonAttributes(this->logo, LOGO_POS);
	// Initiating title
	this->title.setFont(*LoadFromFile<Font>(DEFAULT_FONTPATH));
	this->title.setString(TITLE);
	this->title.setCharacterSize(50);
	this->title.setOutlineColor(Color::Black);
	this->title.setOutlineThickness(5);
	SetCommonAttributes(this->title, TITLE_POS);
	// Initiating navigation buttons
	btnStartProgram = new Button<StartProgramDialog*&, IShellItem**,RenderWindow*&, module_*&, map<string, Screen*>*&, Screen**&>(window,
		Vector2f(PROGRAM_DIM.x / 2, (PROGRAM_DIM.y / 1.5)), &StartProgram, new RectangleShape(Vector2f(140, 60)));
	btnStartProgram->AddText("Start", 35);

	btnQuitProgram = new Button<>(window, Vector2f(PROGRAM_DIM.x / 2, (PROGRAM_DIM.y / 1.3)),
		&QuitProgram, new RectangleShape(Vector2f(110, 50)));
	btnQuitProgram->AddText("Quit", 30);
}

void OpeningPage::Draw()
{
	this->window->draw(this->logo);
	this->window->draw(this->title);
	btnStartProgram->Draw(*this->window);
	btnQuitProgram->Draw(*this->window);
	if (dialogTest != nullptr)
		dialogTest->Draw();
}

void OpeningPage::Update(Event& event)
{
	if (isInteractable == true)
	{
		btnStartProgram->Update(event, this->dialogTest, this->chosenItem, this->window, this->pythonModule, this->screens, this->currentScreen);
		btnQuitProgram->Update(event);
	}
	if (dialogTest != nullptr)
	{
		if (!dialogTest->Update(event))
		{
			delete dialogTest;
			dialogTest = nullptr;
			isInteractable = true;
		}
	}
}
