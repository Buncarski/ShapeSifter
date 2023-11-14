#pragma once
#include "GameObject.h"
#include "Common.h"
class Enemy: public GameObject
{
protected:
	sf::Vector2f movementVector;
	GameObject* target;
	//Init functions
	virtual void InitVars(GameObject* target, char direction);
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Enemy();
	Enemy(GameObject* target, char direction);
	virtual ~Enemy();

	//Functions
	virtual void setMovementDirection();

	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

