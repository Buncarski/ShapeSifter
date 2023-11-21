#include "Player.h"

void Player::InitVars()
{
	this->playerHp = 2;
	this->bulletReshootTime = .0f;
	this->SetPos(window_x/2 - 32, window_y/2 - 32);
	this->BulletShot = false;

	//Sound loading
	if (!bufferShoot.loadFromFile("Sfx/shoot.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}
	if (!bufferHit.loadFromFile("Sfx/hit_player.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}
	if (!bufferDeath.loadFromFile("Sfx/death.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}

	soundShoot.setBuffer(bufferShoot);
	soundHit.setBuffer(bufferHit);
	soundDeath.setBuffer(bufferDeath);

	soundShoot.setVolume(20.f);
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

int Player::GetHp()
{
	return this->playerHp;
}

bool Player::GetBulletCall()
{
	return this->BulletShot;
}

float Player::GetBulletReshootTime()
{
	return this->bulletReshootTime;
}

void Player::TakeDamage(int damage)
{
	this->playerHp -= damage;

	//Damage/Death sfx
	if (this->playerHp > 0) {
		soundHit.play();
	}
	else {
		soundDeath.play();
	}
}

void Player::Move()
{
	
	if (this->bulletReshootTime <= .0f) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			soundShoot.play();
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