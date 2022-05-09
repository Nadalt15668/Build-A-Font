#include "TextBox.h"

void ActivateTextBox(bool& isWritable)
{
	isWritable = true;
}

int CalculateLengthOfTextBox(float textBoxWidth, int textSize, Font*& font)
{
	sf::Text testingText;
	testingText.setCharacterSize(textSize);
	testingText.setFont(*font);
	testingText.setString("_");
	float widestCharWidth = testingText.getLocalBounds().width;
	char widestCharacter = '_';
	char* currentCharacter = (char*)malloc(sizeof(char) * 2);
	for (int i = 21; i < 127; i++)
	{
		_itoa(i, currentCharacter, 10);
		testingText.setString(*currentCharacter);
		if (testingText.getLocalBounds().width > widestCharWidth)
		{
			widestCharWidth = testingText.getLocalBounds().width;
			widestCharacter = *currentCharacter;
		}
	}
	testingText.setString(widestCharacter);
	int totalOfAvailableChars = textBoxWidth / testingText.getLocalBounds().width;
	std::string testingString = "";
	for (int i = 0; i < totalOfAvailableChars; i++)
		testingString.push_back(widestCharacter);
	testingText.setString(testingString);
	while (testingText.getLocalBounds().width > textBoxWidth)
	{
		totalOfAvailableChars--;
		testingString.pop_back();
		testingText.setString(testingString);
	}
	return totalOfAvailableChars - 1;
}

TextBox::TextBox(RenderWindow& window, Vector2f pos, Vector2f size, std::string hintText, int textSize, std::string fontPath) :
	UIElement(pos, new RectangleShape(size), Color::White)
{
	SetShapeOutline(2, Color::Black);
	SetText(hintText, fontPath, textSize, HINT_TEXT_COLOR, LEFT);
	SetTextMargin(MARGIN_LEFT, 5);
	this->btnTextBox = new Button<bool&>(window, pos, &ActivateTextBox, new RectangleShape(size), Color::Transparent);
	this->font = new Font();
	this->font->loadFromFile(fontPath);
	this->hintText = hintText;
	this->textSize = textSize;
	this->window = &window;
	this->lastInputClock = new Clock();
	this->lastInputClock->restart();
	this->numOfShownCharacters = CalculateLengthOfTextBox(this->shape->getLocalBounds().width, textSize, this->font);
}

void TextBox::Draw(RenderWindow& window)
{
	window.draw(*this->shape);
	window.draw(this->text);
}

bool CheckBorders(RenderWindow& window, Vector2f mousePos, Vector2f textBoxSize, Vector2f textBoxPos)
{
	if (mousePos.x > textBoxPos.x - textBoxSize.x / 2 && mousePos.x < textBoxPos.x + textBoxSize.x / 2 &&
		mousePos.y > textBoxPos.y - textBoxSize.y / 2 && mousePos.y < textBoxPos.y + textBoxSize.y / 2)
		return true;
	return false;
};

void ManageKeyboardInput(Event& event, std::string& filledText, Clock*& lastInputClock)
{
	// Checks if a key was entered and if its a unicode character
	if (event.type == Event::TextEntered && event.text.unicode < 127)
	{
		// Checks if the key is a real character for printing
		if (event.text.unicode > 31 )
		{
			if ((filledText == "") || filledText.back() != CHARARCTER_INPUT ||
				(filledText.back() == CHARARCTER_INPUT &&
					lastInputClock->getElapsedTime().asSeconds() > ELAPSED_TIME_FOR_INPUT))
			{
				filledText.push_back(static_cast<char>(event.text.unicode));
				lastInputClock->restart();
			}
		}
		// Checks if the key is backspace
		else if (event.text.unicode == 8 && filledText != "")
		{
			if (lastInputClock->getElapsedTime().asSeconds() > ELAPSED_TIME_FOR_BACKSPACE)
			{
				filledText.pop_back();
				lastInputClock->restart();
			}
		}
	}
}

void TextBox::Update(Event& event)
{
	// Checks interaction
	Vector2i pixelPos = Mouse::getPosition(*this->window);
	Vector2f worldPos = this->window->mapPixelToCoords(pixelPos);
	this->btnTextBox->Update(event, this->isWritable);
	bool contains = CheckBorders(*this->window, worldPos, Vector2f(this->shape->getLocalBounds().width, this->shape->getLocalBounds().height),
		this->pos);
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (!contains)
		{ 
			this->isWritable = false;
			this->shape->setOutlineColor(Color::Black);
		}
	}
	// Manage keyboard input
	if (isWritable)
	{
		ManageKeyboardInput(event, this->totalText, this->lastInputClock);
		this->shape->setOutlineColor(SELECTED_TEXTBOX_COLOR);
	}
	// Sets current text
	if (totalText == "")
		SetText(hintText, HINT_TEXT_COLOR);
	else
	{
		if (totalText.length() > this->numOfShownCharacters)
			this->shownText = totalText.substr(totalText.length() - numOfShownCharacters - 1);
		else
			this->shownText = totalText;
		SetText(this->shownText, Color::Black);
	}
}

TextBox::~TextBox()
{
	delete font;
	delete btnTextBox;
	delete lastInputClock;
}


