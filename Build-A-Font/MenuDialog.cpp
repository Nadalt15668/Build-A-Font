#include "MenuDialog.h"

// Reads the characterSet into a full string
std::string ReadCharacterSet(CharacterSet** characterSet)
{
	std::string fileData = "";
	std::vector<std::string>* mapsKeys = (*characterSet)->GetMapsKeys();
	std::map<std::string, std::vector<RectangleShape>*>* charactersData = (*characterSet)->GetCharactersDataPtr();
	// Runs through the map using the map's keys
	for (int i = 0; i < (*mapsKeys).size(); i++)
	{
		std::vector<RectangleShape>* curCharData = (*charactersData)[(*mapsKeys)[i]];
		if ((*curCharData).size() != 0)
		{
			fileData += (*mapsKeys)[i] + FILE_DELIM; // Character Name
			fileData += std::to_string((*curCharData).size()) + FILE_DELIM; // Num of lines
		}
		for (auto line : *curCharData) // Writing a character's lines
		{
			fileData += std::to_string(line.getSize().x) + FILE_DELIM;
			fileData += std::to_string(line.getSize().y) + FILE_DELIM;
			fileData += std::to_string(line.getPosition().x) + FILE_DELIM;
			fileData += std::to_string(line.getPosition().y) + FILE_DELIM;
			fileData += std::to_string(line.getRotation()) + FILE_DELIM;
		}
	}
	return fileData;
}

// Button function
void btnFuncQuitProgram()
{
	exit(0);
}

// Button function
void btnFuncSaveChanges(IShellItem** loadedProject, CharacterSet** characterSet)
{
	std::string fileData = ReadCharacterSet(characterSet);
	PWSTR fileDataW = CDialogEventHandler::StrToPWSTR(fileData);
	CDialogEventHandler::SaveChanges(fileDataW, loadedProject);
}

// Button function
void btnFuncSaveAs(IShellItem** loadedProject, CharacterSet** characterSet)
{
	std::string fileData = ReadCharacterSet(characterSet);
	PWSTR fileDataW = CDialogEventHandler::StrToPWSTR(fileData);
	int sizeofstr = sizeof(fileData);
	int sizeofpwstr = sizeof(fileDataW);
	CDialogEventHandler::SaveFileAs(fileDataW, loadedProject);
}

// Button function
void btnFuncExportFont(ExportingDialog** exportDialog, RenderWindow& window, pybind11::module_& pythonMoudle, CharacterSet** characterSet,
	Screen*& parentScreen)
{
	*exportDialog = new ExportingDialog(window, pythonMoudle, characterSet, parentScreen, Vector2f(400, 400), "Export Font");
	(*exportDialog)->OpenDialog(parentScreen->GetInteractability());
}

// Element initialization function
void InitializeBtnSaveChanges(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveChanges,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 30);
	*btnSaveChanges = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveChanges,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveChanges)->AddText("Save Changes", 30);
}

// Element initialization function
void InitializeBtnSaveAs(RenderWindow& window, Button<IShellItem**, CharacterSet**>** btnSaveAs,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 100);
	*btnSaveAs = new Button<IShellItem**, CharacterSet**>(window, position, &btnFuncSaveAs,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnSaveAs)->AddText("Save As", 30);
}

// Element initialization function
void InitializeBtnExportFont(RenderWindow& window, Button<ExportingDialog**, RenderWindow&, pybind11::module_&, CharacterSet**, Screen*&>** btnExportFont,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 170);
	*btnExportFont = new Button<ExportingDialog**, RenderWindow&, pybind11::module_&, CharacterSet**,
		Screen*&>(window, position, &btnFuncExportFont,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnExportFont)->AddText("Export Font", 30);
}

// Element initialization function
void InitializeBtnQuitProgram(RenderWindow& window, Button<>** btnQuitProgram,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(170, 50));
	Vector2f position(dialogBground.width / 2 + startingOffset.x, startingOffset.y + size.y / 2 + 240);
	*btnQuitProgram = new Button<>(window, position, &btnFuncQuitProgram,
		new RectangleShape(size), Color(200, 200, 200));
	(*btnQuitProgram)->AddText("Quit Program", 30);
}

// Checks if all characters are drawn
bool IsFull(CharacterSet** characterSet)
{
	std::map<std::string, std::vector<RectangleShape>*>* charactersMap = (*characterSet)->GetCharactersDataPtr();
	for (auto key : *(*characterSet)->GetMapsKeys())
	{
		if (charactersMap->at(key)->empty())
			return false;
	}
	return true;
}

// Constructor
MenuDialog::MenuDialog(RenderWindow& window, ExportingDialog** exportDialog, pybind11::module_& pythonModule, CharacterSet** characterSet, IShellItem** loadedProject,
	Screen*& parentScreen, Vector2f size, std::string dialogTitle, Color bgroundColor) :
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
			btnExportFont->Update(event, exportDialog, *this->window, this->pythonModule, this->characterSet, this->parentScreen))
			return false;
		CheckForDragging(event);
		btnSaveChanges->Update(event, loadedProject, characterSet);
		btnSaveAs->Update(event, loadedProject, characterSet);
		btnQuitProgram->Update(event);
	}
	return true;
}

// Destructor
MenuDialog::~MenuDialog()
{
	delete btnSaveChanges;
	delete btnSaveAs;
	delete btnExportFont;
	delete btnQuitProgram;
}
