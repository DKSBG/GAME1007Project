#pragma once
#include "audioPlayer.h"
#include "resource.h"

void AudioPlayer::PlaySound(std::string sound)
{
	PlaySound(sound, 0, NULL);
}

void AudioPlayer::PlaySound(std::string sound, std::function<void(void)> callback)
{
	PlaySound(sound, 0, callback);
}

void AudioPlayer::PlaySound(std::string sound, int times)
{
	PlaySound(sound, times, NULL);
}

void AudioPlayer::PlaySound(std::string sound, int times, std::function<void(void)> callback)
{
	SoundResource* resource = ResourceManager::GetInstance()->LoadSoundResource(sound);
	if (resource == NULL)
	{
		std::cout << "Play Sound Error: " << sound << " can not play because load sound fail." << std::endl;;
		return;
	}

	Mix_PlayChannel(-1, resource->GetSoundChunk(), times);

	if (callback != NULL)
		callback();
}

void AudioPlayer::PlayMusic(std::string music) 
{
	MusicResource *resource = ResourceManager::GetInstance()->LoadMusicResource(music);
	if (resource == NULL) 
	{
		std::cout << "Play Music Error: " << music << " can not play because load music fail." << std::endl;;
		return;
	}
	Mix_PlayMusic(resource->GetMusic(), -1);
}

AudioPlayer* AudioPlayer::GetInstance() 
{
	if (s_instance == NULL)
		s_instance = new AudioPlayer();
	return s_instance;
}

AudioPlayer* AudioPlayer::s_instance = NULL;
