#include "WaveManager.h"
#include <iostream>

void WaveManager::InitWave()
{
	this->currentWave = 1;
	this->waveHealth = 5 * currentWave;
}

WaveManager::WaveManager()
{
	this->InitWave();
}

WaveManager::~WaveManager()
{
}

int WaveManager::GetCurrentWave()
{
	return this->currentWave;
}

void WaveManager::SetCurrentWave()
{
}

int WaveManager::GetWaveHealth()
{
	return this->waveHealth;
}

void WaveManager::SetWaveHealth()
{
}

void WaveManager::NextWave()
{
	this->currentWave += 1;
	this->waveHealth = 5 * currentWave;
}

void WaveManager::damageWave(int damage)
{
	waveHealth -= damage;
	//std::cout << "Current wave health: " << waveHealth;
}

void WaveManager::ResetWave()
{

}

void WaveManager::Update()
{
	if (waveHealth <= 0) {
		NextWave();
	}
}
