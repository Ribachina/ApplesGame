#include "Apple.h"

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

	void DrawApple(Apple apple[], sf::RenderWindow& window)
	{
		// ќтрисовываем массив €блок
		for (int i = 0; i < NUM_APPLES; ++i)
		{
			if (!apple[i].isEaten)
			{
				window.draw(apple[i].sprite);
			}
		}
	}
}


