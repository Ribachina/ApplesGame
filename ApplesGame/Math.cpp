#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Position.x - rect2Position.x);         // fabs(x1-x2)    расстояние по X 
		float dy = (float)fabs(rect1Position.y - rect2Position.y);         // fabs (y1-y2)   расстояние по Y
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&                 // dx = fabs(x1-x2) <= (a+b)/2 &&     
			dy <= (rect1Size.y + rect2Size.y) / 2.f);                      // dy = fabs(y1-y2) <= (a+b)/2
	}

	bool IsCirclesCollide(Position2D circ1Position, float circ1Radius, Position2D circ2Position, float circ2Radius)
	{
		float squareDistance = (circ1Position.x - circ2Position.x) * (circ1Position.x - circ2Position.x) +  // (х2-х1) * (х2-х1) +
			(circ1Position.y - circ2Position.y) * (circ1Position.y - circ2Position.y);                      // (y2-y1) * (y2-y1)
		float squareRadiusSum = (circ1Radius + circ2Radius) * (circ1Radius + circ2Radius);                  // (r1+r2) * (r1+r2) / 4
		return squareDistance <= squareRadiusSum;
	}
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { (desiredWidth / spriteRect.width), (desiredHeight / spriteRect.height) }; // Размер спрайта (Димы)
		sprite.setScale(scale);
	}
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}
}


