#include "Bullet.h"
void Bullet::InitVars()
{
	float center_x = window_x / 2;
	float center_y = window_y / 2;
	
	this->mouseX -= center_x;
	this->mouseY -= center_y;
	this->hitTarget = false;

	float vecLength = sqrt((mouseX * mouseX) + (mouseY * mouseY));
	this->movementSpeed = 6.0f;
	this->SetPos(window_x / 2 - 8, window_y / 2 - 8);
	
	this->movementVector.x = (mouseX / vecLength) * this->movementSpeed;
	this->movementVector.y = (mouseY / vecLength) * this->movementSpeed;

	this->damage = 1;
}

void Bullet::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);
}

void Bullet::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);
}

Bullet::Bullet()
{
	this->InitVars();
	this->InitTexture("Graphics/bullet.png");
	this->InitSprite();
}

Bullet::Bullet(sf::Vector2i mousePos)
{
	mouseX = mousePos.x;
	mouseY = mousePos.y;
	this->InitVars();
	this->InitTexture("Graphics/bullet.png");
	this->InitSprite();
}

Bullet::~Bullet()
{
	delete this->texture;
}

int Bullet::GetDamage()
{
	return this->damage;
}

bool Bullet::GetHitTarget()
{
	return hitTarget;
}

void Bullet::SetToDestroy()
{
	this->hitTarget = true;
}

void Bullet::Move()
{
	this->objectPos.x = this->objectPos.x + this->movementVector.x;
	this->objectPos.y = this->objectPos.y + this->movementVector.y;
	this->sprite.setPosition(this->objectPos);
}

void Bullet::Update()
{
	this->Move();
}

void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
