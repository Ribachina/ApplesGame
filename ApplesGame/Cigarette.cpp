#include "Cigarette.h"
#include "Game.h"

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

	void CollisionWithCigarette(Game& game)
	{
		for (int i = 0; i < game.numCigarettes; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.cigarettes[i].position, { CIGARETTE_SIZE, CIGARETTE_SIZE }))
			{
				game.cigarettes[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				game.cigarettes[i].sprite.setPosition(game.cigarettes[i].position.x, game.cigarettes[i].position.y);

				game.numEatenApples += 10;

				game.text.Score.setString("Score: " + std::to_string(game.numEatenApples));

				game.audio.cigaretteSound.play();
			}
		}
	}
}