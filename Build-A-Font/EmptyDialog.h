#pragma once
#include "Dialog.h"
class EmptyDialog :
    public Dialog
{
public:
    EmptyDialog(RenderWindow& window, Vector2f size, string dialogTitle = "", Color bgroundColor = DEFAULT_DIALOG_COLOR);
    void Draw();
    void Move(Vector2f offset);
    void Update(Event& event);
};

