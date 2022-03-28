#include "TextBox.h"

void ActivateTextBox(Vector2f lastClickedPosition)
{

}

TextBox::TextBox(RenderWindow& window, Vector2f pos, Vector2f size, string hintText, int textSize, string fontPath) :
	UIElement(pos, new RectangleShape(size), Color::White)
{
	SetShapeOutline(2, Color::Black);
	SetText(hintText, fontPath, textSize, HINT_TEXT_COLOR, LEFT);
	SetTextMargin(MARGIN_LEFT, 5);
	this->btnTextBox = new Button<Vector2f>(window, pos, &ActivateTextBox, new RectangleShape(size), Color::Transparent);
	this->font = new Font();
	this->font->loadFromFile(fontPath);
	this->hintText = hintText;
	this->textSize = textSize;
}

void TextBox::Draw(RenderWindow& window)
{
	window.draw(*this->shape);
	window.draw(this->text);
}
