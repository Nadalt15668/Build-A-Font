#include "StartProgramDialog.h"

bool containsOnlyASCII(string& filePath) {
	for (auto c : filePath) {
		if (static_cast<unsigned char>(c) > 127 || static_cast<unsigned char>(c) == 63) {
			return false;
		}
	}
	return true;
}

#define DEFAULT_CHOOSE_MSG "No Chosen File"
#define ERROR_NON_ASCII "Error: N0N-ASCII characters"
void ChooseFile(string& filePath, sf::Text*& chosenFile)
{
	filePath = CDialogEventHandler::ChooseFromFolder();
	if (filePath != "" && containsOnlyASCII(filePath))
	{
		string fileName = filePath.substr(filePath.find_last_of('\\') + 1);
		chosenFile->setString(fileName);
		chosenFile->setFillColor(Color::Green);
		chosenFile->setOutlineColor(Color::Black);
		chosenFile->setOrigin(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2);
	}
	else if (filePath != "")
	{
		filePath = "";
		chosenFile->setString(ERROR_NON_ASCII);
		chosenFile->setFillColor(Color::Red);
		chosenFile->setOutlineColor(Color::Black);
		chosenFile->setOrigin(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2);
	}
}

void CancelChoice(string& filePath, sf::Text*& chosenFile)
{
	filePath = "";
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

void InitiateSttcNewFileName(Font*& font, sf::Text*& sttcNewFileName, FloatRect dialogBground, Vector2f& startingOffset)
{
	sttcNewFileName = new sf::Text("New filename: ", *font, 30);
	sttcNewFileName->setFillColor(Color::Black);
	sttcNewFileName->setPosition(
		Vector2f(dialogBground.width / 2 - sttcNewFileName->getLocalBounds().width + startingOffset.x,
		20 + startingOffset.y)
	);
}
void InitiateSttcOr(Font*& font, sf::Text*& sttcOr, FloatRect dialogBground, Vector2f& startingOffset)
{
	sttcOr = new sf::Text("or", *font, 40);
	sttcOr->setFillColor(Color::Black);
	sttcOr->setOrigin(sttcOr->getLocalBounds().width / 2, sttcOr->getLocalBounds().height / 2);
	sttcOr->setPosition(
		Vector2f(dialogBground.width / 2 + startingOffset.x,
			80 + startingOffset.y)
	);
}
void InitiateTxtBoxNewFileName(RenderWindow& window, TextBox*& newFilename, FloatRect dialogBground, Vector2f& startingOffset)
{
	Vector2f size = DEFAULT_TEXTBOX_DIM;
	Vector2f position(dialogBground.width / 2 + size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 17.5);
	newFilename = new TextBox(window, position, size, "New filename", TEXTBOX_TEXT_SIZE);
}
void InitiateBtnChooseFile(RenderWindow& window, Button<string&, sf::Text*&>*& btnChooseFile, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(110, 40));
	Vector2f position(dialogBground.width / 2 - size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 135);
	btnChooseFile = new Button<string&, sf::Text*&>(window, position, &ChooseFile, new RectangleShape(size), Color(200, 200, 200));
	btnChooseFile->AddText("Choose...", 25);
}
void InitiateBtnCancelChoice(RenderWindow& window, Button<string&, sf::Text*&>*& btnCancelChoice, FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(110, 40));
	Vector2f position(dialogBground.width / 2 + size.x / 1.5 + startingOffset.x, startingOffset.y + size.y / 2 + 135);
	btnCancelChoice = new Button<string&, sf::Text*&>(window, position, &CancelChoice, new RectangleShape(size), Color(200, 200, 200));
	btnCancelChoice->AddText("Cancel", 25);
}
void InitiateTxtChosenFile(Font*& font, sf::Text*& chosenFile, FloatRect dialogBground, Vector2f& startingOffset)
{
	chosenFile = new sf::Text(DEFAULT_CHOOSE_MSG, *font, 30);
	chosenFile->setFillColor(Color::Black);
	chosenFile->setOutlineColor(Color::Transparent);
	chosenFile->setOutlineThickness(2);
	chosenFile->setOrigin(Vector2f(chosenFile->getLocalBounds().width / 2, chosenFile->getLocalBounds().height / 2));
	chosenFile->setPosition(Vector2f(dialogBground.width / 2 + startingOffset.x, startingOffset.y + 210));
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
	DrawingPagePars* parameters, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->parameters = parameters;
	Vector2f startingOffset = CalculateStartingOffset();
	Font* font = new Font();
	if (!font->loadFromFile(DEFAULT_FONTPATH))
	{
		// Handle Errors
		exit(0);
	}
	InitiateSttcNewFileName(font, sttcNewFileName, this->dialogBground->getLocalBounds(), startingOffset);
	InitiateTxtBoxNewFileName(window, newFileName, this->dialogBground->getLocalBounds(), startingOffset);
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
		this->window->draw(*sttcNewFileName);
		this->window->draw(*sttcOr);
		newFileName->Draw(*window);
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
	sttcNewFileName->move(offset);
	sttcOr->move(offset);
	newFileName->MoveTextBox(offset);
	btnChooseFile->Move(offset);
	btnCancelChoice->Move(offset);
	chosenFileName->move(offset);
	btnUserProgram->Move(offset);
	btnAIProgram->Move(offset);
}

void StartProgramDialog::Update(Event& event)
{
	if (isOpen)
	{
		CheckForDragging(event);
		btnCloseDialog->Update(event, isOpen, parentScreen->GetInteractability());
		newFileName->Update(event);
		btnChooseFile->Update(event, filePath, chosenFileName);
		btnCancelChoice->Update(event, filePath, chosenFileName);
		btnUserProgram->Update(event, parameters);
		btnAIProgram->Update(event, parameters);
	}
}

