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

bool CheckDialogBorders(Vector2f worldPos, FloatRect area, Vector2f pos)
{
	if (!(worldPos.x > pos.x - area.width / 2 && worldPos.x < pos.x + area.width / 2) ||
		!(worldPos.y > pos.y - area.height / 2 && worldPos.y < pos.y + area.height / 2))
		return false;
	return true;
}

void Dialog::OpenDialog()
{
	this->isOpen = true;
}

void Dialog::CheckForDragging(Event& event)
{
	Vector2f topBarPos = Vector2f(this->dialogBar->getPosition().x,
		this->dialogBar->getPosition().y + this->dialogBar->getLocalBounds().height / 2);
	FloatRect holdingArea = FloatRect(Vector2f(0, 0),
		Vector2f(this->dialogBar->getLocalBounds().width * 2, this->dialogBar->getLocalBounds().height * 2));
	// ----------------- Current position of mouse in our window -----------------
	Vector2i pixelPos = sf::Mouse::getPosition(*window);
	Vector2f worldPos = window->mapPixelToCoords(pixelPos);
	// ---------------------------------------------------------------------------
	if (event.type == Event::MouseButtonReleased)
		ResetLastPos();
	if (Mouse::isButtonPressed(Mouse::Left) &&
		(lastMouseHeldPos.x == NULL || lastMouseHeldPos.y == NULL) &&
		CheckDialogBorders(worldPos, this->dialogBar->getLocalBounds(), topBarPos))
	{
		lastMouseHeldPos.x = worldPos.x;
		lastMouseHeldPos.y = worldPos.y;
	}
	else if (Mouse::isButtonPressed(Mouse::Left) &&
		(worldPos.x != lastMouseHeldPos.x || worldPos.y != lastMouseHeldPos.y) &&
		CheckDialogBorders(worldPos, holdingArea, topBarPos))
	{
		Move(Vector2f(worldPos.x - lastMouseHeldPos.x, worldPos.y - lastMouseHeldPos.y));
		lastMouseHeldPos.x = worldPos.x;
		lastMouseHeldPos.y = worldPos.y;
		// Adds offset to current position
		this->dialogPos.x += worldPos.x - lastMouseHeldPos.x;
		this->dialogPos.y += worldPos.y - lastMouseHeldPos.y;
	}
}

Dialog::Dialog(RenderWindow& window, Vector2f size, string dialogTitle, Color bgroundColor)
{
	this->dialogPos = Vector2f(Vector2f(PROGRAM_DIM.x / 2, PROGRAM_DIM.y / 2));
	this->dialogTitle = new sf::Text();
	this->window = &window;
	this->isOpen = false; 
	this->lastMouseHeldPos.x = 0;
	this->lastMouseHeldPos.y = 0;
	// Setting the dialog background
	this->dialogBground = new RectangleShape(size);
	this->dialogBground->setPosition(this->dialogPos);
	this->dialogBground->setOrigin(this->dialogBground->getLocalBounds().width / 2,
		this->dialogBground->getLocalBounds().height / 2);
	this->dialogBground->setFillColor(bgroundColor);
	this->dialogBground->setOutlineColor(DEFAULT_BAR_COLOR);
	this->dialogBground->setOutlineThickness(2);
	// Setting the top bar
	this->dialogBar = new RectangleShape(Vector2f(size.x, BAR_THICKNESS));
	this->dialogBar->setFillColor(DEFAULT_BAR_COLOR);
	this->dialogBar->setOrigin(Vector2f(this->dialogBar->getLocalBounds().width / 2, 0));
	this->dialogBar->setPosition(Vector2f(this->dialogPos.x, this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2));
	// Setting the close button
	Vector2f closeBtnPos(
		this->dialogPos.x + this->dialogBground->getLocalBounds().width / 2 - 10,
		this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2 + 10
	);
	btnCloseDialog = new Button<bool&>(window, closeBtnPos, &closeDialog,
		new RectangleShape(Vector2f(20, BAR_THICKNESS)), this->dialogBar->getFillColor());
	btnCloseDialog->AddText("X", 15, DEFAULT_FONTPATH, Color::White);
	btnCloseDialog->SetShapeOutline(0, Color::Transparent);
	// Setting the dialog title
	LoadDialogTitle(dialogTitle, this->dialogTitle);
	this->dialogTitle->setPosition(Vector2f(this->dialogPos.x,
		this->dialogPos.y - this->dialogBground->getLocalBounds().height / 2 ));
}

void Dialog::MoveEssentials(Vector2f offset)
{
	this->dialogBar->move(offset);
	this->btnCloseDialog->Move(offset);
	this->dialogTitle->move(offset);
	this->dialogBground->move(offset);
}

void Dialog::DrawEssentials()
{
	this->window->draw(*this->dialogBground);
	this->window->draw(*this->dialogBar);
	this->btnCloseDialog->Draw(*this->window);
	this->window->draw(*this->dialogTitle);
}
