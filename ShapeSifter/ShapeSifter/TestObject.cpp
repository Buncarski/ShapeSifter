#include "TestObject.h"


//Variable functions

void TestObject::initVars() {
	this->SetPos(0.f, 0.f);
	this->movementSpeed = 1.f;
}

void TestObject::initTexture(std::string texturePath)
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(texturePath);
}

void TestObject::initSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(this->objectPos);
}

TestObject::TestObject()
{
	this->initVars();
	this->initTexture("Graphics/test-img.jpg");
	this->initSprite();
}

TestObject::TestObject(std::string texturePath, float xPos, float yPos)
{
}

TestObject::~TestObject()
{
	delete this->texture;
}

void TestObject::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->objectPos.x += movementSpeed * -1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->objectPos.y += movementSpeed * -1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->objectPos.y += movementSpeed * 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->objectPos.x += movementSpeed * 1.f;

	this->sprite.setPosition(this->objectPos);
}

void TestObject::Update()
{
	this->Move();
}

void TestObject::Render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
