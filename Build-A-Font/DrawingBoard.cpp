#include "DrawingBoard.h"

// Sets rendered template from a givem file
bool DrawingBoard::SetTemplate(std::string filename)
{
	Texture* templateTex = new Texture();
	if (!templateTex->loadFromFile(filename))
	{
		// Handle Error
		return false;
	}
	this->shape->setTexture(templateTex);
	this->shape->setScale(0.8, 0.8);
	return true;
}

bool CheckBorders(Vector2f worldPos, FloatRect area, Vector2f pos)
{
	if (!(worldPos.x > pos.x - area.width / 2 && worldPos.x < pos.x + area.width / 2) ||
		!(worldPos.y > pos.y - area.height / 2 && worldPos.y < pos.y + area.height / 2))
		return false;
	return true;
}

// Creates a line according to mouse position and adds it to main lines vector
void DrawingBoard::CreateLine()
{
	float length = brush.CalculateLength() + 4;
	float angle = brush.CalculateAngle();
	RectangleShape newLine;
	newLine.setOrigin(Vector2f(0, BRUSH_THICKNESS / 2));
	newLine.setRotation(angle);
	newLine.setFillColor(Color::Black);
	newLine.setPosition(this->brush.prevPos);
	newLine.setSize(Vector2f(BRUSH_THICKNESS, length));
	mainLines.push_back(newLine);
}

void DrawingBoard::Update(Event& event)
{
	// ----------------- Current position of mouse in our window -----------------
	Vector2i pixelPos = sf::Mouse::getPosition(*window);
	Vector2f worldPos = window->mapPixelToCoords(pixelPos);
	// ---------------------------------------------------------------------------
	if (event.type == Event::MouseButtonReleased || 
		!CheckBorders(worldPos, FloatRect(DRAWING_POS, DRAWING_DIM), DRAWING_POS))
		brush.ResetPositions();
	if (Mouse::isButtonPressed(Mouse::Left) &&
		(brush.curPos.x == NULL || brush.curPos.y == NULL) &&
		CheckBorders(worldPos, FloatRect(DRAWING_POS, DRAWING_DIM), DRAWING_POS))
	{
		brush.curPos.x = worldPos.x;
		brush.curPos.y = worldPos.y;
	}
	else if (Mouse::isButtonPressed(Mouse::Left) &&
		(worldPos.x != brush.curPos.x || worldPos.y != brush.curPos.y) &&
		CheckBorders(worldPos, FloatRect(DRAWING_POS, DRAWING_DIM), DRAWING_POS))
	{
		brush.NewPosition(worldPos);
		CreateLine();
	}
}

void DrawingBoard::SetCurrentCharacter(std::string characterName, std::string templateFilename, std::vector<RectangleShape>& mainLines)
{
	// Sets the template as a background
	std::string drawingTemplate = templateFilename;
	SetTemplate(drawingTemplate);
	std::string replacedDir = "CharacterTemplates";
	drawingTemplate.replace(drawingTemplate.find_first_of("/") + 1, replacedDir.length(), "DrawingTemplates");
	SetTemplate(drawingTemplate);
	this->characterName = characterName;
	this->templateFilename = drawingTemplate;
	this->mainLines = mainLines;
}

// Constructor
DrawingBoard::DrawingBoard(RenderWindow& window, Vector2f center,
	Vector2f size, Vector2f vpSizeRatio, Vector2f vpLocationRatio) :
	UIElement(center, new RectangleShape(Vector2f(199,216)), Color::White)
{
	this->window = &window;
	// -------------------- Drawing Final Texture (for .png later) -------------------- 
	drawingTex.create(size.x, size.y);
	drawingTex.clear(Color::Transparent);
	// ----------------- Drawing View (The view that actually gets drawn) -----------------
	drawingView.setCenter(center);
	drawingView.setSize(size.x + 2, size.y + 2);
	drawingView.setViewport(FloatRect(vpLocationRatio.x, vpLocationRatio.y,
		vpSizeRatio.x, vpSizeRatio.y));
	SetCurrentCharacter("", BLANK_TEMPLATE, *(new std::vector<RectangleShape>));
}

void DrawingBoard::Draw(RenderWindow& window)
{
	viewLines = mainLines; // Used for actually showing the drawing
	window.setView(drawingView);
	window.draw(*this->shape);
	for (int i = 0; i < mainLines.size(); i++)
	{
		viewLines[i].move(Vector2f(PROGRAM_DIM.x / 2 + DRAWING_DIM.x / 2, (DRAWING_DIM.y / 2) - (PROGRAM_DIM.y / 3)));
		window.draw(viewLines[i]);
	}
	drawingTex.display();
	window.setView(window.getDefaultView());
}

void DrawingBoard::Draw()
{
	Draw(*this->window);
}

void DrawingBoard::Clear()
{
	mainLines.clear();
	viewLines.clear();
	drawingTex.clear(Color::Transparent);
}

bool DrawingBoard::CheckIfEmpty()
{
	return (this->characterName != "") ? false : true;
}
