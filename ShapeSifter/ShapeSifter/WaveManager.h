#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Red.h"
#include "Blue.h"
#include "Yellow.h"
class WaveManager
{
private:
	int currentWave;
	int waveHealth;
	int maxEnemyCount;
	
	float spawnCutoff_red;
	float spawnCutoff_blue;
	float spawnCutoff_yellow;

	float respawnTimer;
	float respawnTimerMod;
	
	GameObject* player_ref;
	std::vector<Enemy*>* enemies;

	char directions[4] = { 'N','S','W','E' };
	char enemyType[3] = { 'R','B','Y' };

	void InitVars(std::vector<Enemy*>& enemy_ref, GameObject& player_ref);
public:
	WaveManager(std::vector<Enemy*>* enemy_ref, GameObject* player_ref);
	virtual ~WaveManager();

	int GetCurrentWave();
	void SetCurrentWave();
	int GetWaveHealth();
	void SetWaveHealth();
	std::vector<Enemy*> GetEnemyVector();


	void NextWave();
	void damageWave(int damage);
	void ResetWave();
	
	void spawnEnemy();

	void Update();
};

