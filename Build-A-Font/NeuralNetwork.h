#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>


#define PIXEL_QUANTITY 28
#define NumOfHiddenLayers 3
#define NumOfNodesInHidden 20
#define NumOfNodesInInput PIXEL_QUANTITY * PIXEL_QUANTITY
// Nodes for each pixel in the input picture (28X28)
#define NumOfNodesInOutput 10
// Nodes for each possible digit
#define SubSetSize 10
#define TimeToGoOverTrain 3
#define JUMP_SIZE 3
#define SAVE_FILE "datasave.dat"
#define UPLOAD_FILE "datasave.dat"
#define TRAIN_DATA "Dataset/train_data.idx3-ubyte"
#define TRAIN_LABEL "Dataset/train_labels.idx1-ubyte"
#define TEST_DATA "Dataset/test_data.idx3-ubyte"
#define TEST_LABEL "Dataset/test_labels.idx1-ubyte"
typedef double HiddenW[NumOfNodesInHidden][NumOfNodesInHidden];

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(std::string fileName);
	int Calc(double* input);
	void SaveToFile(std::string fileName);
	void Backprop(std::vector<double*> input, std::vector<int> label, double jumpSize);
	void Learn(std::vector<double*>& input, std::vector<int>& label, double jumpSize);
	void Test(std::vector<double*>& input, std::vector<int>& label);
	void InsertInput(const char* dataName, const char* labelName, int mode);

private:
	std::vector<double> layers[NumOfHiddenLayers + 2];
	std::vector<double> bias[NumOfHiddenLayers + 1];
	double inputW[NumOfNodesInHidden][NumOfNodesInInput];
	double outputW[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWs[NumOfHiddenLayers - 1];
};
