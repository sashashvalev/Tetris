#include "ConstList.h"

void drawQuad(sf::RenderWindow & window, float x, float y, sf::Color c)
{
	sf::RectangleShape rect(sf::Vector2f(SIZE, SIZE));
	rect.setPosition(x + 1, y + 1);
	rect.setFillColor(c);
	window.draw(rect);
}