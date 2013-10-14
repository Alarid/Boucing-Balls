#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdlib.h>
#include <iostream>

#include "defines.hpp"

class Gui
{
	public:
		static bool init();
		static bool draw();
		static bool update(const int secs);

		static sf::RenderWindow window;
		static sf::Texture sideGui;

	private:
		static sf::Texture bg;
		static sf::Sprite bgSpr, sideGuiSpr;
		static sf::Font guiFont;
		static sf::Text guiCountdown;
};

#endif