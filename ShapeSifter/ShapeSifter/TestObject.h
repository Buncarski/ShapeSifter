#pragma once
#include "GameObject.h"
class TestObject: public GameObject
{

	//Init functions
	virtual void InitVars();
	virtual void InitTexture(std::string texturePath);
	virtual void InitSprite();

public:
	//Constructor/destructor
	TestObject();
	TestObject(std::string texturePath, float xPos, float yPos);
	virtual ~TestObject();

	//Functions
	virtual void Move() override;
	virtual void Update() override;
	virtual void Render(sf::RenderTarget* target) override;
};

