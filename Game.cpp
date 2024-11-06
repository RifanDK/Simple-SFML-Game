#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	this->endGame = false;
	this->points = 0;
	this->health = 100;
	this->enemySpawnTimerMax = 15.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 12;
}

void Game::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1280;

	this->window = new sf::RenderWindow(this->videoMode, "At All Cost");

	this->window->setFramerateLimit(60);

	
	if (!windowtexture.loadFromFile("background_re.png", sf::IntRect(0, 0, 1280, 720)))
	{
		std::cout << "error";
	}

	
	windowsprite.setTexture(windowtexture);

	this->window->draw(windowsprite);

	
}

void Game::initEnemies()
{

	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));

	//sf::Texture enemytexture;
	//if (!enemytexture.loadFromFile("enemybasic.png"))
	//{
		//std::cout << "error";
	//}

	//this->enemy.setTexture(&enemytexture);
	//this->enemy.setRotation(180);
	
}

void Game::initplayer()
{
	this->player.setSize(sf::Vector2f(100.f, 100.f));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		if (!playerattack.loadFromFile("player_attack.png"))
		{
			std::cout << "error";
		}
		
		this->player.setTexture(&playerattack);
	}
	else
	{

		if (!playertexture.loadFromFile("player_idle.png"))
		{
			std::cout << "error";
		}

		this->player.setTexture(&playertexture);
	}
}

void Game::initfonts()
{
	if (!this->gamefont.loadFromFile("joystix monospace.ttf"))
	{
		std::cout << "error to load font";
	}
}

void Game::inittext()
{
	this->gametext.setFont(gamefont);
	this->gametext.setCharacterSize(20);
	this->gametext.setPosition(20, 20);
	this->gametext.setFillColor(sf::Color::White);
	this->gametext.setString("IF YOU SEE THIS ITS WORKS");
}

void Game::initgameoverfont()
{
	if (!this->gameoverfont.loadFromFile("Debug.otf"))
	{
		std::cout << "error to load font";
	}
}

void Game::initgameovertext()
{
	this->gameovertext.setFont(gameoverfont);
	this->gameovertext.setCharacterSize(80);
	this->gameovertext.setFillColor(sf::Color::Red);
	this->gameovertext.setString("!!GAME OVER!!");
	this->gameovertext.setPosition(this->window->getSize().x / 2.f - this->gameovertext.getGlobalBounds().width / 2.f,
								   this->window->getSize().y / 2.f - this->gameovertext.getGlobalBounds().height / 2.f);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initfonts();
	this->inittext();
	this->initEnemies();
	this->initplayer();
	this->initgameoverfont();
	this->initgameovertext();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

		int type = rand() % 4;

		switch (type)
		{
		case 0:
			this->enemy.setSize(sf::Vector2f(120.f, 120.f));
			this->enemy.setFillColor(sf::Color::Magenta);
			if (!enemytexture2.loadFromFile("enemybasic1.png"))
			{
				std::cout << "error";
			}

			this->enemy.setTexture(&enemytexture2);
			break;

		case 1:
			this->enemy.setSize(sf::Vector2f(120.f, 120.f));
			this->enemy.setFillColor(sf::Color::Cyan);
			if (!enemytexture3.loadFromFile("enemybasic4.png"))
			{
				std::cout << "error";
			}

			this->enemy.setTexture(&enemytexture3);
			break;

		case 2:
			this->enemy.setSize(sf::Vector2f(120.f, 120.f));
			this->enemy.setFillColor(sf::Color::Blue);
			if (!enemytexture4.loadFromFile("enemybasic3.png"))
			{
				std::cout << "error";
			}

			this->enemy.setTexture(&enemytexture4);
			break;

		default:
			this->enemy.setSize(sf::Vector2f(120.f, 120.f));
			this->enemy.setFillColor(sf::Color::Red);
			if (!enemytexture1.loadFromFile("enemybasic.png"))
			{
				std::cout << "error";
			}

			this->enemy.setTexture(&enemytexture1);
			break;
		}

		this->enemy.setRotation(180);
		


	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				std::cout << "esc pressed, game ended";
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i].getFillColor() == sf::Color::Magenta)
			this->enemies[i].move(7.f, 30.f);
		else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
			this->enemies[i].move(-7.f, 20.f);
		else if (this->enemies[i].getFillColor() == sf::Color::Blue)
			this->enemies[i].move(7.f, 17.f);
		else if (this->enemies[i].getFillColor() == sf::Color::Red)
			this->enemies[i].move(-7.f, 16.f);

		//this->enemies[i].move(0.f, 15.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			if (this->enemies[i].getFillColor() == sf::Color::Magenta)
				this->health -= 10;
			else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
				this->health -= 7;
			else if (this->enemies[i].getFillColor() == sf::Color::Blue)
				this->health -= 5;
			else if (this->enemies[i].getFillColor() == sf::Color::Red)
				this->health -= 3;

			//this->health -= 5;
		}

		
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			int isdodge = 0; //( 0 = belum dodge || 1 == dodge || 2 == sudah dodge )
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					
					if (isdodge == 0)
					{
						int dodgerange = rand() % 2;

						if (dodgerange == 1)
						{
							this->enemies[i].move(200.f, 0.f);
							isdodge = 1;
						}
						else if (dodgerange == 2)
						{
							this->enemies[i].move(-200.f, 0.f);
							isdodge = 1;
						}
						else isdodge = 1;
					}

					else if (isdodge == 1)
					{
						this->enemies.erase(this->enemies.begin() + i);
					}

					
					
					
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;

					//deleted = true;
					//this->enemies.erase(this->enemies.begin() + i);
					//points = points + 10;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateplayer()
{
	this->player.setSize(sf::Vector2f(100.f, 100.f));
	this->player.setScale(sf::Vector2f(1.f, 1.f));


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (!playerattack.loadFromFile("player_attack.png"))
		{
			std::cout << "error";
		}
		
		this->player.setTexture(&playerattack);
		//this->player.setTextureRect(sf::IntRect(0, 0, 500, 500));

	}
	else
	{

		if (!playertexture.loadFromFile("player_idle.png"))
		{
			std::cout << "error";
		}

		this->player.setTexture(&playertexture);
		//this->player.setTextureRect(sf::IntRect(0, 0, 500, 500));
	}

	this->player.setPosition(mousePosView);


}

void Game::updatetext()
{
	std::stringstream ss;

	ss << "PLAYER 1" << "\n"
	   << "Planet Health : " << this->health << "\n"
	   <<"Points :" << this->points;

	this->gametext.setString(ss.str());
}

void Game::update()
{
	//this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updatetext();

		this->updateEnemies();

		this->updateplayer();

	}

	//End game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderEnemies(sf::RenderTarget& target)
{

	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderplayer(sf::RenderTarget& target)
{
	target.draw(this->player);
}

void Game::rendertext(sf::RenderTarget& target)
{
	target.draw(this->gametext);
}


void Game::render()
{
	
	this->window->clear();
	this->window->draw(windowsprite);

	//Draw game objects
	this->renderEnemies(*this->window);
	this->renderplayer(*this->window);

	this->rendertext(*this->window);

	if (this->endGame ==true)
	{
		//this->window->clear();
		this->window->draw(gameovertext);
	}

	this->window->display();
}