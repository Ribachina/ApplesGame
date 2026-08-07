#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct Audio
	{
		sf::SoundBuffer eatSoundBuffer;
		sf::Sound eatSound;

		sf::SoundBuffer gameOverSoundBuffer;
		sf::Sound gameOverSound;

		sf::SoundBuffer cigaretteSoundBuffer;
		sf::Sound cigaretteSound;
	};

	void InitAudio(Audio& audio);
}