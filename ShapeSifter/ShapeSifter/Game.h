#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameObject.h"
#include "TestObject.h"
#include "Player.h"
#include "Common.h"
#include "bullet.h"
#include "Enemy.h"
#include "Red.h"
#include "Blue.h"

#include<cstdlib>
class Game
{
private:
	//Attributes
	sf::RenderWindow* gameWindow;
	sf::Event ev;

	GameObject* testObject;
	Player* player;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	char directions[4] = {'N','S','W','E'};
	char enemyType[3] = {'R','B','Y'};
	std::string songList[3] = {"Sfx/Music/song_0.ogg", "Sfx/Music/song_1.ogg", "Sfx/Music/song_2.ogg"};
	sf::Music music;

	//Destroy sound
	sf::SoundBuffer destroyBuffer;
	sf::Sound destroySound;


	void initWindow();
	virtual void initObject();
	void initMisc();

public:
	//Constructor and destructor
	Game();
	Game(const Game&) = default;
	virtual ~Game();

	//
	const bool windowOpened() const;

	//Functions
	void Run();

	void UpdateEventPolls();
	void UpdateBullets();
	void UpdateEnemies();
	void UpdateCollisions();
	void Update();
	void Render();
	void conjureBullet();
	void spawnEnemy(char enemySpawnType);
};

