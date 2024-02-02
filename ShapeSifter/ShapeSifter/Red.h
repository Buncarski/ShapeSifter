#pragma once
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "Common.h"
#include "Enemy.h"

class Red : public Enemy
{
private:
	sf::Vector2f targetPos;
	std::vector<Enemy*>* enemies;


	//Init functions
	virtual void InitVars(GameObject& target, std::vector<Enemy*>& enemies_ref, char direction);
	virtual void InitTexture(std::string texturePath) override;
	virtual void InitSprite() override;
public:
	//Constructors/destructors
	Red();
	Red(GameObject* target, std::vector<Enemy*>* enemies_ref, char direction);
	virtual ~Red();

	//Functions
	virtual void dealDamage(int damage) override;
	virtual float GetObjectTargetVectorLength(sf::Vector2f targetPos);
	virtual sf::Vector2f GetObjectTargetVector(sf::Vector2f targetPos) override;
	virtual void setMovementDirection() override;
	virtual void Logic() override;
	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

