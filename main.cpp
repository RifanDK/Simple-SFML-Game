#include <iostream>
#include "Game.h"
#include "main_menu.h"


int main()
{
	int state = 0; // 0 = menu || 1 = play (play using bool playpressed) || 2 = credit

	sf::SoundBuffer gamesound;
	sf::Sound gamemusic;

	if (!gamesound.loadFromFile("BLACK_SUN.ogg"))
	{
		std::cout << "error";
	}

	gamemusic.setBuffer(gamesound);
	gamemusic.setLoop(true);
	gamemusic.play();


	bool startpressed = false;

	std::srand(static_cast<unsigned>(time(NULL)));


	sf::RenderWindow mainwindow(sf::VideoMode(1280, 720), "At All Cost");

	mainwindow.setFramerateLimit(60);

	main_menu menu(mainwindow.getSize().x, mainwindow.getSize().y);

	while (mainwindow.isOpen())
	{
		sf::Event event;

		while (mainwindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					if (state != 0) break;
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed, game start" << std::endl;
						startpressed = true;

						if (startpressed == true)
						{
							mainwindow.close();
							Game game;
							while (game.running())
							{
								game.pollEvents();

								if (!game.getEndGame())
								{	
									//update game
									game.update();

								}
								//render game
								game.render();

							}
						}
						break;

					case 1:
						std::cout << "Credit button has been pressed" << std::endl;
						state = 2;

						break;

					case 2:
						mainwindow.close();
						break;
					}

					break;

				case sf::Keyboard::BackSpace:
					std::cout << "Back Button has been pressed"<<std::endl;
					state = 0;
					break;
				}

				break;
			case sf::Event::Closed:
				mainwindow.close();

				break;

			}
		}

		mainwindow.clear();

		sf::Sprite mainwinsprite;
		sf::Texture mainwintexture;

		switch (state) {
		case 0:
		{
			if (!mainwintexture.loadFromFile("menu_background.png", sf::IntRect(0, 0, 1280, 720)))
			{
				std::cout << "error";
			}

			mainwinsprite.setTexture(mainwintexture);

			break;
		}
		case 2:
		{
			if (!mainwintexture.loadFromFile("game_credit.png", sf::IntRect(0, 0, 1280, 720)))
			{
				std::cout << "error";
			}

			mainwinsprite.setTexture(mainwintexture);

			break;
		}
		}

		mainwindow.draw(mainwinsprite);
		if(state == 0) menu.draw(mainwindow);

		mainwindow.display();

	}

	return 0;
}