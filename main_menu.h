#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3


class main_menu
{
public:

	main_menu(float width, float height);
	~main_menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() {return selectedItemIndex;}

private:

	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

