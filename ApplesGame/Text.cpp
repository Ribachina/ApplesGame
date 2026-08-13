#include "Text.h"
#include "Game.h"

namespace ApplesGame
{
	void LeaderBoard(Text& text, sf::RenderWindow& window, Game& game)
	{
			std::vector<std::pair<std::string, int>>sortedEntries;     // Вектор, каждый элемент которого пара: строка и число
			for (const auto& [name, score] : game.leaderboard)         // Извлекаем строку в name, а число в score
			{
				sortedEntries.push_back({ name, score });              // Создаём пару имя и очки, и добавляем в конец вектора и создаём пару в std::pair { }
			}

			for (int i = 1; i < sortedEntries.size(); ++i)             // Сортируем по убыванию очков
			{
				auto key = sortedEntries[i];                           // key - текущий элемент, который хотим вставить в отсортированную часть
				int j = i - 1;                                         // индекс предыдущего элемента

				while (j >= 0 && sortedEntries[j].second < key.second) // Двигаем элементы вправо, пока не найдём место для key
				{
					sortedEntries[j + 1] = sortedEntries[j];           // сдвигаем элементы вправо на освободившееся место
					j--;
				}
				sortedEntries[j + 1] = key;                            // как нашли место вставляем key
			}

			if (sortedEntries.size() > 10)
			{
				sortedEntries.resize(10);                              // Оставляем только 10 элементов
			}

			std::string leaderboardStr = "===== LEADERBOARD =====\n";

			for (int i = 0; i < sortedEntries.size(); ++i)             // Перебираем все записи в векторе
			{
				const auto& [name, score] = sortedEntries[i];
				leaderboardStr += std::to_string(i + 1) + ". ";        // превращаем число в строку
				leaderboardStr += name;                                // добавляем ник Player

				int dotsCount = 20 - name.length();                    // Добавим точки (20макс), чтобы красиво расположить ники в таблице лидеров
				for (int j = 0; j < dotsCount; ++j)                    // Добавляем точки
				{
					leaderboardStr += ".";
				}
				leaderboardStr += " " + std::to_string(score) + "\n";
			}
			leaderboardStr += "=======================";

			text.LeaderBoard.setString(leaderboardStr);
			window.draw(text.LeaderBoard);
	}

	void DrawMainMenu(Text& text, sf::RenderWindow& window, Game& game)
	{
		window.draw(text.menuTitle); // Заголовок

		for (int i = 0; i < 3; ++i)
		{
			if (i == game.selectedMenuItem)
			{
				text.menuItems[i].setFillColor(sf::Color::Yellow); // Красим выбранный пункт
			}
			else
			{
				text.menuItems[i].setFillColor(sf::Color::White); // Не выбранный пункт остаётся белым
			}
			window.draw(text.menuItems[i]);
		}

		window.draw(text.menuHint); // Подсказка
	}

	void DrawPauseMenu(Text& text, sf::RenderWindow& window, Game& game)
	{
		// Затемняем экран
		sf::RectangleShape overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);
		// Отрисовываем заголовок PAUSE
		window.draw(text.pauseTitle);
		// Подсвечиваем выбранный пункт в меню паузы
		for (int i = 0; i < 2; ++i)
		{
			if (i == game.selectedPauseMenuItem)
			{
				text.pauseItems[i].setFillColor(sf::Color::Yellow);
			}
			else
			{
				text.pauseItems[i].setFillColor(sf::Color::White);
			}
			window.draw(text.pauseItems[i]);
		}
		window.draw(text.pauseHint);
	}

	

	void InitText(Text& text)
	{
		// Загружаем шрифт
		text.font.loadFromFile("Resources/Tokushupikuseru-Regular.otf");

		// Инициализация текста очков
		text.Score.setFont(text.font);                                     // Задаём переменной Score шрифт
		text.Score.setCharacterSize(40);                                   // Задаём переменной Score размер шрифта
		text.Score.setFillColor(sf::Color::White);                         // Цвет текста
		text.Score.setPosition(5.f, -20.f);                                // Выводим в левом верхнем углу
		text.Score.setString("Score: 0");                                  // Выводим пременную Score с текстом Score

		// Инициализация текста Game Over
		text.gameOverText.setFont(text.font);
		text.gameOverText.setCharacterSize(100);
		text.gameOverText.setFillColor(sf::Color::Red);
		text.gameOverText.setString("GAME OVER!");
		text.gameOverText.setOrigin(text.gameOverText.getLocalBounds().width / 2, text.gameOverText.getLocalBounds().height / 2);
		text.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 40);

		// Инициализация текста Restart game in:
		text.restartGameText.setFont(text.font);
		text.restartGameText.setCharacterSize(60);
		text.restartGameText.setFillColor(sf::Color::White);
		text.restartGameText.setString("Restart game in: 2");
		text.restartGameText.setOrigin(text.restartGameText.getLocalBounds().width / 2, text.restartGameText.getLocalBounds().height / 2);
		text.restartGameText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.5);
		
		// Инициализация текста управления
		text.Control.setFont(text.font);
		text.Control.setCharacterSize(50);                                   
		text.Control.setFillColor(sf::Color::Yellow);
		text.Control.setString("Use arrows or WASD to move");
		text.Control.setOrigin(text.Control.getLocalBounds().width / 2, text.Control.getLocalBounds().height / 2);
		text.Control.setPosition(SCREEN_WIDTH / 2.f, -10.f);

		// Инициализация текста перезапуска и выхода
		text.RestartAndExit.setFont(text.font);
		text.RestartAndExit.setCharacterSize(40);
		text.RestartAndExit.setFillColor(sf::Color(150, 150, 150));
		text.RestartAndExit.setString("Press R to restart or Esc to exit or P for pause");
		float textWidth = text.RestartAndExit.getLocalBounds().width;
		text.RestartAndExit.setOrigin(0.f, 0.f);
		float rightIndent = 10.f; // Небольшой отступ от края
		text.RestartAndExit.setPosition(SCREEN_WIDTH - textWidth - rightIndent, -20.f);

		// Инициализация текста победы (You win!!!)
		text.GameWinLine1.setFont(text.font);
		text.GameWinLine1.setCharacterSize(100);
		text.GameWinLine1.setFillColor(sf::Color::Yellow);
		text.GameWinLine1.setString("YOU WIN!!!");
		text.GameWinLine1.setOrigin(text.GameWinLine1.getLocalBounds().width / 2, text.GameWinLine1.getLocalBounds().height / 2);
		text.GameWinLine1.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 35);

		// Press R to restart
		text.GameWinLine2.setFont(text.font);
		text.GameWinLine2.setCharacterSize(70);
		text.GameWinLine2.setFillColor(sf::Color::Yellow);
		text.GameWinLine2.setString("Press R to restart");
		text.GameWinLine2.setOrigin(text.GameWinLine2.getLocalBounds().width / 2, text.GameWinLine2.getLocalBounds().height / 2);
		text.GameWinLine2.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 20);

		// Press Esc to exit
		text.GameWinLine3.setFont(text.font);
		text.GameWinLine3.setCharacterSize(70);
		text.GameWinLine3.setFillColor(sf::Color::Yellow);
		text.GameWinLine3.setString("Press Esc to exit");
		text.GameWinLine3.setOrigin(text.GameWinLine3.getLocalBounds().width / 2, text.GameWinLine3.getLocalBounds().height / 2);
		text.GameWinLine3.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 50);
		
		// Инициализация текста начала игры
		text.GameStart.setFont(text.font);
		text.GameStart.setCharacterSize(100);
		text.GameStart.setFillColor(sf::Color::White);
		text.GameStart.setString("Press Enter to start");
		text.GameStart.setOrigin(text.GameStart.getLocalBounds().width / 2, text.GameStart.getLocalBounds().height / 2);
		text.GameStart.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

		// Инициализация таблицы лидеров
		text.LeaderBoard.setFont(text.font);
		text.LeaderBoard.setCharacterSize(40);
		text.LeaderBoard.setFillColor(sf::Color::White);
		text.LeaderBoard.setPosition(10.f, 80.f);
		text.LeaderBoard.setString("");

		// Инициализация текста "Want to exit?"
		text.confirmExitText.setFont(text.font);
		text.confirmExitText.setCharacterSize(60);
		text.confirmExitText.setFillColor(sf::Color::White);
		text.confirmExitText.setString("Want to exit?");
		text.confirmExitText.setOrigin(text.confirmExitText.getLocalBounds().width / 2, text.confirmExitText.getLocalBounds().height / 2);
		text.confirmExitText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

		// Инициализация текста "Yes"
		text.confirmExitYes.setFont(text.font);
		text.confirmExitYes.setCharacterSize(40);
		text.confirmExitYes.setFillColor(sf::Color::Green);
		text.confirmExitYes.setString("Yes");
		text.confirmExitYes.setOrigin(text.confirmExitYes.getLocalBounds().width / 2, text.confirmExitYes.getLocalBounds().height / 2);
		text.confirmExitYes.setPosition(SCREEN_WIDTH / 2.f - 100, SCREEN_HEIGHT / 2.f + 40);

		// Инициализация текста "No"
		text.confirmExitNo.setFont(text.font);
		text.confirmExitNo.setCharacterSize(40);
		text.confirmExitNo.setFillColor(sf::Color::Red);
		text.confirmExitNo.setString("No");
		text.confirmExitNo.setOrigin(text.confirmExitNo.getLocalBounds().width / 2, text.confirmExitNo.getLocalBounds().height / 2);
		text.confirmExitNo.setPosition(SCREEN_WIDTH / 2.f + 100, SCREEN_HEIGHT / 2.f + 40);

		// Инициализация текста заголовка игры
		text.menuTitle.setFont(text.font);
		text.menuTitle.setCharacterSize(80);
		text.menuTitle.setFillColor(sf::Color::Yellow);
		text.menuTitle.setString("APPLES GAME");
		text.menuTitle.setOrigin(text.menuTitle.getLocalBounds().width / 2, text.menuTitle.getLocalBounds().height / 2);
		text.menuTitle.setPosition(SCREEN_WIDTH / 2.f, 150.f);

		// Инициализация пунктов меню
		std::vector<std::string>menuItemsStrings =
		{
			"Start Game",
			"Leaderboard",
			"Exit game"
		};
		for (int i = 0; i < 3; ++i)
		{
			text.menuItems[i].setFont(text.font);
			text.menuItems[i].setCharacterSize(50);
			text.menuItems[i].setString(menuItemsStrings[i]);
			text.menuItems[i].setOrigin(text.menuItems[i].getLocalBounds().width / 2, text.menuItems[i].getLocalBounds().height / 2);
			text.menuItems[i].setPosition(SCREEN_WIDTH / 2.f, 300.f + i * 70.f);
		}

		// Инициализация подсказок в меню
		text.menuHint.setFont(text.font);
		text.menuHint.setCharacterSize(50);
		text.menuHint.setFillColor(sf::Color(150, 150,150));
		text.menuHint.setString("Use Up/Down arrows to move. Enter to select");
		text.menuHint.setOrigin(text.menuHint.getLocalBounds().width / 2, text.menuHint.getLocalBounds().height / 2);
		text.menuHint.setPosition(SCREEN_WIDTH / 2.f, 600.f);

		// Инициализация заголовка "Таблица лидеров"
		text.leaderboardTitle.setFont(text.font);
		text.leaderboardTitle.setCharacterSize(60);
		text.leaderboardTitle.setFillColor(sf::Color::Yellow);
		text.leaderboardTitle.setString("Leaderboard");
		text.leaderboardTitle.setOrigin(text.leaderboardTitle.getLocalBounds().width / 2, text.leaderboardTitle.getLocalBounds().height / 2);
		text.leaderboardTitle.setPosition(SCREEN_WIDTH / 2.f, 80.f);

		// Инициализация подсказок для Таблицы лидеров
		text.leaderboardHint.setFont(text.font);
		text.leaderboardHint.setCharacterSize(30);
		text.leaderboardHint.setFillColor(sf::Color(150, 150, 150));
		text.leaderboardHint.setString("Press Backspace to back");
		text.leaderboardHint.setOrigin(text.leaderboardHint.getLocalBounds().width / 2, text.leaderboardHint.getLocalBounds().height / 2);
		text.leaderboardHint.setPosition(SCREEN_WIDTH / 2.f, 680.f);

		// Инициализация текста меню паузы
		text.pauseTitle.setFont(text.font);
		text.pauseTitle.setCharacterSize(80);
		text.pauseTitle.setFillColor(sf::Color::Yellow);
		text.pauseTitle.setString("APPLES GAME");
		text.pauseTitle.setOrigin(text.pauseTitle.getLocalBounds().width / 2, text.pauseTitle.getLocalBounds().height / 2);
		text.pauseTitle.setPosition(SCREEN_WIDTH / 2.f, 150.f);

		// Инициализация пунктов меню паузы
		std::vector<std::string> pauseItemStrings =
		{
			"Continue",
			"Exit to menu"
		};
		for (int i = 0; i < 2; ++i)
		{
			text.pauseItems[i].setFont(text.font);
			text.pauseItems[i].setCharacterSize(50);
			text.pauseItems[i].setString(pauseItemStrings[i]);
			text.pauseItems[i].setOrigin(text.pauseItems[i].getLocalBounds().width / 2, text.pauseItems[i].getLocalBounds().height / 2);
			text.pauseItems[i].setPosition(SCREEN_WIDTH / 2.f, 300.f + i * 70.f);
		}

		// Инициализация подсказок в меню паузы
		text.pauseHint.setFont(text.font);
		text.pauseHint.setCharacterSize(50);
		text.pauseHint.setFillColor(sf::Color(150, 150, 150));
		text.pauseHint.setString("Use Up/Down arrows to move. Enter to select");
		text.pauseHint.setOrigin(text.pauseHint.getLocalBounds().width / 2, text.pauseHint.getLocalBounds().height / 2);
		text.pauseHint.setPosition(SCREEN_WIDTH / 2.f, 600.f);

	}

	void DrawLeaderBoardScreen(Text& text, sf::RenderWindow& window, Game& game)
	{
		// Затемняем экран
		sf::RectangleShape overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);

		// Отрисовываем заголовок таблицы лидеров
		window.draw(text.leaderboardTitle);

		// Отрисовываем таблицу лидеров
		LeaderBoard(text, window, game);

		// Отрисовывем подсказку
		window.draw(text.leaderboardHint);
	}

	void DrawText(Text& text, sf::RenderWindow& window, Game& game)
	{
		GameState currentState = GetCurrentState(game);

		switch (currentState)
		{
		case GameState::MainMenu:
			// Отрисовываем текст для начала игры
			DrawMainMenu(text, window, game);
			break;

		case GameState::Gameplay:
			// Отрисовываем счётчик
			window.draw(text.Score);
			// Отрисовываем текст управления
			window.draw(text.Control);
			// Отрисовывем клавиши для перезапуска и закрытия игры
			window.draw(text.RestartAndExit);
			break;

		case GameState::PauseMenu:
			DrawPauseMenu(text, window, game);
			break;

		case GameState::GameOver:
			// Отрисовываем текст после проигрыша
			window.draw(text.gameOverText);
			window.draw(text.restartGameText);
			if (game.isGameOver)
			{
			LeaderBoard(text, window, game);
			}
			window.draw(text.Score);
			break;

		case GameState::WinScreen:
			// Отрисовываем текст после победы
			window.draw(text.GameWinLine1);
			window.draw(text.GameWinLine2);
			window.draw(text.GameWinLine3);
			if (game.isGameWin)
			{
			LeaderBoard(text, window, game);
			}
			window.draw(text.Score);
			break;

		case GameState::ConfirmExit:
		{
			//Затемним фон игры
			sf::RectangleShape overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
			overlay.setFillColor(sf::Color(0, 0, 0, 150));
			window.draw(overlay);

			// Отрисовка текста подтверждения выхода
			window.draw(text.confirmExitText);
			window.draw(text.confirmExitYes);
			window.draw(text.confirmExitNo);
			break;
		}

		case GameState::LeaderBoardState:
			DrawLeaderBoardScreen(text, window, game);
			break;
		}
	}
}