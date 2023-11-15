#pragma once
#include "GameObject.h"
#include "Common.h"
class Enemy: public GameObject
{
protected:
	int hp;
	float flinchResistance;

	sf::Vector2f movementVector;
	sf::Vector2f movementModVector; //Vector for any additional modifications to the movement vector (for e.g. knockback)
	sf::RectangleShape hitbox;
	GameObject* target;
	//Init functions
	virtual void InitVars(GameObject& target, char direction);
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructors/destructors
	Enemy();
	Enemy(GameObject* target, char direction);
	virtual ~Enemy();

	//Functions
	virtual int GetHp();
	virtual void setMovementDirection();
	virtual sf::FloatRect GetHitbox() override;

	virtual void dealDamage(int damage);

	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

