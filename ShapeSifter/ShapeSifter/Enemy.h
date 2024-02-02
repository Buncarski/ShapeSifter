#pragma once
#include "GameObject.h"
#include "Common.h"
#include <SFML/Audio.hpp>
class Enemy: public GameObject
{
protected:
	int maxHp;
	int hp;
	float flinchResistance;
	char type;

	sf::Vector2f movementVector;
	sf::Vector2f movementModVector; //Vector for any additional modifications to the movement vector (for e.g. knockback)
	sf::RectangleShape hitbox;
	GameObject* target;

	//Sounds
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//Additional sprites
	sf::Texture* damagedTex;
	sf::Sprite damagedSprite;

	bool destroy;

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
	virtual void Logic();
	virtual int GetHp();
	virtual sf::Vector2f GetObjectTargetVector(); //Gets normalized vector between Object and Target
	virtual sf::Vector2f GetObjectTargetVector(sf::Vector2f targetPos); //Gets normalized vector between Object and Target Pos
	virtual void setMovementDirection();
	virtual sf::FloatRect GetHitbox() override;
	virtual char GetEnemyType();
	virtual bool GetDestroyCall();
	virtual void SetDestroyCall();

	virtual void dealDamage(int damage);

	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

