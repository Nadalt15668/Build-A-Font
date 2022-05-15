#include "AIBoard.h"

AIBoard::AIBoard(RenderWindow& window,
	Vector2f center,
	Vector2f size,
	Vector2f vpSizeRatio,
	Vector2f vpLocationRatio) :
	DrawingBoard(window, center, size, vpSizeRatio, vpLocationRatio)
{
	/*if (UPLOAD_FILE == "0")
		network = new NeuralNetwork();
	else
		network = new NeuralNetwork(UPLOAD_FILE);
	if (UPLOAD_FILE == "0")
	{
		network->ReadMNIST(MNIST_TRAIN_DATA, MNIST_TRAIN_LABEL);
		network->TeachNN(LEARNING_RATE);
	}*/
	if (UPLOAD_FILE == "0")
		network = new NeuralNetwork();
	else
		network = new NeuralNetwork(UPLOAD_FILE);
	if (UPLOAD_FILE == "0")
		network->InsertInput(MNIST_TRAIN_DATA, MNIST_TRAIN_LABEL, 1);
	network->InsertInput(MNIST_TEST_DATA, MNIST_TEST_LABEL, 0);
	
}

cv::Mat sfImg2cvImg(const sf::Image& img) {
	//get size from image
	cv::Size size(img.getSize().x, img.getSize().y);
	//create a mat on image memory
	cv::Mat mat(size, CV_8UC4, (void*)img.getPixelsPtr(), cv::Mat::AUTO_STEP);
	//make SFML RGBA to OpenCV BGRA
	cv::cvtColor(mat, mat, cv::COLOR_RGBA2GRAY);
	//clone mat to avoid memory editing on image memory
	return mat.clone();
}

void AIBoard::Capture(std::map<std::string, std::vector<RectangleShape>*>* charactersData)
{
	(*charactersData)[this->characterName]->clear();
	for (auto line : this->mainLines)
		(*charactersData)[this->characterName]->push_back(line);
}

void AIBoard::CaptNum(std::map<std::string, std::vector<RectangleShape>*>* charactersData)
{
	// Build a RenderTexture to convert to an opencv::Image
	RectangleShape texLine;
	RenderTexture tex;
	tex.create(DRAWING_DIM.x, DRAWING_DIM.y);
	tex.clear(Color::Black);
	for (auto line : this->mainLines)
	{
		texLine = line;
		texLine.move(-DRAWING_POS.x + DRAWING_DIM.x / 2, -DRAWING_POS.y + DRAWING_DIM.y / 2);
		texLine.setFillColor(Color::White);
		tex.draw(texLine);
	}
	tex.display();
	// Copies the RenderTexture to an sf::Image
	sf::Image sfImage = tex.getTexture().copyToImage();
	// Converts the sf::Image to a opencv::Image
	cv::Mat cvImage = sfImg2cvImg(sfImage);
	cv::Mat cvImageResized;
	// Resizes the image to the required size for the NN
	cv::resize(cvImage, cvImageResized, cv::Size(DRAWING_SIZE, DRAWING_SIZE), cv::INTER_LINEAR);
	// Creates an array of doubles from the image with each value between 0 (black) to 1 (white)
	double* input = new double[DRAWING_SIZE * DRAWING_SIZE];
	for (int r = 0; r < cvImageResized.rows; r++)
	{
		for (int c = 0; c < cvImageResized.cols; c++)
		{
			input[r * cvImageResized.cols + c] = (double)(cvImageResized.at<unsigned char>(r, c)) / 255;
		}
	}
	// Retrieves the result from the NN and saves the drawing accordingly
	std::string result = std::to_string(network->Calc(input));
	// Saves the data of the number the NN 'thought' the number is - for undoing purposes
	this->lastNumDrawing = *((*charactersData)[result]);
	// If its the first character drawn, save it as the last character
	this->lastNumName = result;
	// Changes the current chosen character on the drawing board and replaces the data of the drawing
	this->characterName = result;
	(*charactersData)[result]->clear();
	for (auto line : this->mainLines)
		(*charactersData)[result]->push_back(line);
}

void AIBoard::UndoNum(std::map<std::string, std::vector<RectangleShape>*>* charactersData)
{
	if (this->lastNumName != "")
	{
		(*charactersData)[this->lastNumName]->clear();
			for (auto line : (this->lastNumDrawing))
				(*charactersData)[this->lastNumName]->push_back(line);
	}
}
