#include "ConstList.h"
#include "ShapeIndexes.h"
#include "drawQuad.h"

class PartFigure
{
private:
	int shapeIndex;
	int data[4][4], posX, posY;

	void fillData()
	{
		for (int i = 0; i < 4; i++)
			for (int m = 0; m < 4; m++)
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
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if ((data[y][x] && (posX + x + xOffset >= WIDTH || posX + xOffset < 0)) || (data[y][x] && (posY + y + yOffset > HEIGHT)))
				{
					return false;
				}

		return true;
	}

	void draw(sf::RenderWindow & window)
	{
		for (int i = 0; i < 4; i++)
			for (int m = 0; m < 4; m++)
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