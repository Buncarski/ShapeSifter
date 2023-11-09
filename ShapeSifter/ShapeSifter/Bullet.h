#pragma once
#include "GameObject.h"
class Bullet: public GameObject
{
private:
	float mouseX;
	float mouseY;

	sf::Vector2f movementVector;
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
	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

