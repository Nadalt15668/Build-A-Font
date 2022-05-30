#pragma once
#include "Brush.h"
#include "UIElement.h"

#define FILE_SAVED_TO "File successfully saved to "
#define ERROR_WHILE_OPENING "An error has accured while opening the file"
#define ERROR_WHILE_LOADING "An error has accured while loading the file"
#define ERROR_ACCURED "An error has accured"
#define FILE_TYPE ".txt"

class DrawingBoard :
    public UIElement
{
public:
    DrawingBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocation);
    bool SetTemplate(std::string filename);
    virtual void Capture(std::map<std::string, std::vector<RectangleShape>*>* charactersData) = 0;
    void CreateLine();
    void Update(Event& event);
    void SetCurrentCharacter(std::string characterName, std::string templateFilename, std::vector<RectangleShape>& mainLines);
    void Draw();
    void Clear();
    bool CheckIfEmpty();
protected:
    void Draw(RenderWindow& window);
    RenderTexture drawingTex;
    RenderWindow* window;
    Brush brush;
    std::string templateFilename;
    std::string characterName;
    std::vector<RectangleShape> mainLines; // Actual mouse input
    std::vector<RectangleShape> viewLines; //Lines in the View
    View drawingView;
};

