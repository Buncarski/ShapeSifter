#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>
class Player: public GameObject
{
	float bulletReshootTime;
	bool BulletShot;

	//Sounds
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Player();
	virtual ~Player();

	//Functions
	virtual bool GetBulletCall();
	virtual float GetBulletReshootTime();

	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

