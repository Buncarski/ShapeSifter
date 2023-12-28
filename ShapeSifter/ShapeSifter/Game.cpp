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
	this->backgroundImage = new TestObject();
	this->player = new Player();
}

void Game::initMisc()
{
	//Init WaveManager
	this->waveManager = new WaveManager(&this->enemies, &this->bullets, this->player);

	//Init UI
	this->ui = new UI(this->waveManager, this->player, &this->isPaused);

	//Set BG music
	int random = rand() % 3;
	if (!music.openFromFile(songList[random])) {
		std::cout << "Song not found\n";
	}
	music.setVolume(20.f);

	if (!destroyBuffer.loadFromFile("Sfx/shoot.wav")) {
		std::cout << "Failed to load shoot.wav\n";
	}

	if (!pauseBuffer.loadFromFile("Sfx/pause.ogg")) {
		std::cout << "Failed to load pause.ogg\n";
	}

	if (!unpauseBuffer.loadFromFile("Sfx/unpause.ogg")) {
		std::cout << "Failed to load unpause.ogg\n";
	}

	sfx_destroy.setBuffer(destroyBuffer);
	sfx_destroy.setPitch(0.5f);
	sfx_destroy.setVolume(20.f);

	sfx_pause.setBuffer(pauseBuffer);
	sfx_pause.setVolume(20.f);

	sfx_unpause.setBuffer(unpauseBuffer);
	sfx_unpause.setVolume(20.f);

	this->isPaused = false;
	this->playerDefeated = false;

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
	delete this->ui;
	for (Bullet* b : bullets) delete b;
	for (Enemy* e : enemies) delete e;
	delete this->player;
	delete this->backgroundImage;
	delete this->waveManager;
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
	if (rePauseTime > 0.f) {
		rePauseTime -= 1.f / static_cast<float>(refreshRate);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		return;
	}
	
	if (rePauseTime <= 0.f) {
		
		if (this->isPaused == false) {
			this->isPaused = true;
			sfx_pause.play();
			music.pause();
			std::cout << "Works main";
		}
		else {
			this->isPaused = false;
			sfx_unpause.play();
			music.play();
			std::cout << "Works else";

		}
		rePauseTime += .5f;
	}
}

void Game::UpdateMusic()
{
	if (this->music.getStatus() == sf::Sound::Stopped) {
		int random = rand() % 3;
		if (!music.openFromFile(songList[random])) {
			std::cout << "Song not found\n";
		}
		std::cout << "Song changed\n";
		music.play();
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
		if (e->GetHitbox().intersects(player->GetHitbox())) { //On player collision
			player->TakeDamage(1);
			waveManager->addDamageTaken(e->GetEnemyType());
			enemies.erase(enemies.begin() + iter_enemy);
			delete e;
		} else if (e->GetHp() <= 0) { //On death
			sfx_destroy.play();
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
	//Pausing
	this->UpdateEventPolls();
	PauseGame();

	if (this->isPaused) {
		return;
	}

	if (player->GetHp() > 0) {

		this->waveManager->Update();

		this->backgroundImage->Update();

		this->UpdateMusic();

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

		this->ui->Update();
	}
}

void Game::Render()
{
	this->gameWindow->clear();

	this->backgroundImage->Render(this->gameWindow);

	if (bullets.size() > 0) {
		for (GameObject* b : bullets) {
			b->Render(this->gameWindow);
		}
	}

	for (Enemy* e : enemies) {
		e->Render(this->gameWindow);
	}

	this->player->Render(this->gameWindow);

	this->ui->Render(this->gameWindow);

	this->gameWindow->display();
}

void Game::conjureBullet()
{
	bullets.push_back(new Bullet(sf::Mouse::getPosition(*this->gameWindow)));
}
