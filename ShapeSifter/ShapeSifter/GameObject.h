#pragma once
#include<SFML/Graphics.hpp>
class GameObject
{
protected:
	//Attributes
	sf::Vector2f objectPos;
	sf::Texture* texture;
	sf::Sprite sprite;
	float movementSpeed;

public:
	//Constructor/destructor
	GameObject() = default;
	virtual ~GameObject() = default;

	//Init functions
	
	//Functions

	//Getters/Setters
	virtual void SetPos(float x, float y) {
		this->objectPos.x = x;
		this->objectPos.y = y;
	}

	virtual void SetScale(float sX, float sY) {
		this->sprite.setScale(sX, sY);
	};
	virtual sf::Vector2f GetPos() {
		return this->objectPos;
	};

	virtual void Move() = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
};

