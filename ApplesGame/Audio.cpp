#include "Audio.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitAudio(Audio& audio)
	{
		audio.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "CoffeSound.wav");
		audio.eatSound.setBuffer(audio.eatSoundBuffer);
		audio.eatSound.setVolume(30.f);

		audio.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav");
		audio.gameOverSound.setBuffer(audio.gameOverSoundBuffer);
		audio.gameOverSound.setVolume(30.f);

		audio.cigaretteSoundBuffer.loadFromFile(RESOURCES_PATH + "Cigarette.wav");
		audio.cigaretteSound.setBuffer(audio.cigaretteSoundBuffer);
		audio.cigaretteSound.setVolume(60.f);
	}
	
	void PlayEatSound(Audio& audio)
	{
		audio.eatSound.play();
	}

	void PlayGameOverSound(Audio& audio)
	{
		audio.gameOverSound.play();
	}

	void PlayCigaretteSound(Audio& audio)
	{
		audio.cigaretteSound.play();
	}
}