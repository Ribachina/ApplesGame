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
		// Игровые объекты
		Player player;
		Apple* apples; // Указатель на массив яблок
		Obstacle* obstacles; // Указатель на массив препядствий
		Text text;
		Audio audio;
		Cigarette* cigarettes; // Указатель на массив бонусов

		// Состояние игры
		int numApples = DEFAULT_NUM_APPLES; // Количество яблок по умолчанию
		int numObstacles = DEFAULT_NUM_OBSTACLES; // Количество препядствий по умолчанию
		int numCigarettes = DEFAULT_NUM_CIGARETTES; // Количество бонусов по умолчанию
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
