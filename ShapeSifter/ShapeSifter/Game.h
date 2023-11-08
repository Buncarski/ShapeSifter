#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "TestObject.h"
#include "Player.h"
class Game
{
private:
	//Attributes
	sf::RenderWindow* gameWindow;
	sf::Event ev;

	GameObject* testObject;
	GameObject* player;

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
	void Update();
	void Render();

};

