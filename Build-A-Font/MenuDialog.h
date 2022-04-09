#pragma once
#include "Dialog.h"
#include "FileDialog.h"
#include "CharacterSet.h"

class MenuDialog :
    public Dialog
{
public:
    MenuDialog(RenderWindow& window, CharacterSet** characterSet, IShellItem** loadedProject,
        Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    bool Update(Event& event);
    ~MenuDialog();
private:
    Button<IShellItem**, CharacterSet**>* btnSaveChanges;
    Button<IShellItem**, CharacterSet**>* btnSaveAs;
    Button<>* btnExportFont;
    Button<>* btnQuitProgram;
    IShellItem** loadedProject;
    CharacterSet** characterSet;
};

