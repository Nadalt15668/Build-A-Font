#include "NeuralNetwork.h"

void OpenFile(FILE*& file, const char* fileName)
{
	file = fopen(fileName, "rb");
	if (!(file))
	{
		std::cout << "can't open file" << std::endl;
		return;
	}
}

double GetRand() {
	return (rand() % 2001 - 1000.0) / 1000.0;
}

void RandMat(int n, int m, double* matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * m + j] = GetRand();
		}
	}
}

void SetMat(int n, int m, double* matrix, int val = 0) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * m + j] = val;
		}
	}
}
// changes a weight matrix's gradient we found
void SubByG(int n, int m, double* matrix, double* matrixG, double jumpSize, int setLen)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * m + j] -= (jumpSize / (double)setLen) * matrixG[i * m + j];
		}
	}
}

double func(double x) {
	return (1 / (1 + exp(-x)));
}

double funcD(double sigX)
{
	return sigX * (1 - sigX);
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
	RandMat(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputW);
	RandMat(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputW);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		RandMat(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWs[i]));
	}
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		for (auto& b : bias[i]) {
			b = GetRand();
		}
	}

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
	if (!file) {
		std::cout << "cant open file" << std::endl;
		return;
	}

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



int NeuralNetwork::Calc(double* input)
{
	// from input to first hidden
	for (int i = 0; i < NODES_IN_INPUT; i++) {
		layers[0][i] = input[i];
	}

	for (int i = 0; i < NODES_IN_HIDDEN; i++) {
		layers[1][i] = bias[0][i];
		for (int j = 0; j < NODES_IN_INPUT; j++) {
			layers[1][i] += layers[0][j] * inputW[i][j];
		}
		layers[1][i] = func(layers[1][i]);
	}

	// from every to hidden 
	for (int k = 0; k < HIDDEN_LAYERS - 1; k++) {
		for (int i = 0; i < NODES_IN_HIDDEN; i++) {
			layers[k + 2][i] = bias[k + 1][i];
			for (int j = 0; j < NODES_IN_HIDDEN; j++) {
				layers[k + 2][i] += layers[k + 1][j] * hiddenWs[k][i][j];
			}
			layers[k + 2][i] = func(layers[k + 2][i]);
		}
	}

	// from last hidden to output
	for (int i = 0; i < NODES_IN_OUTPUT; i++) {
		layers[HIDDEN_LAYERS + 1][i] = bias[HIDDEN_LAYERS][i];
		for (int j = 0; j < NODES_IN_HIDDEN; j++) {
			layers[HIDDEN_LAYERS + 1][i] += layers[HIDDEN_LAYERS][j] * outputW[i][j];
		}
		layers[HIDDEN_LAYERS + 1][i] = func(layers[HIDDEN_LAYERS + 1][i]);
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

void NeuralNetwork::SaveToFile(std::string fileName)
{
	std::ofstream file(fileName, std::ofstream::binary);
	if (!file) {
		std::cout << "cant open file" << std::endl;
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



void NeuralNetwork::Backprop(std::vector<double*> input, std::vector<int> label, double jumpSize)
{
	double inputWG[NODES_IN_HIDDEN][NODES_IN_INPUT];
	double outputWG[NODES_IN_OUTPUT][NODES_IN_HIDDEN];
	double hiddenWsG[NODES_IN_HIDDEN][NODES_IN_HIDDEN][HIDDEN_LAYERS - 1];
	std::vector<double> biasG[HIDDEN_LAYERS + 1];
	std::vector<double> error[HIDDEN_LAYERS + 2];
	int SetLen = input.size();

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
	SetMat(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputWG);
	SetMat(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputWG);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		SetMat(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWsG[i]));
	}
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		for (auto& b : biasG[i]) {
			b = 0;
		}
	}

	// reset the error
	for (int t = 0; t < SetLen; t++) {
		std::cout << label[t] << "l" << std::endl;
		std::cout << Calc(input[t]) << "c" << std::endl;
		for (int p = 0; p < HIDDEN_LAYERS + 2; p++) {
			for (auto& e : error[p]) {
				e = 0;
			}
		}
		for (int j = 0; j < NODES_IN_OUTPUT; j++) {
			// error(L,j) = Dsig(Z(L,j)) * (a(L,j) - y(j))
			error[HIDDEN_LAYERS + 1][j] = funcD(layers[HIDDEN_LAYERS + 1][j]) *
				(layers[HIDDEN_LAYERS + 1][j] - (label[t] == j));
			for (int k = 0; k < NODES_IN_HIDDEN; k++) {
				// error(l, k) = sumForEveryJ(w(l+1,j,k) * error(j, l+1) * Dsig(z(l, k)))
				error[HIDDEN_LAYERS][k] += outputW[j][k] * error[HIDDEN_LAYERS + 1][j]
					* funcD(layers[HIDDEN_LAYERS][k]);
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
						* funcD(layers[l - 1][k]);
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
	SubByG(NODES_IN_HIDDEN, NODES_IN_INPUT, *inputW, *inputWG, jumpSize, SetLen);
	SubByG(NODES_IN_OUTPUT, NODES_IN_HIDDEN, *outputW, *outputWG, jumpSize, SetLen);
	for (int i = 0; i < HIDDEN_LAYERS - 1; i++) {
		SubByG(NODES_IN_HIDDEN, NODES_IN_HIDDEN, *(hiddenWs[i]), *(hiddenWsG[i]), jumpSize, SetLen);
	}
	// change the bias with the gradient we found
	for (int i = 0; i <= HIDDEN_LAYERS; i++) {
		int bLen = bias[i].size();
		for (int j = 0; j < bLen; j++) {
			bias[i][j] -= (jumpSize / (double)SetLen) * biasG[i][j];
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

void NeuralNetwork::Learn(std::vector<double*>& input, std::vector<int>& label, double jumpSize)
{
	int totalSize = input.size();
	std::vector<double*> trainSet;
	std::vector<int> labelSet;
	for (int t = 0; t < EPOCHS; t++)
	{
		randomize(input, label);
		for (int i = 0; i < totalSize / SET_SIZE; i++)
		{
			for (int j = 0; j < SET_SIZE; j++)
			{
				trainSet.push_back(input[SET_SIZE * i + j]);
				labelSet.push_back(label[SET_SIZE * i + j]);
			}
			Backprop(trainSet, labelSet, jumpSize);
			trainSet.clear();
			labelSet.clear();
		}
	}
}

void NeuralNetwork::Test(std::vector<double*>& input, std::vector<int>& label)
{
	int len = input.size();
	int cor = 0;
	for (int i = 0; i < len; i++)
	{
		if (Calc(input[i]) == label[i])
			cor++;
	}
	std::cout << (double)cor / len << std::endl;
}

void NeuralNetwork::InsertInput(const char* dataName, const char* labelName, int mode)
{
	unsigned int fileLen = 0;
	std::vector<double*> inputV;
	std::vector<int> labelV;
	// Opens images set file
	FILE* fdata = NULL;
	OpenFile(fdata, dataName);
	// Opens labels set file
	FILE* flabel = NULL;
	OpenFile(flabel, labelName);
	// Reads number of images in file
	std::fseek(fdata, 4, SEEK_SET);
	std::fread(&fileLen, 4, 1, fdata);
	fileLen = (fileLen >> 24) |
		((fileLen << 8) & 0x00ff0000) |
		((fileLen >> 8) & 0x0000ff00) |
		(fileLen << 24);
	std::cout << fileLen << std::endl;
	// Skips to information in both files
	std::fseek(fdata, 16, SEEK_SET);
	std::fseek(flabel, 8, SEEK_SET);
	// Reads files information
	for (int i = 0; i < fileLen; i++)
	{
		// An image matrix
		double* temp = new double[28 * 28];
		for (int j = 0; j < 28 * 28; j++)
		{
			// Reads 28X28 bytes for each image
			bool n; // A byte for a pixel 
			fread(&n, 1, 1, fdata);
			temp[j] = (double)n / 255;
		}
		inputV.push_back(temp);
		bool n;
		fread(&n, 1, 1, flabel);
		labelV.push_back((int)n);
	}
	fclose(fdata);
	fclose(flabel);

	if (mode)
	{
		Learn(inputV, labelV, LEARNING_RATE);
		if (SAVE_FILE != "0")
			SaveToFile(SAVE_FILE);
	}
	else
		Test(inputV, labelV);

	for (int i = 0; i < fileLen; i++)
		delete inputV[i];
}
