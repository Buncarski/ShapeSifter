#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->gameWindow = new sf::RenderWindow(sf::VideoMode(window_x, window_y), "Shape Sifter", sf::Style::Close | sf::Style::Titlebar);
	this->gameWindow->setFramerateLimit(refreshRate);
	this->gameWindow->setVerticalSyncEnabled(false);
}

void Game::initObject()
{
	this->testObject = new TestObject();
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initObject();
}

Game::~Game()
{
	delete this->gameWindow;
}

const bool Game::windowOpened() const
{
	return this->gameWindow->isOpen();
}


void Game::Run()
{
	while (this->gameWindow->isOpen())
	{
		this->Update();

		this->Render();
	}
}

void Game::UpdateEventPolls()
{
	while (this->gameWindow->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			this->gameWindow->close();
	}
}

void Game::UpdateBullets() {

	int iter = 0;

	//Update
	for (GameObject* b : bullets) {
		b->Update();
	}

	//Remove
	for (GameObject* b : bullets) {
		if (b->GetPos().x >= window_x || b->GetPos().x < -16 || b->GetPos().y < -16 || b->GetPos().y >= 800) {
			bullets.erase(bullets.begin() + iter);
			delete b;
		}
		iter++;

	}
}

//Functions
void Game::Update()
{

	this->UpdateEventPolls();

	this->testObject->Update();
	if (this->player->GetBulletCall()) {
		this->conjureBullet();
	}
	this->player->Update();
	if (bullets.size() > 0) {
		this->UpdateBullets();
	}
}

void Game::Render()
{
	this->gameWindow->clear();

	this->testObject->Render(this->gameWindow);

	if (bullets.size() > 0) {
		for (GameObject* b : bullets) {
			b->Render(this->gameWindow);
		}
	}
	this->player->Render(this->gameWindow);

	this->gameWindow->display();
}

void Game::conjureBullet()
{
	bullets.push_back(new Bullet(sf::Mouse::getPosition(*this->gameWindow)));
}
