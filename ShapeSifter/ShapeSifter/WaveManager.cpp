#include "WaveManager.h"
#include <iostream>

void WaveManager::InitVars(std::vector<Enemy*>& enemy_ref, Player& player_ref)
{
	this->currentWave = 1;
	this->waveHealth = 3 * currentWave;
	this->maxEnemyCount = 5;

	this->spawnCutoff_red = 1.f;
	this->spawnCutoff_blue = .0f;
	this->spawnCutoff_yellow = .0f;

	//Refs
	this->enemies = &enemy_ref;
	this->player_ref = &player_ref;

	this->respawnTimer = .5f;
	this->respawnTimerMod = 0.f;

	//
	for (int esc : enemySpawnCount) esc = 0;

	this->weightManipulationMod = .95f;
}

WaveManager::WaveManager(std::vector<Enemy*>* enemy_ref, Player* player_ref)
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

void WaveManager::addDamageTaken(char enemyType)
{
	switch (enemyType) {
	case 'R': playerDamageTaken[0]++;
		break;
	case 'B': playerDamageTaken[1]++;
		break;
	case 'Y': playerDamageTaken[2]++;
		break;
	}
}

void WaveManager::resetDifficultyDeterminingVariables()
{
	for (int esc : enemySpawnCount) esc = 0;
	this->playerDamageTaken[0] = 0;
	this->playerDamageTaken[1] = 0;
	this->playerDamageTaken[2] = 0;
}

void WaveManager::UpdateSpawnWeights() {
	float maxSpawnChance = fmaxf(spawnCutoff_red, fmaxf(spawnCutoff_blue, spawnCutoff_yellow));
	if (maxSpawnChance == spawnCutoff_red) {
		spawnCutoff_red *= weightManipulationMod;
		spawnCutoff_blue = (1.f - spawnCutoff_red)/2.f;
		spawnCutoff_yellow = 1.f - spawnCutoff_red - spawnCutoff_blue;
	}
}

void WaveManager::NextWave()
{
	this->currentWave += 1;
	this->waveHealth = 3 * currentWave;

	this->UpdateSpawnWeights();

	this->resetDifficultyDeterminingVariables();
	
	//this->respawnTimerMod -= 1.f;
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
		this->enemySpawnCount[0]++; //Spawn Red
	}
	else if (r > spawnCutoff_red && r <= spawnCutoff_red + spawnCutoff_blue) {
		enemies->push_back(new Blue(this->player_ref, this->directions[direction]));
		this->enemySpawnCount[1]++; //Spawn Blue
	}
	else {
		enemies->push_back(new Yellow(this->player_ref, this->directions[direction]));
		this->enemySpawnCount[2]++; //Spawn Yellow
	}

	this->respawnTimer += 2.f + this->respawnTimerMod;
	std::cout << respawnTimer << "\n";
}



void WaveManager::Update()
{
	if (waveHealth <= 0) {
		NextWave();
	}
	std::cout << "Red: " << playerDamageTaken[0] << " Blue: " << playerDamageTaken[1] << " Yellow: " << playerDamageTaken[2] << "\n";
	spawnEnemy();
}
