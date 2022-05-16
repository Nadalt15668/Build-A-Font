#pragma once
#include <Python.h>
#include <pybind11/embed.h>
#include "Dialog.h"
#include "FileDialog.h"
#include "TextBox.h"
#include "Button.h"
#include "CharacterSet.h"
#include "FilesWriter.h"

class ExportingDialog :
    public Dialog
{
public:
    ExportingDialog(RenderWindow& window, pybind11::module_& pythonModule, CharacterSet** characterSet,
        Screen*& parentScreen, Vector2f size, std::string dialogTitle, Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    bool Update(Event& event);
    void SetCharacterSet(CharacterSet** characterSet) { this->characterSet = *characterSet; };
    ~ExportingDialog();
private:
    pybind11::module_ pythonModule;
    IShellItem* chosenItemPath = nullptr;
    std::string chosenItemStr = "";
    TextBox* txtbxCopyright;
    TextBox* txtbxFamilyname;
    TextBox* txtbxVersion;
    sf::Text* txtChosenItem;
    CharacterSet* characterSet;
    Button<IShellItem**, std::string&, sf::Text**>* btnChooseDest;
    Button<CharacterSet**, std::string, std::string, std::string, std::string>* btnFinalExport;
};

