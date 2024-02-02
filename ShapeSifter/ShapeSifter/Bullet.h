#pragma once
#include "GameObject.h"
class Bullet: public GameObject
{
private:
	float mouseX;
	float mouseY;
	bool hitTarget;

	sf::Vector2f movementVector;
	int damage;

	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Bullet();
	Bullet(sf::Vector2i mousePos);
	virtual ~Bullet();

	//Functions
	virtual int GetDamage();
	virtual bool GetHitTarget();
	virtual void SetToDestroy();

	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

