#include "StartPage.h"

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

void StartUserProgram(EmptyDialog*& dialog, RenderWindow& window, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen)
{
	/*Screen* userProgram = new CharsDrawingPage(window, true, pythonModule, screens, currentScreen);
	screens.insert_or_assign(CHARS_DRAWING_PAGE, userProgram);
	currentScreen = userProgram;*/
	dialog->OpenDialog();
}

void StartAIProgram(RenderWindow& window, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen)
{
	Screen* aiProgram = new CharsDrawingPage(window, false, pythonModule, screens, currentScreen);
	screens.insert_or_assign(CHARS_DRAWING_PAGE, aiProgram);
	currentScreen = aiProgram;
}


StartPage::StartPage(RenderWindow& window, module_& pythonModule, map<string, Screen*>& screens, Screen*& currentScreen)
{
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
	btnUserProgam = new Button<EmptyDialog*&, RenderWindow&, module_&, map<string, Screen*>&, Screen*&>(window,
		USER_PROG_BTN_POS, &StartUserProgram, new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM)));
	btnUserProgam->AddText("User Program", 25);
	btnAIProgram = new Button<RenderWindow&, module_&, map<string, Screen*>&, Screen*&>(window,
		AI_PROG_BTN_POS, &StartAIProgram, new RectangleShape(Vector2f(DEFAULT_BUTTON_DIM)));
	btnAIProgram->AddText("AI Program", 30);

	dialogTest = new EmptyDialog(window, Vector2f(500, 400), "Empty Dialog");
	test = new TextBox(window, Vector2f(300, 300), DEFAULT_TEXTBOX_DIM, "testing test", TEXTBOX_TEXT_SIZE);
}

void StartPage::Draw()
{
	this->window->draw(this->logo);
	this->window->draw(this->title);
	btnUserProgam->Draw(*this->window);
	btnAIProgram->Draw(*this->window);
	test->Draw(*this->window);
	dialogTest->Draw();
}

void StartPage::Update(Event& event)
{
	btnUserProgam->Update(event, this->dialogTest, *this->window, *this->pythonModule, *this->screens, *this->currentScreen);
	btnAIProgram->Update(event, *this->window, *this->pythonModule, *this->screens, *this->currentScreen);
	test->Update(event);
	dialogTest->Update(event);
}
