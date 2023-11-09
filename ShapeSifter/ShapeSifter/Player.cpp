#include "Player.h"

void Player::InitVars()
{
	this->bulletReshootTime = .0f;
	this->SetPos(window_x/2 - 32, window_y/2 - 32);
	this->BulletShot = false;
}

void Player::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);
}

void Player::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);
}

Player::Player()
{
	this->InitVars();
	this->InitTexture("Graphics/player.png");
	this->InitSprite();
}

Player::~Player()
{
	delete this->texture;
}

bool Player::GetBulletCall()
{
	return this->BulletShot;
}

float Player::GetBulletReshootTime()
{
	return this->bulletReshootTime;
}

void Player::Move()
{
	
	if (this->bulletReshootTime <= .0f) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			this->BulletShot = true;
			this->bulletReshootTime = 0.2f;
		}
	}
	else {
		if(BulletShot = true) BulletShot = false;
		this->bulletReshootTime -= (1.f / refreshRate);
	}
	
}

void Player::Update()
{
	this->Move();
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}