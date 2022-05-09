#pragma once
#include <opencv2/opencv.hpp>
#include "DrawingBoard.h"
#include "NeuralNetwork.h"

class AIBoard :
    public DrawingBoard
{
public:
    AIBoard(RenderWindow& window, Vector2f center, Vector2f size,
        Vector2f vpSizeRatio, Vector2f vpLocationRatio);
    void Capture(std::map<std::string, std::vector<RectangleShape>*>* charactersData);
    void CaptNum(std::map<std::string, std::vector<RectangleShape>*>* charactersData);
    void UndoNum(std::map<std::string, std::vector<RectangleShape>*>* charactersData);
private:
    NeuralNetwork* network;
    std::vector<RectangleShape> lastNumDrawing;
    std::string lastNumName;
};