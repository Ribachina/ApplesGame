#include "Text.h"
#include "Game.h"

namespace ApplesGame
{
	void LeaderBoard(Text& text, sf::RenderWindow& window, Game& game)
	{
		if (game.isGameOver || game.isGameWin)
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
		text.RestartAndExit.setFillColor(sf::Color::White);
		text.RestartAndExit.setString("Press R to restart or Esc to exit");
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
	}
	void DrawText(Text& text, sf::RenderWindow& window, Game& game)
	{
		GameState currentState = GetCurrentState(game);

		switch (currentState)
		{
		case GameState::StartScreen:
			// Отрисовываем текст для начала игры
			window.draw(text.GameStart);
			break;

		case GameState::Gameplay:
			// Отрисовываем счётчик
			window.draw(text.Score);
			// Отрисовываем текст управления
			window.draw(text.Control);
			// Отрисовывем клавиши для перезапуска и закрытия игры
			window.draw(text.RestartAndExit);
			break;

		case GameState::GameOver:
			// Отрисовываем текст после проигрыша
			window.draw(text.gameOverText);
			window.draw(text.restartGameText);
			LeaderBoard(text, window, game);
			window.draw(text.Score);
			break;

		case GameState::WinScreen:
			// Отрисовываем текст после победы
			window.draw(text.GameWinLine1);
			window.draw(text.GameWinLine2);
			window.draw(text.GameWinLine3);
			LeaderBoard(text, window, game);
			window.draw(text.Score);
			break;

		case GameState::ConfirmExit:
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
	}
}