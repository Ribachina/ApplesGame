#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
	struct Apple
	{
		// Apples data
		Position2D position;
		sf::Sprite sprite;
		bool isEaten = false;
	};

	void InitApples(Apple& apple, const sf::Texture& texture);
	void DrawApple(Apple* apples, int count, sf::RenderWindow& window);

}


