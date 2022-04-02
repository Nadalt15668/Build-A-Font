#include "EmptyDialog.h"

EmptyDialog::EmptyDialog(RenderWindow& window, Vector2f size, string dialogTitle, Color bgroundColor) :
	Dialog(window, size, dialogTitle, bgroundColor)
{
}

void EmptyDialog::Draw()
{
	if (this->isOpen)
	{
		DrawEssentials();
	}
}

void EmptyDialog::OpenDialog()
{
	this->isOpen = true;
}

void EmptyDialog::Update(Event& event)
{
	if (isOpen)
		btnCloseDialog->Update(event, isOpen);
}
