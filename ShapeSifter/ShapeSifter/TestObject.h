#pragma once
#include "GameObject.h"
class TestObject: public GameObject
{

	//Init functions
	void initVars();
	virtual void initTexture(std::string texturePath);
	virtual void initSprite();

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

