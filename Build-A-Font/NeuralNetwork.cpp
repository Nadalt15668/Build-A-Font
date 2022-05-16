#include "NeuralNetwork.h"
#define FLIP_ENDIANS(number) ((number >> 24) | ((number << 8) & 0x00ff0000) | ((number >> 8) & 0x0000ff00) | (number << 24))
#define SIGMOID(x) (1 / (1 + exp(-x)))
#define SIGMOID_DERIVATIVE(x) (x * (1 - x))

double RandomDouble() {
	std::uniform_real_distribution<double> unif(-1, 1);
	return unif(random_engine);
}

void BuildMatrix(int n, int m, double* matrix, bool buildMode) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * m + j] = (buildMode) ? RandomDouble() : 0;
		}
	}
}
// changes a weight matrix's gradient we found
void SubtractGradient(int n, int m, double* matrix, double* matrixG, double jumpSize, int setLen)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * m + j] -= (jumpSize / (double)setLen) * matrixG[i * m + j];
		}
	}
}

NeuralNetwork::NeuralNetwork()
{
	layers[0].resize(NODES_IN_INPUT);
	layers[HIDDEN_LAYERS + 1].resize(NODES_IN_OUTPUT);
	bias[HIDDEN_LAYERS].resize(NODES_IN_OUTPUT);
	for (int i = 1; i <= HIDDEN_LAYERS; i++)
	{
		layers[i].resize(NODES_IN_HIDDEN);
		bias[i - 1].resize(NODES_IN_HIDDEN);
	}
	BuildMatrix(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputW, true);
	BuildMatrix(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputW, true);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		BuildMatrix(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWs[i]), true);
	}
	for (int i = 0; i <= HIDDEN_LAYERS; i++)
		for (auto& b : bias[i])
			b = RandomDouble();
}

NeuralNetwork::NeuralNetwork(std::string fileName)
{
	layers[0].resize(NODES_IN_INPUT);
	layers[HIDDEN_LAYERS + 1].resize(NODES_IN_OUTPUT);
	bias[HIDDEN_LAYERS].resize(NODES_IN_OUTPUT);
	for (int i = 1; i <= HIDDEN_LAYERS; i++)
	{
		layers[i].resize(NODES_IN_HIDDEN);
		bias[i - 1].resize(NODES_IN_HIDDEN);
	}
	std::ifstream file(fileName, std::ofstream::binary);
	if (!file)
		return;

	// mod bias
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		int len = bias[i].size();
		for (int j = 0; j < len; j++) {
			file.read((char*)&(bias[i][j]), sizeof(double));
		}
	}

	// mod input to first hidden
	for (int i = 0; i < NODES_IN_HIDDEN; i++) {
		for (int j = 0; j < NODES_IN_INPUT; j++) {
			file.read((char*)&(inputW[i][j]), sizeof(double));
		}
	}

	// mod last hidden to output
	for (int i = 0; i < NODES_IN_OUTPUT; i++) {
		for (int j = 0; j < NODES_IN_HIDDEN; j++) {
			file.read((char*)&(outputW[i][j]), sizeof(double));
		}
	}

	// mod from hidden to hidden
	for (int k = 0; k < HIDDEN_LAYERS - 1; k++) {
		for (int i = 0; i < NODES_IN_HIDDEN; i++) {
			for (int j = 0; j < NODES_IN_HIDDEN; j++) {
				file.read((char*)&(hiddenWs[k][i][j]), sizeof(double));
			}
		}
	}
	file.close();
}

int NeuralNetwork::CheckDigit(double* drawing)
{
	// from input to first hidden
	for (int i = 0; i < NODES_IN_INPUT; i++) {
		layers[0][i] = drawing[i];
	}

	for (int i = 0; i < NODES_IN_HIDDEN; i++) {
		layers[1][i] = bias[0][i];
		for (int j = 0; j < NODES_IN_INPUT; j++) {
			layers[1][i] += layers[0][j] * inputW[i][j];
		}
		layers[1][i] = SIGMOID(layers[1][i]);
	}

	// from every to hidden 
	for (int k = 0; k < HIDDEN_LAYERS - 1; k++) {
		for (int i = 0; i < NODES_IN_HIDDEN; i++) {
			layers[k + 2][i] = bias[k + 1][i];
			for (int j = 0; j < NODES_IN_HIDDEN; j++) {
				layers[k + 2][i] += layers[k + 1][j] * hiddenWs[k][i][j];
			}
			layers[k + 2][i] = SIGMOID(layers[k + 2][i]);
		}
	}

	// from last hidden to output
	for (int i = 0; i < NODES_IN_OUTPUT; i++) {
		layers[HIDDEN_LAYERS + 1][i] = bias[HIDDEN_LAYERS][i];
		for (int j = 0; j < NODES_IN_HIDDEN; j++) {
			layers[HIDDEN_LAYERS + 1][i] += layers[HIDDEN_LAYERS][j] * outputW[i][j];
		}
		layers[HIDDEN_LAYERS + 1][i] = SIGMOID(layers[HIDDEN_LAYERS + 1][i]);
	}

	//find the max output
	int maxn = 0;
	for (int i = 0; i < NODES_IN_OUTPUT; i++)
	{
		if (layers[HIDDEN_LAYERS + 1][i] > layers[HIDDEN_LAYERS + 1][maxn])
			maxn = i;
	}
	return maxn;
}

void NeuralNetwork::WriteNN(std::string fileName)
{
	std::ofstream file(fileName, std::ofstream::binary);
	if (!file) {
		return;
	}

	// mod bias
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		int len = bias[i].size();
		for (int j = 0; j < len; j++) {
			file.write((const char*)&(bias[i][j]), sizeof(double));
		}
	}

	// mod input to first hidden
	for (int i = 0; i < NODES_IN_HIDDEN; i++) {
		for (int j = 0; j < NODES_IN_INPUT; j++) {
			file.write((const char*)&(inputW[i][j]), sizeof(double));
		}
	}

	// mod last hidden to output
	for (int i = 0; i < NODES_IN_OUTPUT; i++) {
		for (int j = 0; j < NODES_IN_HIDDEN; j++) {
			file.write((const char*)&(outputW[i][j]), sizeof(double));
		}
	}

	// mod from hidden to hidden
	for (int k = 0; k < HIDDEN_LAYERS - 1; k++) {
		for (int i = 0; i < NODES_IN_HIDDEN; i++) {
			for (int j = 0; j < NODES_IN_HIDDEN; j++) {
				file.write((const char*)&(hiddenWs[k][i][j]), sizeof(double));
			}
		}
	}
	file.close();
}



void NeuralNetwork::Backpropagate(double learningRate)
{
	double inputWG[NODES_IN_HIDDEN][NODES_IN_INPUT];
	double outputWG[NODES_IN_OUTPUT][NODES_IN_HIDDEN];
	HiddenW hiddenWsG[HIDDEN_LAYERS - 1];
	std::vector<double> biasG[HIDDEN_LAYERS + 1];
	std::vector<double> error[HIDDEN_LAYERS + 2];
	int SetLen = drawings.size();

	error[0].resize(NODES_IN_INPUT);
	error[HIDDEN_LAYERS + 1].resize(NODES_IN_OUTPUT);
	biasG[HIDDEN_LAYERS].resize(NODES_IN_OUTPUT);

	// set the size of error and biasG vectors
	for (int i = 1; i <= HIDDEN_LAYERS; i++)
	{
		error[i].resize(NODES_IN_HIDDEN);
		biasG[i - 1].resize(NODES_IN_HIDDEN);
	}

	// set all the gradient arrs to 0
	BuildMatrix(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputWG, false);
	BuildMatrix(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputWG, false);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		BuildMatrix(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWsG[i]), false);
	}
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		for (auto& b : biasG[i]) {
			b = 0;
		}
	}

	// reset the error
	for (int t = 0; t < SetLen; t++) {
		for (int p = 0; p < HIDDEN_LAYERS + 2; p++) {
			for (auto& e : error[p]) {
				e = 0;
			}
		}
		for (int j = 0; j < NODES_IN_OUTPUT; j++) {
			// error(L,j) = Dsig(Z(L,j)) * (a(L,j) - y(j))
			error[HIDDEN_LAYERS + 1][j] = SIGMOID_DERIVATIVE(layers[HIDDEN_LAYERS + 1][j]) *
				(layers[HIDDEN_LAYERS + 1][j] - (labels[t] == j));
			for (int k = 0; k < NODES_IN_HIDDEN; k++) {
				// error(l, k) = sumForEveryJ(w(l+1,j,k) * error(j, l+1) * Dsig(z(l, k)))
				error[HIDDEN_LAYERS][k] += outputW[j][k] * error[HIDDEN_LAYERS + 1][j]
					* SIGMOID_DERIVATIVE(layers[HIDDEN_LAYERS][k]);
				// dc/dw(l,j,k) = a(l-1, k) * error(l, j)
				outputWG[j][k] += layers[HIDDEN_LAYERS][k] * error[HIDDEN_LAYERS + 1][j];
			}
			// dc/db(l, j) = error(l,j)
			biasG[HIDDEN_LAYERS][j] += error[HIDDEN_LAYERS + 1][j];
		}

		// calc back for all hiddens
		for (int ly = HIDDEN_LAYERS - 2; ly >= 0; ly--) {
			int l = ly + 2;
			for (int j = 0; j < NODES_IN_HIDDEN; j++) {
				for (int k = 0; k < NODES_IN_HIDDEN; k++) {
					// error(l, k) = sumForAllJ(W(l+1, j, k)*error(l+1, j)*Dsig(z(l, k)))
					error[l - 1][k] += hiddenWs[ly][j][k] * error[l][j]
						* SIGMOID_DERIVATIVE(layers[l - 1][k]);
					// dc/dw(l,j,k) = a(l-1, k) * error(l, j)
					hiddenWsG[ly][j][k] += layers[l - 1][k] * error[l][j];
				}
				// dc/db(l, j) = error(l,j)
				biasG[l - 1][j] += error[l][j];
			}
		}

		// calc for input
		for (int j = 0; j < NODES_IN_HIDDEN; j++) {
			for (int k = 0; k < NODES_IN_INPUT; k++) {
				// dc/dw(l,j,k) = a(l-1, k) * error(l, j)
				inputWG[j][k] += layers[0][k] * error[1][j];
			}
			// dc/db(l, j) = error(l,j)
			biasG[0][j] += error[1][j];
		}
	}

	// change all the w matrixs with the gradients we found
	SubtractGradient(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputW, *inputWG, learningRate, SetLen);
	SubtractGradient(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputW, *outputWG, learningRate, SetLen);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		SubtractGradient(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWs[i]), *(hiddenWsG[i]), learningRate, SetLen);
	}
	// change the bias with the gradient we found
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		int bLen = bias[i].size();
		for (int j = 0; j < bLen; j++) {
			bias[i][j] -= (learningRate / (double)SetLen) * biasG[i][j];
		}
	}
}

void randomize(std::vector<double*>& input, std::vector<int>& label)
{
	int s = input.size();
	for (int i = 0; i < s; i++)
	{
		int k = rand() % s;
		std::swap(input[i], input[k]);
		std::swap(label[i], label[k]);
	}
}

void NeuralNetwork::TeachNN(double learningRate)
{
	int totalSize = drawings.size();
	std::vector<double*> trainSet;
	std::vector<int> labelSet;
	for (int t = 0; t < NUM_OF_EPOCHS; t++)
	{
		randomize(drawings, labels);
		for (int i = 0; i < totalSize / SUBSET_SIZE; i++)
		{
			for (int j = 0; j < SUBSET_SIZE; j++)
			{
				trainSet.push_back(drawings[SUBSET_SIZE * i + j]);
				labelSet.push_back(labels[SUBSET_SIZE * i + j]);
			}
			Backpropagate(learningRate);
			trainSet.clear();
			labelSet.clear();
		}
	}
}

double NeuralNetwork::CheckNN()
{
	int datasetSize = drawings.size();
	int correctAnswers = 0;
	for (int i = 0; i < datasetSize; i++)
		correctAnswers += (CheckDigit(drawings[i]) == labels[i]) ? 1 : 0;
	return (double)correctAnswers / datasetSize;
}

void NeuralNetwork::ReadMNIST(std::string drawingsFilename, std::string labelsFilename)
{
	// Opens images set file
	FILE* drawingsFile = fopen(drawingsFilename.c_str(), "rb");
	FILE* labelsFile = fopen(labelsFilename.c_str(), "rb");
	if (!drawingsFile || !labelsFile)
		exit(0);
	// Reads number of images in file
	std::fseek(drawingsFile, 4, SEEK_SET);
	std::fread(&this->datasetSize, 4, 1, drawingsFile);
	datasetSize = FLIP_ENDIANS(datasetSize);
	// Skips to information in both files
	std::fseek(drawingsFile, 16, SEEK_SET);
	std::fseek(labelsFile, 8, SEEK_SET);
	// Reads files information
	for (int i = 0; i < datasetSize; i++)
	{
		// An image matrix
		double* currentDrawing = new double[28 * 28];
		for (int j = 0; j < 28 * 28; j++)
		{
			// Reads 28X28 bytes for each image
			bool currentPixel; // A byte for a pixel 
			fread(&currentPixel, 1, 1, drawingsFile);
			currentDrawing[j] = (double)currentPixel / 255;
		}
		drawings.push_back(currentDrawing);
		bool currentLabel;
		fread(&currentLabel, 1, 1, labelsFile);
		labels.push_back((int)currentLabel);
	}
	fclose(drawingsFile);
	fclose(labelsFile);
}

void NeuralNetwork::RunNN(std::string drawingsFilename, std::string labelsFilename, bool networkMode)
{
	ReadMNIST(drawingsFilename, labelsFilename);
	if (networkMode)
	{
		TeachNN(LEARNING_RATE);
		if (SAVE_FILE != "0")
			WriteNN(SAVE_FILE);
	}
	else
		CheckNN();
}
