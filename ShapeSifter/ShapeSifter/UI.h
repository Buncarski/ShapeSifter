#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "WaveManager.h"
#include "Player.h"

#include <format>

class UI
{
private:
	//Refs
	Player* player_ref;
	WaveManager* waveManager_ref;

	//Text
	sf::Font font;
	sf::Text defeatText;
	sf::Text waveText;
	sf::Text healthText;
	void initVars(WaveManager& wm, Player& player);
	void initFont();
	void initText();
	
public:
	//Constructors/Destructors
	UI();
	UI(WaveManager* wm, Player* player);
	virtual ~UI();

	//Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

