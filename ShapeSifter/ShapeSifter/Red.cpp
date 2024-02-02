#include "Red.h"

void Red::InitVars(GameObject& target, std::vector<Enemy*>& enemies_ref, char direction)
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
	this->movementSpeed = 1.f;
	this->maxHp = 3;
	this->hp = this->maxHp;
	this->flinchResistance = 2.f;
	this->enemies = &enemies_ref;
	this->targetPos = target.GetPos();

	this->InitTexture("Graphics/red_circle.png");
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

	this->type = 'R';
}

void Red::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);

	this->damagedTex = new sf::Texture();
	this->damagedTex->loadFromFile("Graphics/crack.png");
}

void Red::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);

	this->damagedSprite.setTexture(*this->damagedTex);
	this->damagedSprite.setPosition(this->objectPos);
}

Red::Red()
{
}

Red::Red(GameObject* target, std::vector<Enemy*>* enemies_ref, char direction)
{
	this->InitVars(*target, *enemies_ref, direction);
	this->setMovementDirection();
}

Red::~Red()
{
}

void Red::dealDamage(int damage)
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

float Red::GetObjectTargetVectorLength(sf::Vector2f targetPos)
{
	float current_x = this->GetPos().x;
	float current_y = this->GetPos().y;

	float target_x = targetPos.x - current_x;
	float target_y = targetPos.y - current_y;

	float vecLength = sqrt((target_x * target_x) + (target_y * target_y));

	return vecLength;
}

sf::Vector2f Red::GetObjectTargetVector(sf::Vector2f targetPos)
{
	float current_x = this->GetPos().x;
	float current_y = this->GetPos().y;

	float target_x = targetPos.x - current_x;
	float target_y = targetPos.y - current_y;

	float vecLength = sqrt((target_x * target_x) + (target_y * target_y));

	return sf::Vector2f(target_x / vecLength, target_y / vecLength);
}

void Red::setMovementDirection()
{
	sf::Vector2f objectTargetVector = this->GetObjectTargetVector(this->targetPos);

	this->movementVector.x = (objectTargetVector.x * this->movementSpeed);
	this->movementVector.y = (objectTargetVector.y * this->movementSpeed);

	//Knockback falloff
	if (movementModVector.x < .05f && movementModVector.x > -0.05f) movementModVector.x = .0f;
	if (movementModVector.y < .05f && movementModVector.y > -0.05f) movementModVector.y = .0f;
	if (movementModVector.x != .0f) movementModVector.x *= 0.9f;
	if (movementModVector.y != .0f) movementModVector.y *= 0.9f;
}

void Red::Logic()
{
	std::vector<Enemy*> blues;
	

	std::copy_if(this->enemies->begin(), this->enemies->end(), std::back_inserter(blues), [](Enemy* e) {return e->GetEnemyType() == 'B'; });
	
	//target = player
	if (blues.size() == 0) {
		//std::cout << "No blues\n";
		this->targetPos = this->target->GetPos();
		return;
	}
	Enemy* closestBlue = nullptr;

	//Finds closest blue enemy
	for (Enemy* b : blues) {
		if (closestBlue == nullptr) {
			closestBlue = b;
			continue;
		}

		if (GetObjectTargetVectorLength(closestBlue->GetPos()) > GetObjectTargetVectorLength(b->GetPos())) {
			closestBlue = b;
		}
	}

	if (GetObjectTargetVectorLength(closestBlue->GetPos()) > 200.f) {
		//std::cout << "Not within distance\n";
		this->targetPos = this->target->GetPos();
		return;
	}

	if (GetObjectTargetVectorLength(closestBlue->GetPos()) >= GetObjectTargetVectorLength(this->target->GetPos())) {
		//std::cout << "Further than player: Blue: " << GetObjectTargetVectorLength(closestBlue->GetPos()) << " || Player: " << GetObjectTargetVectorLength(this->target->GetPos());
		this->targetPos = sf::Vector2f(closestBlue->GetPos().x + (closestBlue->GetObjectTargetVector().x * 100.f), 
			closestBlue->GetPos().y + (closestBlue->GetObjectTargetVector().y * 100.f));
		return;
	}
	else {
		//std::cout << "Further than blue: Blue: " << GetObjectTargetVectorLength(closestBlue->GetPos()) << " || Player: " << GetObjectTargetVectorLength(this->target->GetPos());
		this->targetPos = sf::Vector2f(closestBlue->GetPos().x + (closestBlue->GetObjectTargetVector().x * -100.f),
			closestBlue->GetPos().y + (closestBlue->GetObjectTargetVector().y * -100.f));
	}
}

void Red::Move()
{
	this->setMovementDirection();

	this->objectPos.x = this->objectPos.x + this->movementVector.x + movementModVector.x;
	this->objectPos.y = this->objectPos.y + this->movementVector.y + movementModVector.y;
	this->sprite.setPosition(this->objectPos);
	this->damagedSprite.setPosition(this->objectPos);
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));

}

void Red::Update()
{
	this->Logic();
	this->Move();
}

void Red::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

	if (hp < maxHp) {
		target->draw(this->damagedSprite);
	}
}
