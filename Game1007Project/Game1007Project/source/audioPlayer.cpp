#pragma once
#include "audioPlayer.h"
#include "resource.h"

void AudioPlayer::PlaySound(int channel, std::string sound, int volume)
{
	PlaySound(channel, sound, 0, NULL, volume);
}

void AudioPlayer::PlaySound(int channel, std::string sound, std::function<void(void)> callback, int volume)
{
	PlaySound(channel, sound, 0, callback, volume);
}

void AudioPlayer::PlaySound(int channel, std::string sound, int times, int volume)
{
	PlaySound(channel, sound, times, NULL,  volume);
}

void AudioPlayer::PlaySound(int channel, std::string sound, int times, std::function<void(void)> callback, int volume)
{
	SoundResource* resource = ResourceManager::GetInstance()->LoadSoundResource(sound);
	if (resource == NULL)
	{
		std::cout << "Play Sound Error: " << sound << " can not play because load sound fail." << std::endl;;
		return;
	}

	int usingChannel = Mix_PlayChannel(channel, resource->GetSoundChunk(), times);
	if (usingChannel != -1)
		Mix_Volume(usingChannel, volume);

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
	Mix_VolumeMusic(40);
	Mix_PlayMusic(resource->GetMusic(), -1);
}

AudioPlayer* AudioPlayer::GetInstance() 
{
	if (s_instance == NULL)
		s_instance = new AudioPlayer();
	return s_instance;
}

AudioPlayer* AudioPlayer::s_instance = NULL;
