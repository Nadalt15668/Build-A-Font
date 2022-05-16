#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <string>
#include "Constants.h"

static std::default_random_engine random_engine;
typedef double HiddenW[NODES_IN_HIDDEN][NODES_IN_HIDDEN];

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(std::string fileName);
	void RunNN(std::string drawingsFilename, std::string labelsFilename, bool networkMode);
	int CheckDigit(double* drawing);
protected:
	void ReadMNIST(std::string drawingsFilename, std::string labelsFilename);
	void Backpropagate(double learningRate);
	void TeachNN(double learningRate);
	double CheckNN();
	void WriteNN(std::string fileName);
private:
	std::vector<double*> drawings;
	std::vector<int> labels;
	int datasetSize;
	std::vector<double> layers[HIDDEN_LAYERS + 2];
	std::vector<double> bias[HIDDEN_LAYERS + 1];
	double inputW[NODES_IN_HIDDEN][NODES_IN_INPUT];
	double outputW[NODES_IN_OUTPUT][NODES_IN_HIDDEN];
	HiddenW hiddenWs[HIDDEN_LAYERS - 1];
};
