#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>

//#include "ConstList.h"
#include "drawQuad.h"
#include "ShapeIndexes.h"

const int WIDTH = 10;
const int HEIGHT = 20;

class PartFigure
{
private:
	int shapeIndex;
	int data[4][4], posX, posY;

	void fillData()
	{
		for (int i = 0;i < 4;i++)
			for (int m = 0;m < 4;m++)
				data[i][m] = SHAPES[shapeIndex][i][m];
	}

public:
	PartFigure()
	{
		posX = 4;
		posY = -3;
		generate();
	}

	int color;
	void generate()
	{
		int g = (rand() % 7) * 4;
		shapeIndex = (ShapeIndexes)g;
		color = g / 4;
		fillData();	
	}

	void move(int x, int y)
	{
		if (isValid(x, y))
		{
			posX += x;
			posY += y;
		}

	}

	void rotate()
	{
		int coIndex = shapeIndex;
		shapeIndex = ((shapeIndex + 1) % 4 == 0 ? shapeIndex - 3 : shapeIndex + 1);
		fillData();
		if (!isValid())
		{
			shapeIndex = coIndex;
			fillData();
		}
	}

	bool isValid(int xOffset = 0, int yOffset = 0)
	{
		for (int y = 0;y < 4;y++)
			for (int x = 0;x < 4;x++)
				if ((data[y][x] && (posX + x + xOffset >= WIDTH || posX + xOffset < 0)) || (data[y][x] && (posY + y + yOffset > HEIGHT)))
				{
					return false;
				}

		return true;
	}

	void draw(sf::RenderWindow & window)
	{
		for (int i = 0;i < 4;i++)
			for (int m = 0;m < 4;m++)
				if (data[i][m])
				{
					drawQuad(window, (m + posX) * SIZE, (i + posY) * SIZE, sf::Color::Green);
				}
	}

	int getPosX()
	{
		return posX;
	}

	int getPosY()
	{
		return posY;
	}

	int getElement(int x, int y)
	{
		return data[y][x];
	}
};

class Map
{
private:
	int data[HEIGHT][WIDTH];
	
public:
	Map()
	{
		reset();
	}

	void reset()
	{
	for (int y = 0;y < HEIGHT;y++)
		for (int x = 0;x < WIDTH;x++)
			data[y][x] = 0;
	}

	bool isCollision(PartFigure part)
	{
		for (int y = 0;y < 4;y++)
			for (int x = 0;x < 4;x++)
				if ((part.getPosY() + y >= 0) && ((data[part.getPosY() + y + 1][part.getPosX() + x] && part.getElement(x, y)) ||
					(part.getElement(x, y) && part.getPosY() + y >= HEIGHT - 1)))
					return true;

		return false;
	}

	void addPartFigure(PartFigure part)
	{
		for (int y = 0;y < 4;y++)
			for (int x = 0;x < 4;x++)
				if (part.getElement(x, y))
					data[part.getPosY() + y][part.getPosX() + x] = 1;
	}

	void applyGravity(int h)
	{
		for (int y = h;y > -1;y--)
			for (int x = 0;x < WIDTH;x++)
				if (y < HEIGHT - 1 && data[y + 1][x] == 0 && data[y][x])
				{
					data[y][x] = 0;
					data[y + 1][x] = 1;
				}
	}

	void destroyLines()
	{
		for (int y = 0;y < HEIGHT;y++)
		{
			bool good = true;
			for (int x = 0;x < WIDTH;x++)
				if (!data[y][x])
				{
					good = false;
					break;
				}
			if (good)
			{
				for (int x = 0;x < WIDTH;x++)
					data[y][x] = 0;
				applyGravity(y);
				y = 0;
			}
		}
	}

	bool isFull()
	{
		for (int x = 0;x < WIDTH;x++)
			if (data[0][x])
				return true;
		return false;
	}

	void draw(sf::RenderWindow & window)
	{
		for (int i = 0;i < HEIGHT;i++)
			for (int m = 0;m < WIDTH;m++)
				if (data[i][m])
					drawQuad(window, m * SIZE, i * SIZE, sf::Color::Green);
	}

};

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH * SIZE, HEIGHT * SIZE), "Tetris", sf::Style::None);
	int speed = 60;
	window.setFramerateLimit(speed);

	Map map;
	PartFigure part;
	int tick = 0;
	bool gameOver = false;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){ window.close(); }
			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			{
				PartFigure p = part;
				part.move(1, 0);
				if (map.isCollision(part))
					part = p;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			{
				PartFigure p = part;
				part.move(-1, 0);
				if (map.isCollision(part))
					part = p;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) 
			{
				PartFigure p = part;
				part.move(0, 1);
				if (map.isCollision(part))
					part = p;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
			{
				PartFigure p = part;
				part.rotate();
				if (map.isCollision(part))
					part = p;
			}
		} 
		
		window.clear(sf::Color(32,32,32));		
		window.setFramerateLimit(speed);

		if (gameOver)
		{
			speed = 180;
			gameOver = false;
		}

		if (tick % 30 == 0){ part.move(0, 1); }

		if (map.isCollision(part))
		{
			map.addPartFigure(part);
			map.destroyLines();
			part = PartFigure();
		}

		map.draw(window);
		part.draw(window);

		if (tick <= 30){ tick++; }
		else{ tick = 1; }

		if (map.isFull())
		{
			map.reset();
			gameOver = true;
		}
		window.display();
	}
	 
	return 0;
}