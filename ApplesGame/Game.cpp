#include "Game.h"
#include <cassert>
#include <iostream>

namespace ApplesGame
{
	void ResetGame(Game& game)
	{

			InitPlayer(game.player, game);

			for (int i = 0; i < game.numApples; ++i)
			{
				InitApples(game.apples[i], game.appleTexture);
			}

			for (int i = 0; i < game.numObstacles; ++i)
			{
				InitObstacles(game.obstacles[i], game.obstacleTexture);
			}

			for (int i = 0; i < game.numCigarettes; ++i)
			{
				InitCigarette(game.cigarettes[i], game.cigaretteTexture);
			}

			InitText(game.text);

			game.numEatenApples = 0;
			game.isGameOver = false;
			game.gameOverTime = 0.f;
			game.isGameWin = false;
			game.isGameStart = false;
			game.text.Score.setString("Score: 0");
	}

	
	void InitGame(Game& game)
	{
		game.playerTexture.loadFromFile(RESOURCES_PATH + "Dima.png");
		game.appleTexture.loadFromFile(RESOURCES_PATH + "Coffe.png");
		game.obstacleTexture.loadFromFile(RESOURCES_PATH + "Maks.png");
		game.cigaretteTexture.loadFromFile(RESOURCES_PATH + "Cigarette.png");

		game.apples = new Apple[game.numApples]; // Выделяем память для яблок
		game.obstacles = new Obstacle[game.numObstacles]; // Выделяем память для препядствий
		game.cigarettes = new Cigarette[game.numCigarettes]; // Выделяем память для бонусов
		
		InitAudio(game.audio);

		ResetGame(game);
	}

	void CollisionWithApple(Game& game)
	{
		// Проверка коллизии с яблоками
		for (int i = 0; i < game.numApples; ++i)
		{
			if (!game.apples[i].isEaten && IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
				game.apples[i].position, APPLE_SIZE / 2.f))
			{
				game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				game.apples[i].sprite.setPosition(game.apples[i].position.x, game.apples[i].position.y);

				game.apples[i].isEaten = false;

				game.numEatenApples++;

				game.text.Score.setString("Score: " + std::to_string(game.numEatenApples));

				game.audio.eatSound.play();
			}
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
				}
				game.isGameOver = true;
				game.gameOverTime = 0.f;
			}
		}
	}

	void CollisionWithCigarette(Game& game)
	{
		for (int i = 0; i < game.numCigarettes; ++i)
		{
			if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
				game.cigarettes[i].position, {CIGARETTE_SIZE, CIGARETTE_SIZE}))
			{
				game.cigarettes[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				game.cigarettes[i].sprite.setPosition(game.cigarettes[i].position.x, game.cigarettes[i].position.y);

				game.numEatenApples += 10;
				
				game.text.Score.setString("Score: " + std::to_string(game.numEatenApples));

				game.audio.cigaretteSound.play();
			}
		}
	}

	// Обновление состояния игры
	void UpdateGame(Game& game, float deltaTime)
	{
		if (!game.isGameStart)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game.isGameStart = true;
			}
			return;
		}
		
		if (!game.isGameOver && !game.isGameWin)
			// Управление
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))                         // проверяем
			{                                                                                                                           // какие
				game.player.direction = PlayerDirection::Right;                                                                         // клавиши
			}                                                                                                                           // нажаты
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))                       // и
			{                                                                                                                           // меняем
				game.player.direction = PlayerDirection::Up;                                                                            // направление
			}                                                                                                                           // движения
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				game.player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				game.player.direction = PlayerDirection::Down;
			}

			// Скорость игрока
			game.player.speed += ACCELERATION * deltaTime;                       // скорость игрока увеличивается на значения ACCELERATION * deltaTime. Через 1с скорость = 100+20
			if (game.player.speed > MAX_SPEED)
			{
				game.player.speed = MAX_SPEED;
			}

			// Движение игрока                                                        // Движение
			switch (game.player.direction)                                            // по
			{                                                                         // выбранному
			case PlayerDirection::Right:                                              // направлению
			{                                                                         // скорость
				game.player.position.x += game.player.speed * deltaTime;              // умножается
				break;                                                                // на
			}                                                                         // deltaTime
			case PlayerDirection::Up:                                                 // для  
			{                                                                         // независимости
				game.player.position.y -= game.player.speed * deltaTime;              // от
				break;                                                                // кадров
			}                                                                         // в
			case PlayerDirection::Left:                                               // секунду
			{
				game.player.position.x -= game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Down:
			{
				game.player.position.y += game.player.speed * deltaTime;
			}	break;
			}

			// Коллизии
			CollisionWithApple(game);
			CollisionWithObstacle(game);
			CollisionWithCigarette(game);

			// Проверка столкнулся ли игрок с краем экрана
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f || game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.position.y - PLAYER_SIZE / 2.f < 0.f || game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
			{
				if (!game.isGameOver)
				{
					game.audio.gameOverSound.play();
				}
				// Игра останавливается
				game.isGameOver = true;
				game.gameOverTime = 0.f;
			}
			// Проверка если набрано 100 очков
			if (game.numEatenApples >= 50)
			{
				game.isGameWin = true;
				game.text.GameWinLine1.setString("YOU WIN!!!");
				game.text.GameWinLine1.setOrigin(game.text.GameWinLine1.getLocalBounds().width / 2, game.text.GameWinLine1.getLocalBounds().height / 2);
				game.text.GameWinLine1.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 110);

				game.text.GameWinLine2.setString("Press R to restart");
				game.text.GameWinLine2.setOrigin(game.text.GameWinLine2.getLocalBounds().width / 2, game.text.GameWinLine2.getLocalBounds().height / 2);
				game.text.GameWinLine2.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 20);

				game.text.GameWinLine3.setString("Press Esc to exit");
				game.text.GameWinLine3.setOrigin(game.text.GameWinLine3.getLocalBounds().width / 2, game.text.GameWinLine3.getLocalBounds().height / 2);
				game.text.GameWinLine3.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 70);
			}
		}

		if (game.isGameOver)  // Считаем таймер
		{
			game.gameOverTime += deltaTime;

			float remaining = RESTART_DELAY - game.gameOverTime;
			if (remaining < 0)
			{
				remaining = 0;
			}
			int secondsLeft = static_cast<int>(std::ceil(remaining));
			game.text.restartGameText.setString("Restarting in: " + std::to_string(secondsLeft));
			game.text.restartGameText.setOrigin(game.text.restartGameText.getLocalBounds().width / 2, game.text.restartGameText.getLocalBounds().height / 4);


			if (game.gameOverTime >= RESTART_DELAY)  // Автоматический перезапуск
			{
				ResetGame(game);
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		// Отрисовка игрока
		DrawPlayer(game.player, window);
		// Отрисовка массива яблок
		DrawApple(game.apples, game.numApples, window);
		// Отрисовываем массив препятсивий
		DrawObstacles(game.obstacles, game.numObstacles, window);
        // Отрисовываем бонусные сигареты
		DrawCigarette(game.cigarettes, game.numCigarettes, window);
		// Отрисовываем текст
		DrawText(game.text, window, game);
	}

	void Deinitialization(Game& game)
	{
		delete[] game.apples;
		delete[] game.obstacles;
		delete[] game.cigarettes;
	}
}

