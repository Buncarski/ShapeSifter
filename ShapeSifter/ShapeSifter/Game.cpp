#include "Game.h"
#include <iostream>

void Game::initWindow()
{
	this->gameWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Same window level swap", sf::Style::Close | sf::Style::Titlebar);
	this->gameWindow->setFramerateLimit(60);
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

//Functions
void Game::Update()
{
	this->UpdateEventPolls();

	this->testObject->Update();

}

void Game::Render()
{
	this->gameWindow->clear();

	this->testObject->Render(this->gameWindow);
	this->player->Render(this->gameWindow);

	this->gameWindow->display();
}