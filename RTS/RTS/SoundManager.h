#pragma once
#include "raylib.h"
#include <vector>
#include <string>

struct SoundManager
{
	std::vector<Music*> musicAmbients;
	Music* currentMusicAmbients = nullptr;

	void AddMusicAmbients(const char* path);
	void Update();

	void ChangeMusicAmbiant();
	void Close();

	~SoundManager();
};

