#pragma once
#include "audioPlayer.h"
#include "resource.h"

void AudioPlayer::PlaySound(int channel, std::string sound, float volume)
{
	PlaySound(channel, sound, 0, NULL, Mix_Volume (channel, volume));
}

void AudioPlayer::PlaySound(int channel, std::string sound, std::function<void(void)> callback, float volume)
{
	PlaySound(channel, sound, 0, callback, Mix_Volume(channel, volume));
}

void AudioPlayer::PlaySound(int channel, std::string sound, int times, float volume)
{
	PlaySound(channel, sound, times, NULL, Mix_Volume(channel, volume));
}

void AudioPlayer::PlaySound(int channel, std::string sound, int times, std::function<void(void)> callback, float volume)
{
	SoundResource* resource = ResourceManager::GetInstance()->LoadSoundResource(sound);
	if (resource == NULL)
	{
		std::cout << "Play Sound Error: " << sound << " can not play because load sound fail." << std::endl;;
		return;
	}

	Mix_PlayChannel(channel, resource->GetSoundChunk(), times);

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
