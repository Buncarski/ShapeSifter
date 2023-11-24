#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>
class Player: public GameObject
{
	float bulletReshootTime;
	bool BulletShot;
	int maxHp;
	int playerHp;

	//Sounds
	sf::SoundBuffer bufferShoot;
	sf::SoundBuffer bufferHit;
	sf::SoundBuffer bufferDeath;
	sf::Sound soundShoot;
	sf::Sound soundHit;
	sf::Sound soundDeath;

	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Player();
	virtual ~Player();

	//Functions
	virtual int GetMaxHp();
	virtual int GetHp();
	virtual bool GetBulletCall();
	virtual float GetBulletReshootTime();

	virtual void TakeDamage(int damage);
	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

