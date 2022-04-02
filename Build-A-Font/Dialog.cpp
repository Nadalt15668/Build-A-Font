#include "Dialog.h"

void closeDialog(bool& isOpen)
{
	isOpen = false;
}

bool LoadDialogTitle(string dialogString, sf::Text*& dialogTitle)
{
	Font* font = new Font;
	font->loadFromFile(DEFAULT_FONTPATH);
	dialogTitle->setFont(*font);
	dialogTitle->setString(dialogString);
	dialogTitle->setCharacterSize(15);
	dialogTitle->setFillColor(Color::White);
	dialogTitle->setOrigin(dialogTitle->getLocalBounds().width / 2, 0);
	return true;
}

Dialog::Dialog(RenderWindow& window, Vector2f size, string dialogTitle, Color bgroundColor)
{
	this->dialogPos = Vector2f(Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.y / 2));
	this->dialogTitle = new sf::Text();
	this->window = &window;
	this->isOpen = false;
	// Setting the dialog background
	this->dialogBground = new RectangleShape(size);
	this->dialogBground->setPosition(this->dialogPos);
	this->dialogBground->setOrigin(this->dialogBground->getLocalBounds().width / 2,
		this->dialogBground->getLocalBounds().height / 2);
	this->dialogBground->setFillColor(bgroundColor);
	this->dialogBground->setOutlineColor(DEFAULT_BAR_COLOR);
	this->dialogBground->setOutlineThickness(2);
	// Setting the top bar
	this->bar = new RectangleShape(Vector2f(size.x, BAR_THICKNESS));
	this->bar->setFillColor(DEFAULT_BAR_COLOR);
	this->bar->setOrigin(Vector2f(this->bar->getLocalBounds().width / 2, 0));
	this->bar->setPosition(Vector2f(this->dialogPos.x, this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2));
	// Setting the close button
	Vector2f closeBtnPos(
		this->dialogPos.x + this->dialogBground->getLocalBounds().width / 2 - 10,
		this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2 + 10
	);
	btnCloseDialog = new Button<bool&>(window, closeBtnPos, &closeDialog,
		new RectangleShape(Vector2f(20, BAR_THICKNESS)), this->bar->getFillColor());
	btnCloseDialog->AddText("X", 15, DEFAULT_FONTPATH, Color::White);
	btnCloseDialog->SetShapeOutline(0, Color::Transparent);
	// Setting the dialog title
	LoadDialogTitle(dialogTitle, this->dialogTitle);
	this->dialogTitle->setPosition(Vector2f(this->dialogPos.x,
		this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2 ));
}

void Dialog::DrawEssentials()
{
	this->window->draw(*this->dialogBground);
	this->window->draw(*this->bar);
	this->btnCloseDialog->Draw(*this->window);
	this->window->draw(*this->dialogTitle);
}
