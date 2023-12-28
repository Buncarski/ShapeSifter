#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Red.h"
#include "Blue.h"
#include "bullet.h"
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

	float weightManipulationMod;

	int enemySpawnCount[3]; // 0 - Red, 1 - Blue, 2 - Yellow
	int playerDamageTaken[3]; // 0 - Red, 1 - Blue, 2 - Yellow
	int maxDiffEnemy;

	float respawnTimer;
	float respawnTimerMod;
	
	Player* player_ref;
	std::vector<Enemy*>* enemies;
	std::vector<Bullet*>* bullets;

	char directions[4] = { 'N','S','W','E' };
	//char enemyType[3] = { 'R','B','Y' };

	void InitVars(std::vector<Enemy*>& enemy_ref, std::vector<Bullet*>& bullet_ref, Player& player_ref);
public:
	WaveManager(std::vector<Enemy*>* enemy_ref, std::vector<Bullet*>* bullet_ref, Player* player_ref);
	virtual ~WaveManager();

	int GetCurrentWave();
	void SetCurrentWave();
	int GetWaveHealth();
	void SetWaveHealth();
	std::vector<Enemy*> GetEnemyVector();

	void addDamageTaken(char enemyType);
	void resetDifficultyDeterminingVariables();

	void UpdateSpawnWeights();
	void NextWave();
	void damageWave(int damage);
	void ResetWave();
	
	void spawnEnemy();

	void Update();
};

