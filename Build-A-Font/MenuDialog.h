#pragma once
#include "Dialog.h"
#include "ExportingDialog.h"
#include "FileDialog.h"
#include "CharacterSet.h"

class MenuDialog :
    public Dialog
{
public:
    MenuDialog(RenderWindow& window, ExportingDialog** exportDialog, pybind11::module_& pythonModule, CharacterSet** characterSet, IShellItem** loadedProject,
        Screen*& parentScreen, Vector2f size, string dialogTitle, Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    bool Update(Event& event);
    ~MenuDialog();
private:
    pybind11::module_ pythonModule;
    Button<IShellItem**, CharacterSet**>* btnSaveChanges;
    Button<IShellItem**, CharacterSet**>* btnSaveAs;
    Button<ExportingDialog**, RenderWindow&, pybind11::module_&, Screen*&>* btnExportFont;
    Button<>* btnQuitProgram;
    IShellItem** loadedProject;
    CharacterSet** characterSet;
    ExportingDialog** exportDialog;
};

