#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
	struct Game;
	
	struct Cigarette
	{
		// Cigarette data
		Position2D position;
		sf::Sprite sprite;
	};
	void InitCigarette(Cigarette& cigarette, const sf::Texture& texture);
	void DrawCigarette(Cigarette* cigarettes, int count, sf::RenderWindow& window);
	void CollisionWithCigarette(Game& game);
}
