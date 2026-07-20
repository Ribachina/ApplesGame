#include "Obstacle.h"

namespace ApplesGame
{
	void InitObstacles(Obstacle& obstacle, const sf::Texture& texture)
	{
		// Инициализация препятствий
		obstacle.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		obstacle.sprite.setTexture(texture);
		obstacle.sprite.setPosition(obstacle.position.x, obstacle.position.y);
		SetSpriteSize(obstacle.sprite, OBSTACLE_SIZE, OBSTACLE_SIZE);
		SetSpriteRelativeOrigin(obstacle.sprite, 0.5f, 0.5f);

	}
	void DrawObstacles(Obstacle obstacle[], sf::RenderWindow& window)
	{
		for (int i = 0; i < NUM_OBSTACLE; ++i)
		{
			window.draw(obstacle[i].sprite);
		}
	}
}


