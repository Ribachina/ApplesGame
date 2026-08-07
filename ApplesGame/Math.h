#pragma once

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size);

	bool IsCirclesCollide(Position2D circ1Position, float circ1Radius,
		Position2D circ2Position, float circ2Radius);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}