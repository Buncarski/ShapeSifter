#include "Player.h"

void Player::InitVars()
{
	this->bulletReshootTime = 0;
	this->SetPos(0.f, 0.f);
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

void Player::Move()
{
}

void Player::Update()
{

}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
