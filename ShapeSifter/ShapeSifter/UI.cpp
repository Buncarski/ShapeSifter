#include "UI.h"

void UI::initVars(WaveManager& wm, Player& player)
{
	this->player_ref = &player;
	this->waveManager_ref = &wm;
}

void UI::initFont()
{
	if (!font.loadFromFile("Misc/pixpopenei.ttf"))
	{
		std::cout << "FAILED TO LOAD FONT\n";
	}

	
}

void UI::initText()
{
	//Defeat
	defeatText.setFont(font);
	defeatText.setString("YOU LOST");
	defeatText.setCharacterSize(48);
	defeatText.setFillColor(sf::Color::White);
	defeatText.setOutlineColor(sf::Color::Black);
	defeatText.setOutlineThickness(4.f);
	defeatText.setPosition(window_x / 2 - defeatText.getGlobalBounds().width / 2, window_y / 2 - defeatText.getGlobalBounds().height / 2);

	//Wave
	waveText.setFont(font);
	waveText.setCharacterSize(32);
	waveText.setFillColor(sf::Color::White);
	waveText.setOutlineColor(sf::Color::Black);
	waveText.setOutlineThickness(4.f);
	waveText.setPosition(20.f, 20.f);

	//Health
	healthText.setFont(font);
	healthText.setCharacterSize(32);
	healthText.setFillColor(sf::Color::White);
	healthText.setOutlineColor(sf::Color::Black);
	healthText.setOutlineThickness(4.f);
	healthText.setPosition(220.f, 20.f);

}

void UI::initTex()
{
	this->hp_tex = new sf::Texture();
	this->hp_tex->loadFromFile("Graphics/Health.png");
}

void UI::initSprites()
{
	for (int i = 0; i < this->player_ref->GetMaxHp(); i++) {
		this->hp_sprites.push_back(new sf::Sprite());
		this->hp_sprites[i]->setTexture(*this->hp_tex);
		this->hp_sprites[i]->setScale(2.5f, 2.5f);
		this->hp_sprites[i]->setPosition(healthText.getGlobalBounds().getPosition().x + 128.f + 32.f * i,
			healthText.getGlobalBounds().top);
	}
}

UI::UI()
{
	
}

UI::UI(WaveManager* wm, Player* player)
{
	this->initVars(*wm, *player);
	this->initFont();
	this->initText();
	this->initTex();
	this->initSprites();
}

UI::~UI()
{
	for (sf::Sprite* s : hp_sprites) delete s;
	delete hp_tex;
}

void UI::Update()
{
	waveText.setString("Wave: " + std::to_string(waveManager_ref->GetCurrentWave()));

	healthText.setString("Health: ");
}

void UI::Render(sf::RenderTarget* target)
{
	target->draw(waveText);
	target->draw(healthText);
	for (int i = 0; i < player_ref->GetHp(); i++) {
		target->draw(*hp_sprites[i]);
	}

	if (player_ref->GetHp() <= 0) {
		target->draw(defeatText);
	}
}
