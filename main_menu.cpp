#include "main_menu.h"

main_menu::main_menu(float width, float height)
{
	if (!font.loadFromFile("Tigerious.otf"))
	{
		std::cout << "error";
	}

	//menu : play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("Play");
	menu[0].setCharacterSize(100);
	menu[0].setPosition(sf::Vector2f(width / 2 + 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	//menu : credit
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Credit");
	menu[1].setCharacterSize(100);
	menu[1].setPosition(sf::Vector2f(width / 2 + 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	//menu : exit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(100);
	menu[2].setPosition(sf::Vector2f(width / 2 + 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

main_menu::~main_menu()
{
}

void main_menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void main_menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

void main_menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}
