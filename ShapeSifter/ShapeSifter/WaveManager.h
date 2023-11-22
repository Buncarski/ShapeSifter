#pragma once
class WaveManager
{
private:
	int currentWave;
	int waveHealth;



	void InitWave();
public:
	WaveManager();
	virtual ~WaveManager();

	int GetCurrentWave();
	void SetCurrentWave();
	int GetWaveHealth();
	void SetWaveHealth();

	void NextWave();
	void damageWave(int damage);
	void ResetWave();
	
	void Update();
};

