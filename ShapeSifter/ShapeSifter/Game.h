#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TestObject.h"
#include "Player.h"
#include "Common.h"
#include "bullet.h"
class Game
{
private:
	//Attributes
	sf::RenderWindow* gameWindow;
	sf::Event ev;

	GameObject* testObject;
	Player* player;
	std::vector<GameObject*> bullets;

	void initWindow();
	virtual void initObject();

public:
	//Constructor and destructor
	Game();
	Game(const Game&) = default;
	virtual ~Game();

	//
	const bool windowOpened() const;

	//Functions
	void Run();

	void UpdateEventPolls();
	void UpdateBullets();
	void Update();
	void Render();
	void conjureBullet();
};

