#pragma once
#include "Dialog.h"
#include "FileDialog.h"
class MenuDialog :
    public Dialog
{
public:
    MenuDialog(RenderWindow& window, Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor = DEFAULT_DIALOG_COLOR);
    ~MenuDialog();
private:
    Button<IShellItem**, IShellItem**>* btnSaveToFile;
    Button<>* btnSaveAs;
    Button<>* btnExportFont;
    Button<>* btnQuitProgram;
};

