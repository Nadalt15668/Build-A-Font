#include "OpeningPage.h"

#define TITLE "FontCreatorNN"

template<class T>
T* LoadFromFile(std::string filename)
{
	T* buffer = new T();
	if (!buffer->loadFromFile(filename))
		// Handle error
		return nullptr;
	return buffer;
}

template<class Object>
void SetCommonAttributes(Object& object, Vector2f pos)
{
	object.setOrigin(object.getLocalBounds().width / 2, object.getLocalBounds().height / 2);
	object.setPosition(pos);
}

// Button function
void StartProgram(StartProgramDialog*& dialog,IShellItem*& loadedProject, RenderWindow*& window, module_*& pythonModule, std::map<std::string, Screen*>*& screens,
	Screen**& parentScreen)
{
	//ButtonParameters parameters = {window, pythonModule, screens, currentScreen };
	DrawingPagePars* parameters = (DrawingPagePars*)malloc(sizeof(DrawingPagePars));
	parameters->window = &window;
	parameters->pythonModule = &pythonModule;
	parameters->screens = &screens;
	parameters->currentScreen = &parentScreen;
	parameters->loadedProject = &loadedProject;
	dialog = new StartProgramDialog(*window, *parentScreen, Vector2f(500, 400), parameters, "Create Or Load Project");
	dialog->OpenDialog((*parentScreen)->GetInteractability());
}

// Button function
void QuitProgram()
{
	exit(0);
}

// Constructor
OpeningPage::OpeningPage(RenderWindow& window, IShellItem** loadedProject, module_& pythonModule, std::map<std::string, Screen*>& screens, Screen*& currentScreen)
{
	this->loadedProject = *loadedProject;
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
	btnStartProgram = new Button<StartProgramDialog*&, IShellItem*&,RenderWindow*&, module_*&, std::map<std::string, Screen*>*&, Screen**&>(window,
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
	if (startDialog != nullptr) // If there is a startDialog, draw it
		startDialog->Draw();
}

void OpeningPage::Update(Event& event)
{
	if (isInteractable == true) // If the page is interactale, update all its elements
	{
		btnStartProgram->Update(event, this->startDialog, this->loadedProject, this->window, this->pythonModule, this->screens, this->currentScreen);
		btnQuitProgram->Update(event);
	}
	if (startDialog != nullptr)// else if there is a startDialog, update it
	{
		if (!startDialog->Update(event))
		{
			delete startDialog;
			startDialog = nullptr;
			isInteractable = true;
		}
	}
}
