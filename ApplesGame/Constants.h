#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 1280;      // Ширина окна
	const int SCREEN_HEIGHT = 720;     // Высота окна
	const float INITIAL_SPEED = 100.f; // Пиксели в секунду
	const float PLAYER_SIZE = 40.f;    // Размер инрока
	const float ACCELERATION = 20.f;   // Ускорение в секунду каждую секунду
	const float MAX_SPEED = 400.f;     // Максимальная скорость
	const int DEFAULT_NUM_APPLES = 20; // Количество яблок на экране по умолчанию
	const float APPLE_SIZE = 30.f;     // Размер яблока
	const int DEFAULT_NUM_OBSTACLES = 5;// Количество препятствий по умолчанию
	const float OBSTACLE_SIZE = 30.f;  // Размер препятствий
	const float RESTART_DELAY = 2.f;   // Время до рестарта игры

	const float CIGARETTE_SIZE = 20.f;  // Размер бонуса
	const int DEFAULT_NUM_CIGARETTES = 2; // Количество бонусов по умолчанию
}


