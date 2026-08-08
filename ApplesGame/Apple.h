#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

namespace ApplesGame
{
	struct Game;
	struct Apple
	{
		// Apples data
		Position2D position;
		sf::Sprite sprite;
		bool isEaten = false;
	};

	void InitApples(Apple& apple, const sf::Texture& texture);
	void DrawApple(const std::vector<Apple>& apples, sf::RenderWindow& window);
	void CollisionWithApple(Game& game);
}