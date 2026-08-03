#include "Obstacle.h"
#include "Game.h"

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
	
	void DrawObstacles(Obstacle* obstacles, int count, sf::RenderWindow& window)
	{
		for (int i = 0; i < count; ++i)
		{
			window.draw(obstacles[i].sprite);
		}
	}

	void CollisionWithObstacle(Game& game)
	{
		// Проверка коллизии с препяствиями
		for (int i = 0; i < game.numObstacles; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.obstacles[i].position, { OBSTACLE_SIZE, OBSTACLE_SIZE }))
			{
				if (!game.isGameOver)
				{
					game.audio.gameOverSound.play();
					UpdateLeaderboard(game);
				}
				game.isGameOver = true;
				game.gameOverTime = 0.f;
			}
		}
	}
}