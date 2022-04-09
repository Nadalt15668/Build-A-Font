#pragma once
#include "Brush.h"
#include "UIElement.h"
class DrawingBoard :
    public UIElement
{
public:
    DrawingBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocation);
    bool SetTemplate(string filename);
    virtual void Capture(map<string, vector<RectangleShape>*>* charactersData) = 0;
    void CreateLine();
    void Update(Event& event);
    void RemoveBackground();
    void SetCurrentCharacter(string characterName, string templateFilename, vector<RectangleShape>& mainLines);
    void Draw();
    void Clear();
protected:
    void Draw(RenderWindow& window);
    RenderTexture drawingTex;
    RenderWindow* window;
    Brush brush;
    string templateFilename;
    string characterName;
    vector<RectangleShape> mainLines; // Actual mouse input
    vector<RectangleShape> viewLines; //Lines in the View
    View drawingView;
};

