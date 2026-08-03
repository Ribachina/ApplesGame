#include "Text.h"
#include "Game.h"

namespace ApplesGame
{
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
	}
	void DrawText(Text& text, sf::RenderWindow& window, Game& game)
	{
		// Отрисовываем счётчик
		window.draw(text.Score);

		// Отрисовываем текст управления
		window.draw(text.Control);

		// Отрисовывем клавиши для перезапуска и закрытия игры
		window.draw(text.RestartAndExit);

		// Отрисовываем текст для начала игры
		if (!game.isGameStart)
		{
			window.draw(text.GameStart);
		}
		
		// Не важно GameOver или GameWin отрисовываем таблицу
		if (game.isGameOver || game.isGameWin)
		{
			std::string leaderboardStr = "===== LEADERBOARD =====\n";
			for (int i = 0; i < game.leaderboard.size(); ++i)
			{
				const Record& record = game.leaderboard[i];
				leaderboardStr += std::to_string(i + 1) + ". "; // Номер места
				leaderboardStr += record.name;                  // Имя игрока

				int dotsCount = 20 - record.name.length();
				for (int j = 0; j < dotsCount; ++j)
				{
					leaderboardStr += ".";
				}
				leaderboardStr += " " + std::to_string(record.score) + "\n";
			}
			
			leaderboardStr += "=======================";

			text.LeaderBoard.setString(leaderboardStr);
			window.draw(text.LeaderBoard);
		}
		
		// Отрисовываем текст после проигрыша
		if (game.isGameOver)
		{
			window.draw(text.gameOverText);
			window.draw(text.restartGameText);
		}

		// Отрисовываем текст после победы
		if (game.isGameWin)
		{
			window.draw(text.GameWinLine1);
			window.draw(text.GameWinLine2);
			window.draw(text.GameWinLine3);
		}
		
	}
}