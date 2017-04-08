#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#pragma once

sf::Color colors[6] =
{
	sf::Color(255,0,0),
	sf::Color(0,255,0),
	sf::Color(0,0,255),
	sf::Color(255,0,255),
	sf::Color(0,255,255),
	sf::Color(255,255,0)
};

static const int WIDTH = 10;
static const int HEIGHT = 20;
static int SIZE = 32;