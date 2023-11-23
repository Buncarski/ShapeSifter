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
	bool* pause_ref;

	//Text
	sf::Font font;
	sf::Text defeatText;
	sf::Text waveText;
	sf::Text healthText;
	sf::Text pauseText;

	//Graphics
	sf::Texture* hp_tex;
	std::vector<sf::Sprite*> hp_sprites;

	sf::Texture* pause_tex;
	sf::Sprite pause_sprite;

	void initVars(WaveManager& wm, Player& player, bool& pause);
	void initFont();
	void initText();
	void initTex();
	void initSprites();
	
public:
	//Constructors/Destructors
	UI();
	UI(WaveManager* wm, Player* player, bool* pause);
	virtual ~UI();

	//Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

