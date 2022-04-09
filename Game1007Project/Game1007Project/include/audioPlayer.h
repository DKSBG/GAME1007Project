#pragma once
#include "resource.h"
#include <functional>

class AudioPlayer
{
public:
	void PlaySound(std::string sound);
	void PlaySound(std::string sound, int times);
	void PlaySound(std::string sound, std::function<void(void)> callback);
	void PlaySound(std::string sound, int times, std::function<void(void)> callback);
	void PlayMusic(std::string music);
	static AudioPlayer* GetInstance();
private:
	static AudioPlayer* s_instance;
};