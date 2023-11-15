#include "Enemy.h"

void Enemy::InitVars(GameObject& target, char direction)
{
	srand((unsigned)time(NULL));
	switch (direction) {
	case 'N': 
		this->SetPos(rand() % window_x, -32.f);
		break;
	case 'S':
		this->SetPos(rand() % window_x, window_y);
		break;
	case 'W':
		this->SetPos(-32.f, rand() % window_y);
		break;
	case 'E':
		this->SetPos(window_x, rand() % window_y);
		break;
	}
	this->target = &target;
	this->movementSpeed = 1.f;

	this->InitTexture("Graphics/red_circle.png");
	this->InitSprite();

	//Hitbox stuff
	//this->hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width - 8.f, this->sprite.getGlobalBounds().height - 8.f));
	//this->hitbox.setPosition(this->sprite.getPosition());
}

void Enemy::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);
}

void Enemy::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);
}

Enemy::Enemy()
{
	//Default constructor - Never used
}

Enemy::Enemy(GameObject* target, char direction)
{
	this->InitVars(*target, direction);
	this->setMovementDirection();
}

Enemy::~Enemy()
{
	delete this->texture;
}

void Enemy::setMovementDirection()
{
	float current_x = this->GetPos().x;
	float current_y = this->GetPos().y;

	float target_x = this->target->GetPos().x - current_x;
	float target_y = this->target->GetPos().y - current_y;

	float vecLength = sqrt((target_x * target_x) + (target_y * target_y));

	this->movementVector.x = (target_x / vecLength) * this->movementSpeed;
	this->movementVector.y = (target_y / vecLength) * this->movementSpeed;
}

void Enemy::Move()
{
	this->objectPos.x = this->objectPos.x + this->movementVector.x;
	this->objectPos.y = this->objectPos.y + this->movementVector.y;
	this->sprite.setPosition(this->objectPos);
}

void Enemy::Update()
{
	this->Move();
	std::cout << this->objectPos.x << "\n";
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
