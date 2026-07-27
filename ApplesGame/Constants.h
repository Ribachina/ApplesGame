#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 1280;     // Ширина окна
	const int SCREEN_HEIGHT = 720;     // Высота окна
	const float INITIAL_SPEED = 100.f; // Пиксели в секунду
	const float PLAYER_SIZE = 40.f;    // Размер инрока
	const float ACCELERATION = 20.f;   // Ускорение в секунду каждую секунду
	const float MAX_SPEED = 700.f;     // Максимальная скорость
	const float APPLE_SIZE = 30.f;     // Размер яблока
	const float OBSTACLE_SIZE = 30.f;  // Размер препятствий
	const float RESTART_DELAY = 2.f;   // Время до рестарта игры
	const float CIGARETTE_SIZE = 20.f; // Размер бонуса
	const float SPEED_PLUS = 30.f;     // Ускорение после поедания яблока
	

	// Константы для режимов игры
	const int DEFAULT_NUM_APPLES = 20;    // Количество яблок на экране по умолчанию
	const int DEFAULT_NUM_OBSTACLES = 5;  // Количество препятствий по умолчанию
	const int DEFAULT_NUM_CIGARETTES = 2; // Количество бонусов по умолчанию

	// Режимы игры
	
	const int MODE_HARD = 1 << 0;     // 1. 50 яблок, 10 препятствий, 5 бонусов, скорость растёт
	const int MODE_EASY = 1 << 1;     // 2. 20 яблок, 5 препятствий, 2 бонуса, скорость не растёт
	const int MODE_CUSTOM = 1 << 2;   // 4. Настройки пользователя скорость растёт
	const int MODE_END = 1 << 3;      // 8. Конечное число яблок (без респавна)
	const int MODE_SPEED = 1 << 4;    // 16. Ускорение после поедания яблок
	const int MODE_INFINITY = 1 << 5; // 32. Бесконечный режим

}