#include "Blue.h"

void Blue::InitVars(GameObject& target, char direction)
{
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
	this->movementSpeed = .7f;
	this->maxHp = 15;
	this->hp = this->maxHp;
	this->flinchResistance = .5f;

	this->InitTexture("Graphics/blue_square.png");
	this->InitSprite();

	//Hitbox stuff
	this->hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width - 16.f, this->sprite.getGlobalBounds().height - 16.f));
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));

	if (!buffer.loadFromFile("Sfx/hit.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}
	//Sounds
	sound.setBuffer(buffer);
	sound.setVolume(30.f);

	this->type = 'B';
}

void Blue::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);

	this->damagedTex = new sf::Texture();
	this->damagedTex->loadFromFile("Graphics/crack.png");
}

void Blue::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);

	this->damagedSprite.setTexture(*this->damagedTex);
	this->damagedSprite.setPosition(this->objectPos);
}

Blue::Blue()
{
}

Blue::Blue(GameObject* target, char direction)
{
	this->InitVars(*target, direction);
	this->setMovementDirection();
}

Blue::~Blue()
{
}

void Blue::dealDamage(int damage)
{
	this->hp -= damage;
	this->movementModVector += this->movementVector * (-flinchResistance);

	//Hurt sound
	if (hp != 0) {
		int max = 30;
		int min = -30;
		int pitchOffsetBounds = rand() % (max - min + 1) + min;

		float pitchOffset = static_cast<float>(pitchOffsetBounds) / 100.f;

		sound.setPitch(1.f + pitchOffset);
		sound.play();
	}
}

void Blue::Logic()
{

}

void Blue::Move()
{
	this->objectPos.x = this->objectPos.x + this->movementVector.x + movementModVector.x;
	this->objectPos.y = this->objectPos.y + this->movementVector.y + movementModVector.y;
	this->sprite.setPosition(this->objectPos);
	this->damagedSprite.setPosition(this->objectPos);
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));

	this->setMovementDirection();
}

void Blue::Update()
{
	this->Logic();
	this->Move();
}

void Blue::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

	if (hp < maxHp) {
		target->draw(this->damagedSprite);
	}
}
