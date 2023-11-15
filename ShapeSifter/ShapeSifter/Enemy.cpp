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
	this->hp = 999;
	this->flinchResistance = 4.f;

	this->InitTexture("Graphics/red_circle.png");
	this->InitSprite();

	//Hitbox stuff
	this->hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width - 16.f, this->sprite.getGlobalBounds().height - 16.f));
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));
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

int Enemy::GetHp()
{
	return this->hp;
}

void Enemy::setMovementDirection()
{
	float current_x = this->GetPos().x;
	float current_y = this->GetPos().y;

	float target_x = this->target->GetPos().x - current_x;
	float target_y = this->target->GetPos().y - current_y;

	float vecLength = sqrt((target_x * target_x) + (target_y * target_y));

	this->movementVector.x = ((target_x / vecLength) * this->movementSpeed) + movementModVector.x;
	this->movementVector.y = ((target_y / vecLength) * this->movementSpeed) + movementModVector.y;

	//Knockback falloff
	if (movementModVector.x < .05f && movementModVector.x > -0.05f) movementModVector.x = .0f;
	if (movementModVector.y < .05f && movementModVector.y > -0.05f) movementModVector.y = .0f;
	if (movementModVector.x != .0f) movementModVector.x *= 0.9f;
	if (movementModVector.y != .0f) movementModVector.y *= 0.9f;
}

sf::FloatRect Enemy::GetHitbox()
{
	return this->hitbox.getGlobalBounds();
}

void Enemy::dealDamage(int damage)
{
	this->hp -= damage;
	this->movementModVector += this->movementVector * (-flinchResistance);
}

void Enemy::Move()
{
	this->objectPos.x = this->objectPos.x + this->movementVector.x;
	this->objectPos.y = this->objectPos.y + this->movementVector.y;
	this->sprite.setPosition(this->objectPos);
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));

	this->setMovementDirection();
}

void Enemy::Update()
{
	this->Move();
	std::cout << this->movementModVector.x << " | " << movementModVector.y << "\n";
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
