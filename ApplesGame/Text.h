#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"


namespace ApplesGame
{
	struct Game;
	struct Text
	{
		// Инициализируем шрифт и текст
		sf::Font font;
		sf::Text Score;                                                    // Текст Apples: 0
		sf::Text gameOverText;                                             // Текст GAME OVER!
		sf::Text restartGameText;                                          // Текст Restart game in: 2
		sf::Text Control;                                                  // Текст Use arrows for move
		sf::Text RestartAndExit;                                           // Текст Press R for restart or Esc for exit
		sf::Text GameWinLine1;
		sf::Text GameWinLine2;
		sf::Text GameWinLine3;
		sf::Text GameStart;
		sf::Text LeaderBoard;                                              // Таблица лидеров
		sf::Text confirmExitText;                                          // Want to exit?
		sf::Text confirmExitYes;                                           // Yes
		sf::Text confirmExitNo;                                            // No
	};
	
	void InitText(Text& text);
	void DrawText(Text& text, sf::RenderWindow& window, Game& game);
}