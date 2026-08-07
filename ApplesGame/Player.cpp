#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// Переменные игры
		player.position = { SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;                        // 0 - право, 1 - верх, 2 - лево, 3 - низ

		// Инициализируем спрайт игрока
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}
	
	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		// Отрисовываем игрока
		player.sprite.setPosition(player.position.x, player.position.y); // Обновляем позицию

		switch (player.direction)                                        // Крутим спрайт в зависимости от нажатой клавиши управления
		{
		case PlayerDirection::Up:
		
			player.sprite.setRotation(-90.f);
			break;
		
		case PlayerDirection::Right:
		
			player.sprite.setRotation(0.f);
			break;
		
		case PlayerDirection::Down:
		
			player.sprite.setRotation(90.f);
			break;
		
		case PlayerDirection::Left:
		
			player.sprite.setRotation(0.f);
			break;
		
		}
		
		window.draw(player.sprite);                                      // Отрисовываем игрока
	}
}