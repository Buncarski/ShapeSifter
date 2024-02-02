#include "Yellow.h"

void Yellow::InitVars(GameObject& target, std::vector<Bullet*>& bullet_ref, char direction)
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
	this->movementSpeed = 2.5f;
	this->maxHp = 1;
	this->hp = this->maxHp;
	this->flinchResistance = 2.f;

	this->InitTexture("Graphics/yellow_triangle.png");
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

	this->type = 'Y';

	//Behavioral stuff
	int behaviorDecider = rand() % 2;
	this->behavior = behaviorDecider;
	this->decision = DECISION_NONE;

	this->dodgeTimer = .0f;
	this->setMovementDirection();
	this->fakeoutChance = .8f;
	this->reDecideTimer = .0f;

	
	this->detector.setPosition(this->GetPos().x + this->GetObjectTargetVector().x * 100.f, 
		this->GetPos().y + this->GetObjectTargetVector().y * 100.f);
	this->detector.setFillColor(sf::Color::Red);
	this->detector.setSize(sf::Vector2f(44.f, 44.f));
	this->bullet_ref = &bullet_ref;

	std::cout << behavior << "\n";
}

void Yellow::InitTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);

	this->damagedTex = new sf::Texture();
	this->damagedTex->loadFromFile("Graphics/crack.png");
}

void Yellow::InitSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);
	this->sprite.setScale(0.6f, 0.6f);

	this->damagedSprite.setTexture(*this->damagedTex);
	this->damagedSprite.setPosition(this->objectPos);
	this->damagedSprite.setScale(0.6f, 0.6f);
}

Yellow::Yellow()
{
}

Yellow::Yellow(GameObject* target, std::vector<Bullet*>* bullet_ref, char direction)
{
	this->InitVars(*target, *bullet_ref, direction);
}

Yellow::~Yellow()
{
}

sf::RectangleShape Yellow::GetDetector()
{
	return this->detector;
}

void Yellow::setMovementDirection()
{
	if (this->decision == DECISION_FAKEOUT) return;

	sf::Vector2f objectTargetVector = this->GetObjectTargetVector();

	this->movementVector.x = (objectTargetVector.x * this->movementSpeed);
	this->movementVector.y = (objectTargetVector.y * this->movementSpeed);

	//std::cout << dodgeTimer << "\n";
	//Dodge falloff
	if (dodgeVector.x < .05f && dodgeVector.x > -0.05f) dodgeVector.x = .0f;
	if (dodgeVector.y < .05f && dodgeVector.y > -0.05f) dodgeVector.y = .0f;
	if (dodgeVector.x != .0f) dodgeVector.x *= 0.95f;
	if (dodgeVector.y != .0f) dodgeVector.y *= 0.95f;
}

void Yellow::dealDamage(int damage)
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


void Yellow::UpdateDodgeVector()
{
	//Timer update
	if (this->dodgeTimer > 0.0f)
		this->dodgeTimer -= 1.f / refreshRate;
}

void Yellow::MakeDecision()
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	std::cout << r << "\n";
	if (r <= fakeoutChance) {
		this->decision = DECISION_FAKEOUT;

		this->movementVector.x *= -2.f;
		float tmp = movementVector.x;
		this->movementVector.x = this->movementVector.y;
		this->movementVector.y = tmp;
	}
	else {
		this->decision = DECISION_COMMIT;
	}
	this->reDecideTimer = 2.f;
}

void Yellow::Logic()
{
	if (reDecideTimer > 0.0f) {
		reDecideTimer -= 1.5f/refreshRate;
	}

	if (reDecideTimer <= 0.0f) {
		this->decision = DECISION_NONE;
	}

	//Aggressive behavioral type
	if (this->behavior == AGGRESSIVE) {
		for (Bullet* b : *this->bullet_ref) {
			if (this->detector.getGlobalBounds().intersects(b->GetHitbox())) {
				if (this->dodgeTimer <= 0.0f) {
					this->dodgeTimer = 2.f;
					this->dodgeVector = this->movementVector * 2.f;
					this->dodgeVector.x *= -1.f;
					float tmp = dodgeVector.x;
					this->dodgeVector.x = this->dodgeVector.y;
					this->dodgeVector.y = tmp;
				}
			}
		}
	}
	
	//Fakeout behavioral type
	if (this->behavior == FAKEOUT) {
		//Is bullet in front of me? - decision tree node - yes
		for (Bullet* b : *this->bullet_ref) {
			if (this->detector.getGlobalBounds().intersects(b->GetHitbox())) {
				if (this->dodgeTimer <= 0.0f) {
					this->dodgeTimer = 2.f;
					this->dodgeVector = this->movementVector * 2.f;
					this->dodgeVector.x *= -1.f;
					float tmp = dodgeVector.x;
					this->dodgeVector.x = this->dodgeVector.y;
					this->dodgeVector.y = tmp;
				}
				return;
			}
		}

		//Is bullet in front of me? - decision tree node - no
		if (this->detector.getGlobalBounds().intersects(this->target->GetHitbox())) {
			if (this->reDecideTimer <= 0.f) {
				this->MakeDecision();
			}
		}
	}
}

void Yellow::Move()
{

	if (this->decision == DECISION_FAKEOUT) {

		this->objectPos.x = this->objectPos.x + this->movementVector.x + this->dodgeVector.x;
		this->objectPos.y = this->objectPos.y + this->movementVector.y + this->dodgeVector.y;
	}
	else {
		this->movementModVector *= 0.f;
		this->objectPos.x = this->objectPos.x + this->movementVector.x + this->dodgeVector.x;
		this->objectPos.y = this->objectPos.y + this->movementVector.y + this->dodgeVector.y;
	}

	//Sprite positions
	this->sprite.setPosition(this->objectPos);
	this->hitbox.setPosition(sf::Vector2f(this->objectPos.x + 8.f, this->objectPos.y + 8.f));
	this->detector.setPosition(this->GetPos().x + this->GetObjectTargetVector().x * 100.f,
		this->GetPos().y + this->GetObjectTargetVector().y * 100.f); 
	
	this->setMovementDirection();
	this->UpdateDodgeVector();
}

void Yellow::Update()
{
	this->Logic();
	this->Move();
}

void Yellow::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	//target->draw(this->detector);
}

