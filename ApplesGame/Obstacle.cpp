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
	
	void DrawObstacles(const std::vector<Obstacle>& obstacles, sf::RenderWindow& window)
	{
		for (const auto& obstacle : obstacles)
		{
			window.draw(obstacle.sprite);
		}
	}

	void CollisionWithObstacle(Game& game)
	{
		// Проверка коллизии с препяствиями
		for (auto& obstacle : game.obstacles)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				obstacle.position, { OBSTACLE_SIZE, OBSTACLE_SIZE }))
			{
				if (!game.isGameOver)
				{
					game.audio.gameOverSound.play();
					UpdateLeaderboard(game);
				}
				game.isGameOver = true;
				game.gameOverTime = 0.f;
				// Переключаем на GameOver
				PopState(game);
				PushState(game, GameState::GameOver);
			}
		}
	}
}