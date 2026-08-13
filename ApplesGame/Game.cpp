#include "Game.h"
#include "Apple.h"
#include "Cigarette.h"
#include "Obstacle.h"
#include <cassert>
#include <iostream>
#include <algorithm>

namespace ApplesGame
{
	void PushState(Game& game, GameState state)
	{
		game.stateStack.push_back(state);
	}

	void PopState(Game& game)
	{
		if (!game.stateStack.empty())
		{
			game.stateStack.pop_back();
		}
	}

	GameState GetCurrentState(const Game& game)
	{
		if (game.stateStack.empty())
		{
			return GameState::MainMenu;
		}
		return game.stateStack.back();
	}

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
		
		game.stateStack.clear();
		PushState(game, GameState::MainMenu);
		InitAudio(game.audio);
		ResetGame(game);
	}

	void UpdateMainMenu(Game& game)
	{
		// Движение по меню (стрелки вверх и вниз)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (!game.isUpPressed)
			{
				game.selectedMenuItem = (game.selectedMenuItem - 1 + MENU_ITEMS) % MENU_ITEMS;
				game.isUpPressed = true;
			}
		}
		else
		{
			game.isUpPressed = false;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!game.isDownPressed)
			{
				game.selectedMenuItem = (game.selectedMenuItem + 1 + MENU_ITEMS) % MENU_ITEMS;
				game.isDownPressed = true;
			}
		}
		else
		{
			game.isDownPressed = false;
		}
		

		// Выбор пункта меню
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!game.isEnterPressed)
			{
			switch (game.selectedMenuItem)
				{
				case 0:      // Start Game
					PushState(game, GameState::Gameplay);
					break;
				case 1:      // Leaderboard
					PushState(game, GameState::LeaderBoardState);
					break;
				case 2:      // Exit
					PushState(game, GameState::ConfirmExit);
					break;
				}
			game.isEnterPressed = true;
			}
		}
		else
		{
			game.isEnterPressed = false;
		}
	}

	void UpdatePauseMenu(Game& game)
	{
		// Движение по меню паузы (стрелки вверх и вниз)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (!game.isUpPressed)
			{
				game.selectedPauseMenuItem = (game.selectedPauseMenuItem - 1 + PAUSE_MENU_ITEMS) % PAUSE_MENU_ITEMS;
				game.isUpPressed = true;
			}
		}
		else
		{
			game.isUpPressed = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!game.isDownPressed)
			{
				game.selectedPauseMenuItem = (game.selectedPauseMenuItem + 1 + PAUSE_MENU_ITEMS) % PAUSE_MENU_ITEMS;
				game.isDownPressed = true;
			}
		}
		else
		{
			game.isDownPressed = false;
		}


		// Выбор пункта меню
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!game.isEnterPressed)
			{
				switch (game.selectedPauseMenuItem)
				{
				case 0 :             // Continue
					PopState(game);  // Возвращаемся в игру
					break;
				case 1:              // Exit to Menu
					PopState(game);  // Убираем PauseMenu
					PopState(game);  // Убираем Gameplay
					ResetGame(game); // Сбрасываем игру
					break;
				}
				game.isEnterPressed = true;
			}
		}
		else
		{
			game.isEnterPressed = false;
		}
	}
	
	void UpdateLeaderBoardState(Game& game)
	{
		// Возвращение в главное меню посредством нажатия backspace
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		{
				PopState(game); // Возвращаемся в Главное меню
		}
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
	}

	// Обновление таблицы лидеров
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
	


	// Обновление игрового процесса
	void UpdateGameplay(Game& game, float deltaTime)
	{
		// Обработка клавиши Esc (1 раз за нажатие)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!game.isEscPressed)
			{
			PushState(game, GameState::ConfirmExit);
			game.isEscPressed = true;
			}
		}
		else
		{
			game.isEscPressed = false;
		}

		// Обработка клавиши "P" (1 раз за нажатие)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (!game.isPausePressed)
			{
				PushState(game, GameState::PauseMenu);
				game.isPausePressed = true;
			}
		}
		else
		{
			game.isPausePressed = false;
		}
		
		// Управление
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
			// Переключаем на GameOver
			PopState(game);
			PushState(game, GameState::GameOver);
			return;
		}

		// Проверка победы
		bool isEnd = (game.modeFlags & MODE_END) != 0;
		bool isInfinity = (game.modeFlags & MODE_INFINITY) != 0;

		if (!isInfinity && !isEnd)
		{
			if (game.numEatenApples >= 50)
			{
				UpdateLeaderboard(game);
				game.isGameWin = true;
				PopState(game);
				PushState(game, GameState::WinScreen);

				game.text.GameWinLine1.setString("YOU WIN!!!");
				game.text.GameWinLine1.setOrigin(game.text.GameWinLine1.getLocalBounds().width / 2, game.text.GameWinLine1.getLocalBounds().height / 2);
				game.text.GameWinLine1.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 110);

				game.text.GameWinLine2.setString("Press R to restart");
				game.text.GameWinLine2.setOrigin(game.text.GameWinLine2.getLocalBounds().width / 2, game.text.GameWinLine2.getLocalBounds().height / 2);
				game.text.GameWinLine2.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 20);

				game.text.GameWinLine3.setString("Press Esc to exit");
				game.text.GameWinLine3.setOrigin(game.text.GameWinLine3.getLocalBounds().width / 2, game.text.GameWinLine3.getLocalBounds().height / 2);
				game.text.GameWinLine3.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 70);

				return;
			}
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
				PopState(game);
				PushState(game, GameState::WinScreen);

				game.text.GameWinLine1.setString("YOU WIN!!!");
				game.text.GameWinLine1.setOrigin(game.text.GameWinLine1.getLocalBounds().width / 2, game.text.GameWinLine1.getLocalBounds().height / 2);
				game.text.GameWinLine1.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 110);

				game.text.GameWinLine2.setString("Press R to restart");
				game.text.GameWinLine2.setOrigin(game.text.GameWinLine2.getLocalBounds().width / 2, game.text.GameWinLine2.getLocalBounds().height / 2);
				game.text.GameWinLine2.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 20);

				game.text.GameWinLine3.setString("Press Esc to exit");
				game.text.GameWinLine3.setOrigin(game.text.GameWinLine3.getLocalBounds().width / 2, game.text.GameWinLine3.getLocalBounds().height / 2);
				game.text.GameWinLine3.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 70);

				return;
			}
		}
	}

	// Обновление экрана GameOver
	void UpdateGameOver(Game& game, float deltaTime)
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

		if (game.gameOverTime >= RESTART_DELAY)
		{
			ResetGame(game);
			PopState(game);
			PushState(game, GameState::Gameplay);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			ResetGame(game);
			PopState(game);
			PushState(game, GameState::Gameplay);
		}
	}

	// Обновление экрана победы
	void UpdateWinScreen(Game& game, float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			ResetGame(game);
			PopState(game);
			PushState(game, GameState::Gameplay);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			PushState(game, GameState::ConfirmExit);
		}
	}

	// Обновление экрана подтверждения выхода
	void UpdateConfirmExit(Game& game)
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // Закрываем окно, используя Y  или Enter
		{
			if (!game.isEscPressed)
			{
			game.shouldExit = true;
			game.isEscPressed = true;
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // Отменяем закрытия окна, используя N  или Escape
		{
			if (!game.isEscPressed)
			{
			PopState(game);
			game.isEscPressed = true;
			}
		}

		else
		{
			game.isEscPressed = false;
		}
	}



	// Обновление состояния игры
	void UpdateGame(Game& game, float deltaTime)
	{
		GameState currentState = GetCurrentState(game);

		switch (currentState)
		{
		case GameState::MainMenu:
			UpdateMainMenu(game);
			break;

		case GameState::Gameplay:
			UpdateGameplay(game, deltaTime);
			break;

		case GameState::PauseMenu:
			UpdatePauseMenu(game);
			break;

		case GameState::GameOver:
			UpdateGameOver(game, deltaTime);
			break;

		case GameState::WinScreen:
			UpdateWinScreen(game, deltaTime);
			break;

		case GameState::ConfirmExit:
			UpdateConfirmExit(game);
			break;
			
		case GameState::LeaderBoardState:
			UpdateLeaderBoardState(game);
			break;
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