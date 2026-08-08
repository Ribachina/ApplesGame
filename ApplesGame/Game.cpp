#include "Game.h"
#include "Apple.h"
#include "Cigarette.h"
#include "Obstacle.h"
#include <cassert>
#include <iostream>
#include <algorithm>

namespace ApplesGame
{
	void CustomSettings(int& numApples, int& numObstacles, int& numCigarettes) // Функция пользовательских настроек
	{
		std::cout << "=====Custom settings=====\n";
		std::cout << "Enter num of apples: ";
		std::cin >> numApples;
		if (numApples <= 0)
		{
			numApples = 20;
		}
		std::cout << "Enter num of obstacles: ";
		std::cin >> numObstacles;
		if (numObstacles <= 0)
		{
			numObstacles = 5;
		}
		std::cout << "Enter num of bonuses: ";
		std::cin >> numCigarettes;
		if (numCigarettes <= 0)
		{
			numCigarettes = 2;
		}
	}
	
	void ReCreateGameObjects(Game& game)
	{
		/*delete[] game.apples;
		delete[] game.obstacles;
		delete[] game.cigarettes;

		game.apples = nullptr;
		game.obstacles = nullptr;
		game.cigarettes = nullptr;*/

		game.apples.resize(game.numApples);
		game.obstacles.resize(game.numObstacles);
		game.cigarettes.resize(game.numCigarettes);

		for (auto& apple : game.apples)
		{
			InitApples(apple, game.appleTexture);
		}
		for (auto& obstacle : game.obstacles)
		{
			InitObstacles(obstacle, game.obstacleTexture);
		}
		for (auto& cigarette : game.cigarettes)
		{
			InitCigarette(cigarette, game.cigaretteTexture);
		}

		std::cout << "Recreated: " << game.apples.size() << " apples, " << game.obstacles.size() << " obstacles, " << game.cigarettes.size() << " bonuses\n";
	}
	
	void ResetGame(Game& game)
	{

			InitPlayer(game.player, game);

			ReCreateGameObjects(game);

			InitText(game.text);

			game.numEatenApples = 0;
			game.isGameOver = false;
			game.gameOverTime = 0.f;
			game.isGameWin = false;
			game.isGameStart = false;
			game.text.Score.setString("Score: 0");

			UpdateLeaderboard(game);
	}

	
	void InitGame(Game& game)
	{
		game.playerTexture.loadFromFile(RESOURCES_PATH + "Dima.png");
		game.appleTexture.loadFromFile(RESOURCES_PATH + "Coffe.png");
		game.obstacleTexture.loadFromFile(RESOURCES_PATH + "Maks.png");
		game.cigaretteTexture.loadFromFile(RESOURCES_PATH + "Cigarette.png");

		game.leaderboard["Alex"] = 45;
		game.leaderboard["Sasha"] = 40;
		game.leaderboard["Shurik"] = 35;
		game.leaderboard["Anchoys"] = 30;
		game.leaderboard["Shnurok"] = 25;
		
		//ReCreateGameObjects(game);
		
		InitAudio(game.audio);

		ResetGame(game);
	}

	void AcceptGameMode(Game& game, int modeFlags) // Функция применения режима игры
	{
		game.modeFlags = modeFlags;

		bool isHard = (modeFlags & MODE_HARD) != 0;
		bool isEasy = (modeFlags & MODE_EASY) != 0;
		bool isCustom = (modeFlags & MODE_CUSTOM) != 0;
		bool isEnd = (modeFlags & MODE_END) != 0;
		bool isSpeed = (modeFlags & MODE_SPEED) != 0;
		bool isInfinity = (modeFlags & MODE_INFINITY) != 0;

		if (isCustom)
		{
			// Пользовательский режим указан в GameMain 51 строка 
		}
		else if (isHard)
		{
			game.numApples = 50;
			game.numObstacles = 10;
			game.numCigarettes = 5;
		}
		else if (isEnd)
		{
			game.numApples = 50;
			game.numObstacles = 5;
			game.numCigarettes = 2;
		}
		else if (isInfinity)
		{
			game.numApples = 20;
			game.numObstacles = 5;
			game.numCigarettes = 0;
		}
		else // Classic Easy Speed
		{
			game.numApples = 20;
			game.numObstacles = 5;
			game.numCigarettes = 2;
		}

		//ReCreateGameObjects(game);
	}

	void UpdateLeaderboard(Game& game)
	{
		auto it = game.leaderboard.find("Player");
		if (it != game.leaderboard.end())
		{
			game.leaderboard.erase(it);  // Удаляем Player через итератор it
		}
		
		if (game.numEatenApples > 0) // Добавляем ник, только если кол-во очков больше 0
		{
			game.leaderboard["Player"] = game.numEatenApples; // Создаём ник Player и обновляем значение из съеденных яблок
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
			bool isEasy = (game.modeFlags & MODE_EASY) != 0;
			bool isSpeed = (game.modeFlags & MODE_SPEED) != 0;

			if (isEasy)
			{
				game.player.speed = INITIAL_SPEED;
			}
			else if (!isSpeed) // Режим Speed находится в функции Collision with apple
			{
				game.player.speed += ACCELERATION * deltaTime;
				if (game.player.speed > MAX_SPEED)
				{
					game.player.speed = MAX_SPEED;
				}
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
					UpdateLeaderboard(game);
				}
				// Игра останавливается
				game.isGameOver = true;
				game.gameOverTime = 0.f;
			}
			
			bool isEnd = (game.modeFlags & MODE_END) != 0;
			bool isInfinity = (game.modeFlags & MODE_INFINITY) != 0;

			if (isInfinity)
			{

			}
			else if (isEnd)
			{
				// Проверяем все ли яблоки съели для режима End
				bool allEaten = true;
				for (const auto& apple : game.apples)
				{
					if (!apple.isEaten)
					{
						allEaten = false;
						break;
					}
				}

				if (allEaten)
				{
					UpdateLeaderboard(game);

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
			
			// Проверка если набрано 50 очков
			else if (game.numEatenApples >= 50)
			{
				UpdateLeaderboard(game);
				
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
		DrawApple(game.apples, window);
		// Отрисовываем массив препятсивий
		DrawObstacles(game.obstacles, window);
        // Отрисовываем бонусные сигареты
		DrawCigarette(game.cigarettes, window);
		// Отрисовываем текст
		DrawText(game.text, window, game);
	}

	void Deinitialization(Game& game)
	{
		game.apples.clear();
		game.obstacles.clear();
		game.cigarettes.clear();
	}
}