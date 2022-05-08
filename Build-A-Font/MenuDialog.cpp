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
		{
			fileData += (*mapsKeys)[i] + FILE_DELIM; // Character Name
			fileData += to_string((*curCharData).size()) + FILE_DELIM; // Num of lines
		}
		for (auto line : *curCharData) // Writing a character's lines
		{
			fileData += to_string(line.getSize().x) + FILE_DELIM;
			fileData += to_string(line.getSize().y) + FILE_DELIM;
			fileData += to_string(line.getPosition().x) + FILE_DELIM;
			fileData += to_string(line.getPosition().y) + FILE_DELIM;
			fileData += to_string(line.getRotation()) + FILE_DELIM;
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
	int sizeofstr = sizeof(fileData);
	int sizeofpwstr = sizeof(fileDataW);
	CDialogEventHandler::SaveFileAs(fileDataW, loadedProject);
}

void btnFuncExportFont(ExportingDialog** exportDialog, RenderWindow& window, pybind11::module_& pythonMoudle, Screen*& parentScreen)
{
	*exportDialog = new ExportingDialog(window, pythonMoudle, parentScreen, Vector2f(400, 400), "Export Font");
	(*exportDialog)->OpenDialog(parentScreen->GetInteractability());
}

void InitializeBtnSaveChanges(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveChanges,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 30);
	*btnSaveChanges = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveChanges,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveChanges)->AddText("Save Changes", 30);
}
void InitializeBtnSaveAs(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveAs,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 100);
	*btnSaveAs = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveAs,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveAs)->AddText("Save As", 30);
}
void InitializeBtnExportFont(RenderWindow& window, Button<ExportingDialog**, RenderWindow&, pybind11::module_&, Screen*&>** btnExportFont,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 170);
	*btnExportFont = new Button<ExportingDialog**, RenderWindow&, pybind11::module_&, Screen*&>(window, position, &btnFuncExportFont,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnExportFont)->AddText("Export Font", 30);
}
void InitializeBtnQuitProgram(RenderWindow& window, Button<>** btnQuitProgram,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 240);
	*btnQuitProgram = new Button<>(window, position, &btnFuncQuitProgram,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnQuitProgram)->AddText("Quit Program", 30);
}

bool IsFull(CharacterSet** characterSet)
{
	map<string, vector<RectangleShape>*>* charactersMap = (*characterSet)->GetCharactersDataPtr();
	for (auto key : *(*characterSet)->GetMapsKeys())
	{
		if (charactersMap->at(key)->empty())
			return false;
	}
	return true;
}

MenuDialog::MenuDialog(RenderWindow& window, ExportingDialog** exportDialog, pybind11::module_& pythonModule, CharacterSet** characterSet, IShellItem** loadedProject,
	Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->isExportAvailable = IsFull(characterSet);
	this->pythonModule = pythonModule;
	this->exportDialog = exportDialog;
	this->loadedProject = loadedProject;
	this->characterSet = characterSet;
	Vector2f startingOffset = CalculateStartingOffset();
	FloatRect bgroundRect = this->dialogBground->getLocalBounds();
	InitializeBtnSaveChanges(window, &(this->btnSaveChanges), bgroundRect, startingOffset);
	InitializeBtnSaveAs(window, &(this->btnSaveAs), bgroundRect, startingOffset);
	InitializeBtnExportFont(window, &(this->btnExportFont), bgroundRect, startingOffset);
	InitializeBtnQuitProgram(window, &(this->btnQuitProgram), bgroundRect, startingOffset);
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
		// Checks if all drawings for characters exist
		if (this->isExportAvailable &&
			btnExportFont->Update(event, exportDialog, *this->window, this->pythonModule, this->parentScreen))
			return false;
		CheckForDragging(event);
		btnSaveChanges->Update(event, loadedProject, characterSet);
		btnSaveAs->Update(event, loadedProject, characterSet);
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
