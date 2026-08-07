#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include "Constants.h"
#include "Game.h"

int SelectGameMode()
{
	using namespace ApplesGame;

	std::cout << "=====SELECT GAME MODE=====\n";
	std::cout << "1. Classic (20 apples, 5 obstacles, 2 bonuses, speed grow)\n";
	std::cout << "2. Easy (20 apples, 5 obstacles, 2 bonuses, speed FIX)\n";
	std::cout << "3. Hard (50 apples, 10 obstacles, 5 bonuses, speed grow)\n";
	std::cout << "4. Custom (20 apples, 5 obstacles, 2 bonuses, speed grow)\n";
	std::cout << "5. End (50 apples NO RESPAWN, 5 obstacles, 2 bonuses, speed grow)\n";
	std::cout << "6. Speed (20 apples, 5 obstacles, 2 bonuses, speed grow after eat)\n";
	std::cout << "7. Infinity (20 apples, 5 obstacles, 0 bonuses, infinity spawn apples)\n";
	std::cout << "Your choise (1-7): ";

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1: return 0;             // Classic - нет битов 
	case 2: return MODE_EASY;     // Easy - бит 0010
	case 3: return MODE_HARD;     // Hard - бит 0001
	case 4: return MODE_CUSTOM;   // Custom - бит 0100
	case 5: return MODE_END;      // End - бит 1000
	case 6: return MODE_SPEED;    // Speed - бит 0001 0000
	case 7: return MODE_INFINITY; // Infinity - бит 0010 0000
	default: std::cout << "Error!!! Using 1,2,3,4,5,6 or 7. Using Classic mode now";
		return 0;
	}
}


int main()
{
	using namespace ApplesGame;

	int modeFlags = SelectGameMode();

	bool isCustom = (modeFlags & MODE_CUSTOM) != 0;

	int numApples = DEFAULT_NUM_APPLES;
	int numObstacles = DEFAULT_NUM_OBSTACLES;
	int numCigarettes = DEFAULT_NUM_CIGARETTES;

	if (isCustom)
	{
		CustomSettings(numApples, numObstacles, numCigarettes);
	}
	
	// Инициализация генератора случайных чисел
	srand(static_cast<unsigned int>(time(nullptr)));

	// Инициализация окна
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!"); // создаёт окно 800 на 600 с заголовком "Apple game!"

	// Инициализация игры
	Game game;
	game.numApples = numApples; // Передаём количество яблок
	game.numObstacles = numObstacles; // Передаём количество препятствий
	game.numCigarettes = numCigarettes; // Передаём количество бонусов
	
	AcceptGameMode(game, modeFlags);
	InitGame(game);
	
	// Инициализация игровых часов
	sf::Clock gameClock;                                            // часы начинают работать с момента создания
	float lastTime = gameClock.getElapsedTime().asSeconds();        // lastTime - время в прошлом кадре    getElapsedTime() - возвращает время с момента запуска игры.в секундах ()

	// Основной цикл игры
	while (window.isOpen())
	{
		sf::sleep(sf::milliseconds(16));
		
		// Считаем дельту времени
		float currentTime = gameClock.getElapsedTime().asSeconds(); // currentTime - текущее время
		float deltaTime = currentTime - lastTime;                   // deltaTime - разница между кадрами
		lastTime = currentTime;                                     // обновляем для следующего кадра

		// События
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)                    // проверяем есть ли событие "Закрытие окна"
			{
				window.close();                                     // Если есть, закрываем окно
				break;
			}
			// Выход через Esc
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
			// Перезапуск на R
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				ResetGame(game);
			}
		}

		UpdateGame(game, deltaTime);
		
		window.clear();                                              // Очищаем экран
		DrawGame(game, window);
        window.display();                                            // Отрисовка игры
	}
	
	Deinitialization(game);
	return 0;
}
