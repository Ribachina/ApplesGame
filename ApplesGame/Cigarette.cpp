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
	
	void DrawCigarette(const std::vector<Cigarette>& cigarettes, sf::RenderWindow& window)
	{
		for (const auto& cigarette : cigarettes)
		{
			window.draw(cigarette.sprite);
		}
	}

	void CollisionWithCigarette(Game& game)
	{
		for (auto& cigarette : game.cigarettes)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				cigarette.position, { CIGARETTE_SIZE, CIGARETTE_SIZE }))
			{
				cigarette.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				cigarette.sprite.setPosition(cigarette.position.x, cigarette.position.y);

				game.numEatenApples += 10;

				game.text.Score.setString("Score: " + std::to_string(game.numEatenApples));

				game.audio.cigaretteSound.play();
			}
		}
	}
}