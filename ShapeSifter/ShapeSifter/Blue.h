#pragma once
#include "Enemy.h"
#include "Common.h"
#include <SFML/Audio.hpp>
class Blue : public Enemy
{
private:

	//Init functions
	virtual void InitVars(GameObject& target, char direction) override;
	virtual void InitTexture(std::string texturePath) override;
	virtual void InitSprite() override;
public:
	//Constructors/destructors
	Blue();
	Blue(GameObject* target, char direction);
	virtual ~Blue();

	//Functions
	virtual void dealDamage(int damage) override;

	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

