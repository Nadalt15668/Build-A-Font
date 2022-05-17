#include "ExportingDialog.h"
#include <string>
#include <regex>
#include <filesystem>
#include <atlstr.h>
#include <shellapi.h>
#define TEXTBOX_BETWEEN_SPACE (DEFAULT_TEXTBOX_DIM.y + 20)

bool CheckPath(std::string& str) {
	for (auto c : str) {
		if (static_cast<unsigned char>(c) > 127 || static_cast<unsigned char>(c) == 63) {
			return false;
		}
	}
	return true;
}

void ChooseDest(IShellItem** chosenDest, std::string& chosenItemStr, sf::Text** txtChosenItem)
{
	chosenItemStr = CDialogEventHandler::ChooseFolder(chosenDest);
	if (CheckPath(chosenItemStr))
	{
		chosenItemStr = std::regex_replace(chosenItemStr, std::regex("\\\\"), "/"); // replace '\\' -> '/'
		(*txtChosenItem)->setString("OK");
		(*txtChosenItem)->setFillColor(Color::Green);
		(*txtChosenItem)->setOrigin((*txtChosenItem)->getLocalBounds().width / 2, (*txtChosenItem)->getLocalBounds().height / 2);
	}
	else
	{
		chosenItemStr = "";
		(*txtChosenItem)->setString("ERROR");
		(*txtChosenItem)->setFillColor(Color::Red);
		(*txtChosenItem)->setOrigin((*txtChosenItem)->getLocalBounds().width / 2, (*txtChosenItem)->getLocalBounds().height / 2);
	}
}

void FinalExport(CharacterSet** characterSet, std::string copyright, std::string familyname, std::string version, std::string path)
{
	std::filesystem::create_directory("./Temps"); 
	std::filesystem::create_directory(TEMPORARY_DIR);
	for (auto key : *(*characterSet)->GetMapsKeys())
		FilesWriter::WriteCharacterSVG(key, &(*characterSet)->GetCharactersDataPtr()->at(key));
	FilesWriter::CreateSpacePNG();
	//FilesWriter::WriteConversionBAT(*(*characterSet)->GetMapsKeys()); // Written once
	// Structure of information for the execution of the shell
	SHELLEXECUTEINFOW shellInfo;
	// Converting the filename from std::string to std::LPCWSTR
	std::string file = (std::string)".\\" + (std::string)CONV_SCRIPT;
	std::wstring wfile(file.begin(), file.end());
	// Setting the execution information
	shellInfo.lpVerb = L"open";
	shellInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NO_CONSOLE | SEE_MASK_NOCLOSEPROCESS;
	shellInfo.hwnd = NULL;
	shellInfo.lpFile = wfile.c_str();
	shellInfo.lpParameters = NULL;
	shellInfo.lpDirectory = NULL;
	shellInfo.nShow = SW_SHOWMINIMIZED;
	shellInfo.cbSize = sizeof(shellInfo);
	// Converting png to svg
	ShellExecuteEx(&shellInfo);
	WaitForSingleObject(shellInfo.hProcess, INFINITE);
	CloseHandle(shellInfo.hProcess);
	FilesWriter::WriteJSON(copyright, familyname, version, path);
	// Converting the filename from std::string to std::LPCWSTR
	file = (std::string)".\\" + (std::string)SVGS2TTF;
	wfile = std::wstring(file.begin(), file.end());
	shellInfo.lpFile = wfile.c_str();
	// Making a font file
	ShellExecuteEx(&shellInfo);
	WaitForSingleObject(shellInfo.hProcess, INFINITE);
	CloseHandle(shellInfo.hProcess);
	std::filesystem::remove_all(TEMPORARY_DIR);
}

void InitializeTxtboxCopyright(RenderWindow& window, TextBox** txtboxCopyright, std::string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE + startingOffset.y);
	(*txtboxCopyright) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeTxtboxFamilyname(RenderWindow& window, TextBox** txtboxFamilyname, std::string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 2 + startingOffset.y);
	(*txtboxFamilyname) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeTxtboxVersion(RenderWindow& window, TextBox** txtboxVerssion, std::string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 3 + startingOffset.y);
	(*txtboxVerssion) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeBtnChooseDest(RenderWindow& window, Button <IShellItem**, std::string&, sf::Text**> ** btnChooseDest,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(100, 30));
	Vector2f pos(dialogBground.width / 2 + startingOffset.x - size.x / 2 - 10, TEXTBOX_BETWEEN_SPACE * 3 + startingOffset.y + size.y + 30);
	(*btnChooseDest) = new Button<IShellItem**, std::string&, sf::Text**>(window, pos, &ChooseDest, new RectangleShape(size));
	(*btnChooseDest)->AddText("Choose...", 25);
}

void InitializeTextChosenPath(RenderWindow& window, sf::Text** txtChosenPath,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Font* font = new Font;
	font->loadFromFile(DEFAULT_FONTPATH);
	(*txtChosenPath) = new sf::Text("No Chosen Path", *font, 25);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x + (*txtChosenPath)->getLocalBounds().width / 2 + 10,
		TEXTBOX_BETWEEN_SPACE * 3 + startingOffset.y + (*txtChosenPath)->getLocalBounds().height * 1.25 + 30);
	(*txtChosenPath)->setOrigin((*txtChosenPath)->getLocalBounds().width / 2, (*txtChosenPath)->getLocalBounds().height / 2);
	(*txtChosenPath)->setFillColor(Color::Black);
	(*txtChosenPath)->setPosition(pos);
}

void InitializeBtnFinalExport(RenderWindow& window, Button <CharacterSet**, std::string, std::string, std::string, std::string>** btnFinalExport,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_BUTTON_DIM.x *  0.6, DEFAULT_BUTTON_DIM.y *0.4);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 4 + startingOffset.y + 70);
	(*btnFinalExport) = new Button<CharacterSet**, std::string, std::string, std::string, std::string>(window, pos, &FinalExport, new RectangleShape(size));
	(*btnFinalExport)->AddText("Export", 30);
}

ExportingDialog::ExportingDialog(RenderWindow& window, pybind11::module_& pythonModule, CharacterSet** characterSet, Screen*& parentScreen, Vector2f size, std::string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->isDraggable = false;
	this->pythonModule = pythonModule;
	Vector2f startingOffset = CalculateStartingOffset();
	FloatRect bgroundRect = this->dialogBground->getLocalBounds();
	InitializeTxtboxCopyright(window, &this->txtbxCopyright, "Enter Font's Copyright", TEXTBOX_TEXT_SIZE, bgroundRect, startingOffset);
	InitializeTxtboxFamilyname(window, &this->txtbxFamilyname, "Enter Font's Familyname", TEXTBOX_TEXT_SIZE, bgroundRect, startingOffset);
	InitializeTxtboxVersion(window, &this->txtbxVersion, "Enter Font's Version", TEXTBOX_TEXT_SIZE, bgroundRect, startingOffset);
	InitializeBtnChooseDest(window, &this->btnChooseDest, bgroundRect, startingOffset);
	InitializeTextChosenPath(window, &this->txtChosenItem, bgroundRect, startingOffset);
	InitializeBtnFinalExport(window, &this->btnFinalExport, bgroundRect, startingOffset);
}

void ExportingDialog::Draw()
{
	if (this->isOpen)
	{
		DrawEssentials();
		this->txtbxCopyright->Draw(*this->window);
		this->txtbxFamilyname->Draw(*this->window);
		this->txtbxVersion->Draw(*this->window);
		this->btnFinalExport->Draw(*this->window);
		this->btnChooseDest->Draw(*this->window);
		this->window->draw(*this->txtChosenItem);
	}
}

void ExportingDialog::Move(Vector2f offset)
{
	MoveEssentials(offset);
	this->txtbxCopyright->Move(offset);
	this->txtbxFamilyname->Move(offset);
	this->txtbxVersion->Move(offset);
	this->btnChooseDest->Move(offset);
	this->btnFinalExport->Move(offset);
	this->txtChosenItem->move(offset);
}

bool ExportingDialog::Update(Event& event)
{
	if (isOpen)
	{
		if (btnCloseDialog->Update(event, isOpen, parentScreen->GetInteractability()))
			return false;
		CheckForDragging(event);
		this->txtbxCopyright->Update(event);
		this->txtbxFamilyname->Update(event);
		this->txtbxVersion->Update(event);
		this->btnChooseDest->Update(event, &this->chosenItemPath, this->chosenItemStr, &this->txtChosenItem);
		if (this->txtbxCopyright->IsFilled() &&
			this->txtbxFamilyname->IsFilled() &&
			this->txtbxVersion->IsFilled() &&
			this->chosenItemStr != "") // Only if all fields are filled
				this->btnFinalExport->Update(event, &this->characterSet, this->txtbxCopyright->GetText(), 
					this->txtbxFamilyname->GetText(), this->txtbxVersion->GetText(), this->chosenItemStr);
	}
	return true;
}

ExportingDialog::~ExportingDialog()
{
	delete btnChooseDest;
	delete btnFinalExport;
	delete txtbxCopyright;
	delete txtbxFamilyname;
	delete txtbxVersion;
	delete txtChosenItem;
}
