#pragma once
#include "resource.h"
#include <functional>
#include <SDL_mixer.h>

class AudioPlayer
{
public:
	void PlaySound(int channel, std::string sound, int volume);
	void PlaySound(int channel, std::string sound, int times, int volume);
	void PlaySound(int channel, std::string sound, std::function<void(void)> callback, int volume);
	void PlaySound(int channel, std::string sound, int times, std::function<void(void)> callback, int volume);
	void PlayMusic(std::string music);
	static AudioPlayer* GetInstance();
private:
	static AudioPlayer* s_instance;
};