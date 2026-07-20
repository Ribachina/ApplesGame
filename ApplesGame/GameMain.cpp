#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> // Использовал консоль. Была проблема, что не мог найти шрифт. Пришлось задавать много условий где можно поискать шрифт. Консоль нужна была для того
                    // Чтобы выводить ошибку, если шрифт так и не найден
#include "Constants.h"
#include "Game.h"

	
int main()
{
	using namespace ApplesGame;

	std::cout << "Enter num of apples (default 20): ";
	int numApples;
	std::cin >> numApples;  // Просим ввести количество яблок

	if (numApples <= 0)
	{
		numApples = DEFAULT_NUM_APPLES;
		std::cout << "Using default: " << numApples << " apples\n";
	}
	else
	{
		std::cout << "Using: " << numApples << " apples\n";
	}

	std::cout << "Enter num of obstacles (default 5): ";
	int numObstacles;
	std::cin >> numObstacles; // Просим ввести количество препядствий

	if (numObstacles <= 0)
	{
		numObstacles = DEFAULT_NUM_OBSTACLES;
		std::cout << "Using default: " << numObstacles << " obstacles\n";
	}
	else
	{
		std::cout << "Using: " << numObstacles << " obstacles\n";
	}

	std::cout << "Enter num of bonus (default 2): ";
	int numCigarettes;
	std::cin >> numCigarettes; // ПРосим ввести количество бонусов на экране

	if (numCigarettes <= 0)
	{
		numCigarettes = DEFAULT_NUM_CIGARETTES;
		std::cout << "Using default: " << numCigarettes << " bonus\n";
	}
	else
	{
		std::cout << "Using: " << numCigarettes << " bonus\n";
	}
	
	// Инициализация генератора случайных чисел
	srand(static_cast<unsigned int>(time(nullptr)));

	// Инициализация окна
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!"); // создаёт окно 800 на 600 с заголовком "Apple game!"

	// Инициализация игры
	Game game;
	game.numApples = numApples; // Передаём количество яблок
	game.numObstacles = numObstacles; // Передаём количество препядствий
	game.numCigarettes = numCigarettes; // Передаём количество бонусов
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
