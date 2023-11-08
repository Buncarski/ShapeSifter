#pragma once
#include "GameObject.h"
class Player: public GameObject
{
	int bulletReshootTime;

	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Player();
	virtual ~Player();

	//Functions
	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

