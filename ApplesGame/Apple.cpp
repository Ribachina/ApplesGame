#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{

	void InitApples(Apple& apple, const sf::Texture& texture)
	{
		// »нициализаци€ €блок
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		apple.isEaten = false;

		apple.sprite.setTexture(texture);
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);

	}

	void DrawApple(const std::vector<Apple>& apples, sf::RenderWindow& window)
	{
		// ќтрисовываем массив €блок
		for (const auto& apple : apples)
		{
			window.draw(apple.sprite);
		}
	}
	}

	void CollisionWithApple(Game& game)
	{
		// ѕроверка коллизии с €блоками
		bool isEnd = (game.modeFlags & MODE_END) != 0;
		bool isSpeed = (game.modeFlags & MODE_SPEED) != 0;
		
		for (auto& apple : game.apples)
		{
			if (!apple.isEaten && IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				apple.position, APPLE_SIZE / 2.f))
			{
				if (isEnd) // яблоко не респавнитс€
				{
					apple.isEaten = true;
				}
				else
				{
					apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					apple.sprite.setPosition(apple.position.x, apple.position.y);
					apple.isEaten = false;
				}
				if (isSpeed) // –ежим Speed —корость растЄт при поедании €блок
				{
					game.player.speed += SPEED_PLUS;
					if (game.player.speed > MAX_SPEED)
					{
						game.player.speed = MAX_SPEED;
					}
				}
					game.numEatenApples++;

					game.text.Score.setString("Score: " + std::to_string(game.numEatenApples));

					game.audio.eatSound.play();
			}
		}
	}
}
