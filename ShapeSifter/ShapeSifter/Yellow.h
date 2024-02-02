#pragma once
#include "Enemy.h"
#include "Common.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
class Yellow : public Enemy
{
private:
	//Enums
	enum BehavioralType {
		AGGRESSIVE = 0, FAKEOUT = 1
	};
	enum Decision {
		DECISION_NONE = 0, DECISION_COMMIT = 1, DECISION_FAKEOUT = 2
	};

	//Variables
	int behavior;
	float dodgeTimer;
	sf::RectangleShape detector;
	bool inDanger;
	sf::Vector2f dodgeVector;

	//Fakeout vars
	float fakeoutChance;
	int decision;
	float reDecideTimer;

	std::vector<Bullet*>* bullet_ref;

	//Init functions
	virtual void InitVars(GameObject& target, std::vector<Bullet*>& bullet_ref, char direction);
	virtual void InitTexture(std::string texturePath) override;
	virtual void InitSprite() override;

public:
	//Constructors/destructors
	Yellow();
	Yellow(GameObject* target, std::vector<Bullet*>* bullet_ref, char direction);
	virtual ~Yellow();

	//Getters/Setters
	virtual sf::RectangleShape GetDetector();
	virtual void setMovementDirection() override;
	//Functions
	virtual void dealDamage(int damage) override;
	virtual void UpdateDodgeVector();
	virtual void MakeDecision();

	virtual void Logic() override;
	virtual void Move();
	virtual void Update();
	virtual void Render(sf::RenderTarget* target);
};

