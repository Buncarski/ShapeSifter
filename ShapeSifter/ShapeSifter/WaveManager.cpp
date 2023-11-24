#include "WaveManager.h"
#include <iostream>

void WaveManager::InitVars(std::vector<Enemy*>& enemy_ref, GameObject& player_ref)
{
	this->currentWave = 1;
	this->waveHealth = 5 * currentWave;
	this->maxEnemyCount = 5;

	this->spawnCutoff_red = 1.f;
	this->spawnCutoff_blue = .0f;
	this->spawnCutoff_yellow = .0f;

	//Refs
	this->enemies = &enemy_ref;
	this->player_ref = &player_ref;

	this->respawnTimer = 2.f;
	this->respawnTimerMod = 0.f;
}

WaveManager::WaveManager(std::vector<Enemy*>* enemy_ref, GameObject* player_ref)
{
	this->InitVars(*enemy_ref, *player_ref);
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

std::vector<Enemy*> WaveManager::GetEnemyVector()
{
	return *this->enemies;
}

void WaveManager::NextWave()
{
	this->currentWave += 1;
	this->waveHealth = 5 * currentWave;
	
	
	this->respawnTimerMod -= 1.f;
}

void WaveManager::damageWave(int damage)
{
	waveHealth -= damage;
	//std::cout << "Current wave health: " << waveHealth;
}

void WaveManager::ResetWave()
{

}

void WaveManager::spawnEnemy()
{
	if (this->respawnTimer > .0f) {
		this->respawnTimer -= 1.f / refreshRate;
		return;
	}

	if (enemies->size() > maxEnemyCount) return;


	//Random Spawn selection
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	int direction = rand() % 4;
	
	if (r <= spawnCutoff_red) {
		enemies->push_back(new Red(this->player_ref, this->directions[direction]));
	}
	else if (r > spawnCutoff_red && r <= spawnCutoff_red + spawnCutoff_blue) {
		enemies->push_back(new Blue(this->player_ref, this->directions[direction]));
	}
	else {
		enemies->push_back(new Yellow(this->player_ref, this->directions[direction]));
	}

	this->respawnTimer += 2.f + this->respawnTimerMod;
	std::cout << respawnTimer << "\n";
}

void WaveManager::Update()
{
	if (waveHealth <= 0) {
		NextWave();
	}

	spawnEnemy();
}
