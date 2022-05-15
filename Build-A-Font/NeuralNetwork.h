#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include "Constants.h"

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
	std::vector<double> layers[HIDDEN_LAYERS + 2];
	std::vector<double> bias[HIDDEN_LAYERS + 1];
	double inputW[NODES_IN_HIDDEN][NODES_IN_INPUT];
	double outputW[NODES_IN_OUTPUT][NODES_IN_HIDDEN];
	double hiddenWs[NODES_IN_HIDDEN][NODES_IN_HIDDEN][HIDDEN_LAYERS - 1];
};
