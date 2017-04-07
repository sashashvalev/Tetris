//#include "ConstList.h"
const int SIZE = 32;

void drawQuad(sf::RenderWindow & window, float x, float y, sf::Color c)
{
	sf::RectangleShape rect(sf::Vector2f(SIZE - 2, SIZE - 2));
	rect.setPosition(x + 1, y + 1);
	rect.setFillColor(c);
	window.draw(rect);
}