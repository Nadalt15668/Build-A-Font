#include "MenuDialog.h"

string ReadCharacterSet(CharacterSet** characterSet)
{
	string fileData = "";
	vector<string>* mapsKeys = (*characterSet)->GetMapsKeys();
	map<string, vector<RectangleShape>*>* charactersData = (*characterSet)->GetCharactersDataPtr();
	for (int i = 0; i < (*mapsKeys).size(); i++)
	{
		vector<RectangleShape>* curCharData = (*charactersData)[(*mapsKeys)[i]];
		if ((*curCharData).size() != 0)
			fileData += (*mapsKeys)[i] + "\n";
		for (auto line : *curCharData)
		{
			fileData += to_string(line.getSize().x) + "\n";
			fileData += to_string(line.getSize().y) + "\n";
			fileData += to_string(line.getPosition().x) + "\n";
			fileData += to_string(line.getPosition().y) + "\n";
			fileData += to_string(line.getRotation()) + "\n";
		}
	}
	return fileData;
}

void btnFuncQuitProgram()
{
	exit(0);
}

void btnFuncSaveChanges(IShellItem** loadedProject, CharacterSet** characterSet)
{
	string fileData = ReadCharacterSet(characterSet);
	PWSTR fileDataW = CDialogEventHandler::StrToPWSTR(fileData);
	CDialogEventHandler::SaveChanges(fileDataW, loadedProject);
}

void btnFuncSaveAs(IShellItem** loadedProject, CharacterSet** characterSet)
{
	string fileData = ReadCharacterSet(characterSet);
	PWSTR fileDataW = CDialogEventHandler::StrToPWSTR(fileData);
	CDialogEventHandler::SaveFileAs(fileDataW, loadedProject);
}

void btnFuncExportFont()
{

}

void InitiateBtnSaveChanges(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveChanges,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 30);
	*btnSaveChanges = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveChanges,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveChanges)->AddText("Save Changes", 30);
}
void InitiateBtnSaveAs(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveAs,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 100);
	*btnSaveAs = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveAs,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveAs)->AddText("Save As", 30);
}
void InitiateBtnExportFont(RenderWindow& window, Button<>** btnExportFont,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 170);
	*btnExportFont = new Button<>(window, position, &btnFuncExportFont,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnExportFont)->AddText("Export Font", 30);
}
void InitiateBtnQuitProgram(RenderWindow& window, Button<>** btnQuitProgram,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 240);
	*btnQuitProgram = new Button<>(window, position, &btnFuncQuitProgram,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnQuitProgram)->AddText("Quit Program", 30);
}


MenuDialog::MenuDialog(RenderWindow& window, CharacterSet** characterSet, IShellItem** loadedProject,
	Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->loadedProject = loadedProject;
	this->characterSet = characterSet;
	Vector2f startingOffset = CalculateStartingOffset();
	FloatRect bgroundRect = this->dialogBground->getLocalBounds();
	InitiateBtnSaveChanges(window, &(this->btnSaveChanges), bgroundRect, startingOffset);
	InitiateBtnSaveAs(window, &(this->btnSaveAs), bgroundRect, startingOffset);
	InitiateBtnExportFont(window, &(this->btnExportFont), bgroundRect, startingOffset);
	InitiateBtnQuitProgram(window, &(this->btnQuitProgram), bgroundRect, startingOffset);
}

void MenuDialog::Draw()
{
	if (this->isOpen)
	{
		DrawEssentials();
		btnSaveChanges->Draw(*window);
		btnSaveAs->Draw(*window);
		btnExportFont->Draw(*window);
		btnQuitProgram->Draw(*window);
	}
}

void MenuDialog::Move(Vector2f offset)
{
	MoveEssentials(offset);
	btnSaveChanges->Move(offset);
	btnSaveAs->Move(offset);
	btnExportFont->Move(offset);
	btnQuitProgram->Move(offset);
}

bool MenuDialog::Update(Event& event)
{
	if (isOpen)
	{
		if (btnCloseDialog->Update(event, isOpen, parentScreen->GetInteractability()))
			return false;
		CheckForDragging(event);
		btnSaveChanges->Update(event, loadedProject, characterSet);
		btnSaveAs->Update(event, loadedProject, characterSet);
		btnExportFont->Update(event);
		btnQuitProgram->Update(event);
	}
	return true;
}

MenuDialog::~MenuDialog()
{
	delete btnSaveChanges;
	delete btnSaveAs;
	delete btnExportFont;
	delete btnQuitProgram;
}
