#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Text.h"
#include <SFML/Audio.hpp>
#include "Audio.h"
#include "Record.h"
#include <map>
#include <string>
#include "Apple.h"
#include "Cigarette.h"
#include "Obstacle.h"

namespace ApplesGame
{
	//struct Apple;
	//struct Cigarette;
	//struct Obstacle;
	
	struct Game
	{
		// Игровые объекты
		Player player;
		std::vector<Apple> apples;         // Vector на яблоки
		std::vector<Obstacle> obstacles;   // Vector на препятствия
		std::vector<Cigarette> cigarettes; // Vector на бонусы
		Text text;
		Audio audio;
		
		//Количество объектов
		int numApples = 20;    // Количество яблок по умолчанию
		int numObstacles = 5;  // Количество препятствий по умолчанию
		int numCigarettes = 2; // Количество бонусов по умолчанию
		
		// Состояние и режим игры
		int modeFlags = 0;
		int numEatenApples = 0;
		bool isGameOver = false;
		bool isGameWin = false;
		bool isGameStart = false;
		float gameOverTime = 0.f;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture obstacleTexture;
		sf::Texture cigaretteTexture;

		std::map<std::string, int> leaderboard;

	};

	void ResetGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);  // Обновление состояния игры
	void DrawGame(Game& game, sf::RenderWindow& window);
	void Deinitialization(Game& game);
	void CustomSettings(int& numApples, int& numObstacles, int& numCigarettes); // Функция пользовательских настроек
	void AcceptGameMode(Game& game, int modeFlags);
	void ReCreateGameObjects(Game& game);
	void UpdateLeaderboard(Game& game); // Функция таблицы лидеров. Вызываем при победе, столкновении с препятствием или стеной.
}
