#include "ConstList.h"
#include "ShapeIndexes.h"
#include "PartFigure.h"

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
		for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
				data[y][x] = 0;
	}

	bool isCollision(PartFigure part)
	{
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if ((part.getPosY() + y >= 0) && ((data[part.getPosY() + y + 1][part.getPosX() + x] && part.getElement(x, y)) ||
					(part.getElement(x, y) && part.getPosY() + y >= HEIGHT - 1)))
					return true;

		return false;
	}

	void addPartFigure(PartFigure part)
	{
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if (part.getElement(x, y))
					data[part.getPosY() + y][part.getPosX() + x] = 1;
	}

	void applyGravity(int h)
	{
		for (int y = h; y > -1; y--)
			for (int x = 0; x < WIDTH; x++)
				if (y < HEIGHT - 1 && data[y + 1][x] == 0 && data[y][x])
				{
					data[y][x] = 0;
					data[y + 1][x] = 1;
				}
	}

	void destroyLines()
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			bool good = true;
			for (int x = 0; x < WIDTH; x++)
				if (!data[y][x])
				{
					good = false;
					break;
				}
			if (good)
			{
				for (int x = 0; x < WIDTH; x++)
					data[y][x] = 0;
				applyGravity(y);
				y = 0;
			}
		}
	}

	bool isFull()
	{
		for (int x = 0; x < WIDTH; x++)
			if (data[0][x])
				return true;
		return false;
	}

	void draw(sf::RenderWindow & window)
	{
		for (int i = 0; i < HEIGHT; i++)
			for (int m = 0; m < WIDTH; m++)
				if (data[i][m])
					drawQuad(window, m * SIZE, i * SIZE, sf::Color::Green);
	}

};