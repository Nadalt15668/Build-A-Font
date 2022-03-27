#pragma once
#include "Screen.h"

using namespace sf;
using namespace std;

class EmptyPage :
    public Screen
{
public:
    EmptyPage();
    void Draw();
    void Update(Event& event);
private:
};

