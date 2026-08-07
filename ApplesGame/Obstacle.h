#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "vector"

namespace ApplesGame
{
	struct Game;
	struct Obstacle
	{
		// Obstacle data
		Position2D position;
		sf::Sprite sprite;
	};
	
	void InitObstacles(Obstacle& obstacle, const sf::Texture& texture);
	void DrawObstacles(const std::vector<Obstacle>& obstacles, sf::RenderWindow& window);
	void CollisionWithObstacle(Game& game);
}