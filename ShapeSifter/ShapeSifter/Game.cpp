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

void Game::initMisc()
{
	//Init WaveManager
	this->waveManager = new WaveManager();

	//Set BG music
	int random = rand() % 3;
	if (!music.openFromFile(songList[random])) {
		std::cout << "Song not found\n";
	}
	music.setVolume(20.f);

	if (!destroyBuffer.loadFromFile("Sfx/shoot.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}

	destroySound.setBuffer(destroyBuffer);
	destroySound.setPitch(0.5f);
	destroySound.setVolume(20.f);

	this->isPaused = false;
	this->playerDefeated = false;

	if (!font.loadFromFile("Misc/pixpopenei.ttf"))
	{
		std::cout << "FAILED TO LOAD FONT\n";
	}

	defeatText.setFont(font);
	defeatText.setString("YOU LOSE");
	defeatText.setCharacterSize(48);
	defeatText.setFillColor(sf::Color::White);
	defeatText.setOutlineColor(sf::Color::Black);
	defeatText.setOutlineThickness(4.f);
	defeatText.setPosition(window_x/2 - defeatText.getGlobalBounds().width/2, window_y / 2 - defeatText.getGlobalBounds().height / 2);
}

Game::Game()
{
	this->initWindow();
	this->initObject();
	this->initMisc();
	
	music.play();
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

void Game::PauseGame()
{
	if (this->isPaused = false) {
		this->isPaused = true;
	}
	else {
		this->isPaused = false;
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

void Game::UpdateEnemies()
{
	int iter_enemy = 0;
	//Update
	for (Enemy* e : enemies) {
		e->Update();

	}

	//Remove
	for (Enemy* e : enemies) {
		if (e->GetHitbox().intersects(player->GetHitbox())) {
			player->TakeDamage(1);
			enemies.erase(enemies.begin() + iter_enemy);
			delete e;
		} else if (e->GetHp() <= 0) {
			destroySound.play();
			enemies.erase(enemies.begin() + iter_enemy);
			delete e;

			this->waveManager->damageWave(1);
		}
		iter_enemy++;
	}
}

void Game::UpdateCollisions()
{
	int iter_bullet = 0;

	for (Bullet* b : bullets) {
		//Game checks if bullet hits enemy when bullet no longer exists
		for (Enemy* e : enemies) {
			if (b->GetHitbox().intersects(e->GetHitbox())) {
				e->dealDamage(b->GetDamage());
				bullets.erase(bullets.begin() + iter_bullet);
				delete b;
				break;
			}
		}
		iter_bullet++;
	}
}

//Functions
void Game::Update()
{
	
	//Check for pause
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		PauseGame();
		std::cout << "pausing";
	}

	if (this->isPaused) {
		std::cout << this->isPaused << "\n";
	}

	if (player->GetHp() > 0) {
		//EnemySpawn
		if (waveManager->GetWaveHealth() > 0) {
			int spawnChance = rand() % 100;
			if (spawnChance == 1) {
				this->spawnEnemy('R');
			}
		}


		this->UpdateEventPolls();

		this->testObject->Update();

		//Player related
		if (this->player->GetBulletCall()) {
			this->conjureBullet();
		}
		this->player->Update();

		if (bullets.size() > 0) {
			this->UpdateBullets();
		}

		//NPC related
		this->UpdateEnemies();

		//Collisions
		this->UpdateCollisions();
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

	for (Enemy* e : enemies) {
		e->Render(this->gameWindow);
	}

	if (player->GetHp() <= 0) {
		this->gameWindow->draw(defeatText);
	}

	this->gameWindow->display();
}

void Game::conjureBullet()
{
	bullets.push_back(new Bullet(sf::Mouse::getPosition(*this->gameWindow)));
}

void Game::spawnEnemy(char enemySpawnType)
{
	//Random Spawn selection
	int random = rand() % 4;
	switch (enemySpawnType) {
	case 'R': 
		enemies.push_back(new Red(this->player, this->directions[random]));
		break;

	case 'B':
		enemies.push_back(new Blue(this->player, this->directions[random]));
		break;

	case 'Y':
		enemies.push_back(new Blue(this->player, this->directions[random]));
		break;

	default:
		std::cout << "Unknown Enemy Spawn Call\n";
	}
}
