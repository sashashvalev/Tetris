#include "ConstList.h"
#include "drawQuad.h"
#include "ShapeIndexes.h"
#include "PartFigure.h"
#include "Map.h"

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

		if (gameOver){ gameOver = false; }

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