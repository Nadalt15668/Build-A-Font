#include "ExportingDialog.h"

#define TEXTBOX_BETWEEN_SPACE (DEFAULT_TEXTBOX_DIM.y + 20)

void ChooseDest(IShellItem** chosenDest)
{

}

void FinalExport()
{

}

void InitializeTxtboxCopyright(RenderWindow& window, TextBox** txtboxCopyright, string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE + startingOffset.y);
	(*txtboxCopyright) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeTxtboxFamilyname(RenderWindow& window, TextBox** txtboxFamilyname, string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 2 + startingOffset.y);
	(*txtboxFamilyname) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeTxtboxVersion(RenderWindow& window, TextBox** txtboxVerssion, string hintText, int textSize,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_TEXTBOX_DIM.x * 1.5, DEFAULT_TEXTBOX_DIM.y);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 3 + startingOffset.y);
	(*txtboxVerssion) = new TextBox(window, pos, size, hintText, textSize);
}

void InitializeBtnChooseDest(RenderWindow& window, Button <IShellItem**> ** btnChooseDest,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(Vector2f(100, 30));
	Vector2f pos(dialogBground.width / 2 + startingOffset.x - size.x / 2 - 10, TEXTBOX_BETWEEN_SPACE * 3 + startingOffset.y + size.y + 30);
	(*btnChooseDest) = new Button<IShellItem**>(window, pos, &ChooseDest, new RectangleShape(size));
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

void InitializeBtnFinalExport(RenderWindow& window, Button <>** btnFinalExport,
	FloatRect dialogBground, Vector2f startingOffset)
{
	Vector2f size(DEFAULT_BUTTON_DIM.x *  0.6, DEFAULT_BUTTON_DIM.y *0.4);
	Vector2f pos(dialogBground.width / 2 + startingOffset.x, TEXTBOX_BETWEEN_SPACE * 4 + startingOffset.y + 70);
	(*btnFinalExport) = new Button<>(window, pos, &FinalExport, new RectangleShape(size));
	(*btnFinalExport)->AddText("Export", 30);
}

ExportingDialog::ExportingDialog(RenderWindow& window, pybind11::module_& pythonModule, Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor) :
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
		this->btnChooseDest->Update(event, &this->chosenItemPath);
		this->btnFinalExport->Update(event);
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
