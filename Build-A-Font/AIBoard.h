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
    void Capture(map<string, vector<RectangleShape>*>* charactersData);
    void CaptNum(map<string, vector<RectangleShape>*>* charactersData);
private:
    NeuralNetwork* network;
};