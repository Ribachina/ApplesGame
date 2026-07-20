#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
	struct Obstacle
	{
		// Obstacle data
		Position2D position;
		sf::Sprite sprite;
	};
	
	void InitObstacles(Obstacle& obstacle, const sf::Texture& texture);
	void DrawObstacles(Obstacle* obstacles, int count, sf::RenderWindow& window);
}

