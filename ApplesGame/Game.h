#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Obstacle.h"
#include "Text.h"
#include <SFML/Audio.hpp>
#include "Audio.h"
#include "Cigarette.h"

namespace ApplesGame
{
	struct Game
	{
		// ИГровые объекты
		Player player;
		Apple apple[NUM_APPLES];
		Obstacle obstacle[NUM_OBSTACLE];
		Text text;
		Audio audio;
		Cigarette cigarette[NUM_CIGARETTES];

		// Состояние игры
		int numEatenApples = 0;
		bool isGameOver = false;
		bool isGameWin = false;
		bool isGameStart = false;
		float gameOverTime = 0.f;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture obstacleTexture;
		sf::Texture cigaretteTexture;

	};

	void ResetGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);  // Обновление состояния игры
	void DrawGame(Game& game, sf::RenderWindow& window);
	void Deinitialization(Game& game);
}
