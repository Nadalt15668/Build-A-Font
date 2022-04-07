#include "StartProgramDialog.h"

bool containsOnlyASCII(string& filePath) {
	for (auto c : filePath) {
		if (static_cast<unsigned char>(c) > 127 || static_cast<unsigned char>(c) == 63) {
			return false;
		}
	}
	return true;
}

#define DEFAULT_CHOOSE_MSG "No  project file is chosen"
#define ERROR_NON_ASCII "Error: N0N-ASCII characters"
void ChooseFile(string& fileName, IShellItem** chosenItem, sf::Text*& chosenFile)
{
	fileName = CDialogEventHandler::ChooseFile(*chosenItem);
	if (fileName != "" && containsOnlyASCII(fileName))
	{
		chosenFile->setString(fileName);
		chosenFile->setFillColor(Color::Green);
		chosenFile->setOutlineColor(Color::Black);
		chosenFile->setOrigin(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2);
	}
	else if (fileName != "")
	{
		fileName = "";
		chosenFile->setString(ERROR_NON_ASCII);
		chosenFile->setFillColor(Color::Red);
		chosenFile->setOutlineColor(Color::Black);
		chosenFile->setOrigin(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2);
	}
}

void CancelChoice(string& filePath, IShellItem** chosenItem, sf::Text*& chosenFile)
{
	filePath = "";
	*chosenItem = nullptr;
	chosenFile->setString(DEFAULT_CHOOSE_MSG);
	chosenFile->setFillColor(Color::Black);
	chosenFile->setOutlineColor(Color::Transparent);
	chosenFile->setOrigin(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2);
}

void StartUserProgram(DrawingPagePars* parameters)
{
	Screen* userProgram = new CharsDrawingPage(**(parameters->window), true,
		**(parameters->pythonModule), **(parameters->screens), **(parameters->currentScreen));
	(*(parameters->screens))->insert_or_assign(CHARS_DRAWING_PAGE, userProgram);
	**(parameters->currentScreen) = userProgram;
	
}

void StartAIProgram(DrawingPagePars* parameters)
{
	Screen* aiProgram = new CharsDrawingPage(**(parameters->window), false,
		**(parameters->pythonModule), **(parameters->screens), **(parameters->currentScreen));
	(*(parameters->screens))->insert_or_assign(CHARS_DRAWING_PAGE, aiProgram);
	**(parameters->currentScreen) = aiProgram;
}
void InitiateSttcCreatProj(Font*& font, sf::Text*& sttcCreateProj, FloatRect dialogBground, Vector2f& startingOffset)
{
	sttcCreateProj = new sf::Text("Start a new project:", *font, 50);
	sttcCreateProj->setFillColor(Color::Black);
	sttcCreateProj->setOrigin(sttcCreateProj->getLocalBounds().width / 2, sttcCreateProj->getLocalBounds().height / 2);
	sttcCreateProj->setPosition(
		Vector2f(dialogBground.width / 2 + startingOffset.x,
			215 + startingOffset.y)
	);
}
void InitiateSttcOr(Font*& font, sf::Text*& sttcOr, FloatRect dialogBground, Vector2f& startingOffset)
{
	sttcOr = new sf::Text("or", *font, 40);
	sttcOr->setFillColor(Color::Black);
	sttcOr->setOrigin(sttcOr->getLocalBounds().width / 2, sttcOr->getLocalBounds().height / 2);
	sttcOr->setPosition(
		Vector2f(dialogBground.width / 2 + startingOffset.x,
			160 + startingOffset.y)
	);
}
void InitiateBtnChooseFile(RenderWindow& window, Button<string&,IShellItem**,sf::Text*&>*& btnChooseFile, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(110, 40));
	Vector2f position(dialogBground.width / 2 - size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 30);
	btnChooseFile = new Button<string&, IShellItem**, sf::Text*&>(window, position, &ChooseFile, new RectangleShape(size), Color(200, 200, 200));
	btnChooseFile->AddText("Choose...", 25);
}
void InitiateBtnCancelChoice(RenderWindow& window, Button<string&,IShellItem**,sf::Text*&>*& btnCancelChoice, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(110, 40));
	Vector2f position(dialogBground.width / 2 + size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 30);
	btnCancelChoice = new Button<string&, IShellItem**, sf::Text*&>(window, position, &CancelChoice, new RectangleShape(size), Color(200, 200, 200));
	btnCancelChoice->AddText("Cancel", 25);
}
void InitiateTxtChosenFile(Font*& font, sf::Text*& chosenFile, FloatRect dialogBground, Vector2f& startingOffset)
{
	chosenFile = new sf::Text(DEFAULT_CHOOSE_MSG, *font, 30);
	chosenFile->setFillColor(Color::Black);
	chosenFile->setOutlineColor(Color::Transparent);
	chosenFile->setOutlineThickness(2);
	chosenFile->setOrigin(Vector2f(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2));
	chosenFile->setPosition(Vector2f(dialogBground.width / 2 + startingOffset.x, startingOffset.y + 105));
}
void InitiateBtnUserProgram(DrawingPagePars* parameters, Button<DrawingPagePars*>*& btnUserProgram, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(120, 40));
	Vector2f position(dialogBground.width / 2 - size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 300);
	btnUserProgram = new Button<DrawingPagePars*>(**(parameters->window), position, &StartUserProgram,
		new RectangleShape(size), Color(200, 200, 200));
	btnUserProgram->AddText("User Mode", 25);
}
void InitiateBtnAIProgram(DrawingPagePars* parameters, Button<DrawingPagePars*>*& btnAIProgram, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(120, 40));
	Vector2f position(dialogBground.width / 2 + size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 300);
	btnAIProgram = new Button<DrawingPagePars*>(**(parameters->window), position, &StartAIProgram,
		new RectangleShape(size), Color(200, 200, 200));
	btnAIProgram->AddText("AI Mode", 25);
}

StartProgramDialog::StartProgramDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size,
	DrawingPagePars* parameters, IShellItem** chosenItem, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->parameters = parameters;
	this->chosenItem = chosenItem;
	Vector2f startingOffset = CalculateStartingOffset();
	Font* font = new Font();
	if (!font->loadFromFile(DEFAULT_FONTPATH))
	{
		// Handle Errors
		exit(0);
	}
	InitiateSttcCreatProj(font, this->sttcStartNewProj, this->dialogBground->getLocalBounds(), startingOffset);
	InitiateSttcOr(font, sttcOr, dialogBground->getLocalBounds(), startingOffset);
	InitiateBtnChooseFile(window, this->btnChooseFile, this->dialogBground->getLocalBounds(), startingOffset);
	InitiateBtnCancelChoice(window, this->btnCancelChoice, this->dialogBar->getLocalBounds(), startingOffset);
	InitiateTxtChosenFile(font, this->chosenFileName, this->dialogBground->getLocalBounds(), startingOffset);
	InitiateBtnUserProgram(parameters, this->btnUserProgram, this->dialogBground->getLocalBounds(), startingOffset);
	InitiateBtnAIProgram(parameters, this->btnAIProgram, this->dialogBground->getLocalBounds(), startingOffset);
}

void StartProgramDialog::Draw()
{
	if (this->isOpen)
	{
		DrawEssentials();
		this->window->draw(*sttcStartNewProj);
		this->window->draw(*sttcOr);
		btnChooseFile->Draw(*window);
		btnCancelChoice->Draw(*window);
		this->window->draw(*chosenFileName);
		btnUserProgram->Draw(*window);
		btnAIProgram->Draw(*window);
	}
}

void StartProgramDialog::Move(Vector2f offset)
{
	MoveEssentials(offset);
	sttcOr->move(offset);
	sttcStartNewProj->move(offset);
	btnChooseFile->Move(offset);
	btnCancelChoice->Move(offset);
	chosenFileName->move(offset);
	btnUserProgram->Move(offset);
	btnAIProgram->Move(offset);
}

bool StartProgramDialog::Update(Event& event)
{
	if (isOpen)
	{
		if (btnCloseDialog->Update(event, isOpen, parentScreen->GetInteractability()))
			return false;
		CheckForDragging(event);
		btnChooseFile->		Update(event, filePath, chosenItem, chosenFileName);
		btnCancelChoice->	Update(event, filePath, chosenItem, chosenFileName);
		if (btnUserProgram->Update(event, parameters) ||
			btnAIProgram->	Update(event, parameters))
			return false;
	}
	return true;
}

StartProgramDialog::~StartProgramDialog()
{
	delete sttcOr;
	delete chosenFileName;
	delete btnChooseFile;
	delete btnCancelChoice;
	delete btnUserProgram;
	delete btnAIProgram;
}

