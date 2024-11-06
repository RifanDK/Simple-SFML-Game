#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>



class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Texture windowtexture;
	sf::Sprite windowsprite;
	sf::Texture playertexture;
	sf::Texture playerattack;
	sf::Sprite playersprite;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;


	
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::RectangleShape player;
	sf::Texture enemytexture1;
	sf::Texture enemytexture2;
	sf::Texture enemytexture3;
	sf::Texture enemytexture4;
	sf::Font gamefont;
	sf::Text gametext;
	sf::Font gameoverfont;
	sf::Text gameovertext;

	void initVariables();
	void initWindow();
	void initEnemies();
	void initplayer();
	void initfonts();
	void inittext();
	void initgameoverfont();
	void initgameovertext();

public:

	Game();
	virtual ~Game();

	const bool running() const;
	const bool getEndGame() const;

	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateplayer();
	void updatetext();
	void update();

	void renderEnemies(sf::RenderTarget& target);
	void renderplayer(sf::RenderTarget& target);
	void rendertext(sf::RenderTarget& target);
	void render();
};