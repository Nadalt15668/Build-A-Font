#include "ExportingDialog.h"

ExportingDialog::ExportingDialog(RenderWindow& window, pybind11::module_& pythonModule, Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor) :
	Dialog(window, parentScreen, size, dialogTitle, bgroundColor)
{
	this->pythonModule = pythonModule;
}

void ExportingDialog::Draw()
{
	if (this->isOpen)
	{
		DrawEssentials();
	}
}

void ExportingDialog::Move(Vector2f offset)
{
	MoveEssentials(offset);
}

bool ExportingDialog::Update(Event& event)
{
	if (isOpen)
	{
		if (btnCloseDialog->Update(event, isOpen, parentScreen->GetInteractability()))
			return false;
		CheckForDragging(event);
	}
	return true;
}

ExportingDialog::~ExportingDialog()
{
}
