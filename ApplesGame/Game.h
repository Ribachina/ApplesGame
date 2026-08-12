#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Text.h"
#include <SFML/Audio.hpp>
#include "Audio.h"
#include "Record.h"
#include <map>
#include <string>
#include <vector>
#include "Apple.h"
#include "Cigarette.h"
#include "Obstacle.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class GameState
	{
		MainMenu,        // Главное меню
		Gameplay,        // Игровой процесс
		GameOver,        // Экран "Game Over"
		WinScreen,       // Экран "You Win!!!"
		ConfirmExit,     // Экран "Want to exit?"
		LeaderBoardState // Таблица рекордов в меню
	};
	
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
		bool shouldExit = false;               // Переменная подтверждения выхода из игры, чтобы закрыть окно
		float gameOverTime = 0.f;
		bool isEscPressed = false;             // Переменная для замедления обновления нажатия клавиши Esc во время игры
		bool isUpPressed = false;              // Переменная для замедления обновления нажатия стрелки вверх в главном меню
		bool isDownPressed = false;            // Переменная для замедления обновления нажатия стрелки вниз в главном меню
		bool isEnterPressed = false;           // Переменная для замедления обновления нажатия Enter в главном меню

		int selectedMenuItem = 0;              // Чтобы подсвечивать выбранный пункт в меню

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture obstacleTexture;
		sf::Texture cigaretteTexture;

		std::map<std::string, int> leaderboard; // Создаём map таблицу лидеров имя-число
		std::vector<GameState> stateStack;      // Создаём стэк состояний игры

	};

	void ResetGame(Game& game);                                                 // Функция сброса игры
	void InitGame(Game& game);                                                  // Функция инициализации игры
	void UpdateGame(Game& game, float deltaTime);                               // Обновление состояния игры
	void DrawGame(Game& game, sf::RenderWindow& window);                        // Функция отрисовки
	void UpdateGameplay(Game& game, float deltaTime);                           // Обновление игрового процесса
	void Deinitialization(Game& game);                                          // Функция деинициализации яблок, препятствий и бонусов
	void CustomSettings(int& numApples, int& numObstacles, int& numCigarettes); // Функция пользовательских настроек
	void AcceptGameMode(Game& game, int modeFlags);                             // Функция применения режима игры
	void ReCreateGameObjects(Game& game);                                       // Функция пересозданяи объектов игры
	void UpdateLeaderboard(Game& game);                                         // Функция таблицы лидеров. Вызываем при победе, столкновении с препятствием или стеной.
	void UpdateGameOver(Game& game, float deltaTime);                           // Обновление экрана GameOver
	void UpdateWinScreen(Game& game, float deltaTime);                          // Обновление экрана победы
	void UpdateConfirmExit(Game& game);                                         // Обновление экрана подтверждения выхода
	void UpdateMainMenu(Game& game);                                            // Функция передвижения по главному меню
	void UpdateLeaderBoardState(Game& game);                                    // Функция позволяющая вернуться в главное меню из таблицы лидеров
	
	// Стек состояний игры
	void PushState(Game& game, GameState state);
	void PopState(Game& game);
	GameState GetCurrentState(const Game& game);
}
