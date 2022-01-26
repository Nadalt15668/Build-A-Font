#include "Button.h"

void func1(Button<>& button)
{
    button.SetColor(Color::Red);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    Button<Button<>&> button(&window, Vector2f(50, 50), &func1, DEFAULT_BUTTON_SIZE, Color::Red);
    Button<> button1(&window, Vector2f(400, 600), NULL, DEFAULT_BUTTON_SIZE);
    Font font;
    font.loadFromFile("font.ttf");
    button.AddText("banana", font, 40);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            button.Update(event, button1);
            button1.Update(event);
        }
        window.clear(Color::White);
        button.Draw();
        button1.Draw();
        window.display();
    }

    return 0;
}
