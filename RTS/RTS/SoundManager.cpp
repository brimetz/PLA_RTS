#include "SoundManager.h"
#include <time.h> 
#include <iostream> 

void SoundManager::AddMusicAmbients(const char* path)
{
	musicAmbients.push_back(new Music(LoadMusicStream(path)));
}

void SoundManager::Update()
{
	if (!currentMusicAmbients)
		ChangeMusicAmbiant();

	UpdateMusicStream(*currentMusicAmbients);   // Update music buffer with new stream data


	if (IsKeyPressed(KEY_SPACE))
	{
		ChangeMusicAmbiant();
	}

	float timePlayed = GetMusicTimePlayed(*currentMusicAmbients) / GetMusicTimeLength(*currentMusicAmbients) * 400;

	if (timePlayed > 400)
	{
		ChangeMusicAmbiant();
	}
}

void SoundManager::ChangeMusicAmbiant()
{
	if (currentMusicAmbients)
		StopMusicStream(*currentMusicAmbients);

	int random = (rand() % ((musicAmbients.size() - 1) - 0 + 1)) + 0;

	currentMusicAmbients = musicAmbients[random];
	PlayMusicStream(*currentMusicAmbients);
}

void SoundManager::Close()
{
	StopMusicStream(*currentMusicAmbients);
	for (int i = 0; i < musicAmbients.size(); i++)
	{
		UnloadMusicStream(*musicAmbients[i]);
	}
}

SoundManager::~SoundManager()
{}
