#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Text.h"
#include <SFML/Audio.hpp>
#include "Audio.h"

namespace ApplesGame
{
	struct Apple;
	struct Cigarette;
	struct Obstacle;
	
	struct Game
	{
		// Игровые объекты
		Player player;
		Apple* apples = nullptr;         // Указатель на массив яблок
		Obstacle* obstacles = nullptr;   // Указатель на массив препятствий
		Text text;
		Audio audio;
		Cigarette* cigarettes = nullptr; // Указатель на массив бонусов

		// Режим игры
		int modeFlags = 0;
		
		// Количество объектов
		int numApples = DEFAULT_NUM_APPLES; // Количество яблок по умолчанию
		int numObstacles = DEFAULT_NUM_OBSTACLES; // Количество препятствий по умолчанию
		int numCigarettes = DEFAULT_NUM_CIGARETTES; // Количество бонусов по умолчанию
		
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
	void CustomSettings(int& numApples, int& numObstacles, int& numCigarettes); // Функция пользовательских настроек
	void AcceptGameMode(Game& game, int modeFlags);
	void ReCreateGameObjects(Game& game);
}
