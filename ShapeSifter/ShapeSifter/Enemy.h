#pragma once
#include "GameObject.h"
class Enemy: public GameObject
{
	GameObject* Target;
	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Enemy();
	virtual ~Enemy();

	//Functions
	virtual void setMovementDirection();

	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

