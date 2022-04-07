#include "MenuDialog.h"

void MenuQuitProgram()
{
	exit(0);
}



MenuDialog::MenuDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{

}

MenuDialog::~MenuDialog()
{
}
