#pragma once
#include "Enemy.h"
#include "Common.h"
#include <SFML/Audio.hpp>
class Yellow : public Enemy
{
private:
	//Variables
	enum BehavioralType {
		AGGRESSIVE = 0, FAKEOUT = 1
	};
	int behavior;
	float dodgeTimer;
	sf::RectangleShape detector;
	bool inDanger;


	//Init functions
	virtual void InitVars(GameObject& target, char direction) override;
	virtual void InitTexture(std::string texturePath) override;
	virtual void InitSprite() override;

public:
	//Constructors/destructors
	Yellow();
	Yellow(GameObject* target, char direction);
	virtual ~Yellow();

	//Getters/Setters
	virtual sf::RectangleShape GetDetector();
	//Functions
	virtual void dealDamage(int damage) override;

	virtual void Logic() override;
	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

