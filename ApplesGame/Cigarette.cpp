#include "Cigarette.h"

namespace ApplesGame {

	void InitCigarette(Cigarette& cigarette, const sf::Texture& texture)
	{
		// Инициализация сигареты
		cigarette.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		cigarette.sprite.setTexture(texture);
		cigarette.sprite.setPosition(cigarette.position.x, cigarette.position.y);
		SetSpriteSize(cigarette.sprite, CIGARETTE_SIZE, CIGARETTE_SIZE);
		SetSpriteRelativeOrigin(cigarette.sprite, 0.5f, 0.5f);
	}
	void DrawCigarette(Cigarette* cigarettes, int count, sf::RenderWindow& window)
	{
		for (int i = 0; i < count; ++i)
		{
			window.draw(cigarettes[i].sprite);
		}
	}
}