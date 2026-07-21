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

	void DrawApple(Apple* apples, int count, sf::RenderWindow& window)
	{
		// ќтрисовываем массив €блок
		for (int i = 0; i < count; ++i)
		{
			if (!apples[i].isEaten)
			{
				window.draw(apples[i].sprite);
			}
		}
	}

	void CollisionWithApple(Game& game)
	{
		// ѕроверка коллизии с €блоками
		bool isEnd = (game.modeFlags & MODE_END) != 0;
		bool isSpeed = (game.modeFlags & MODE_SPEED) != 0;
		
		for (int i = 0; i < game.numApples; ++i)
		{
			if (!game.apples[i].isEaten && IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				game.apples[i].position, APPLE_SIZE / 2.f))
			{
				if (isEnd) // яблоко не респавнитс€
				{
					game.apples[i].isEaten = true;
				}
				else
				{
					game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					game.apples[i].sprite.setPosition(game.apples[i].position.x, game.apples[i].position.y);
					game.apples[i].isEaten = false;
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


