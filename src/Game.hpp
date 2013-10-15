#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "defines.hpp"
#include "random.hpp"
#include "Balloon.hpp"
#include "Gui.hpp"

class Game
{
	public:
		static bool run();

	private:
		static bool initBalloons();
		static bool updateBalloons(const float time);
		static bool checkCollisions();
		static bool draw();

		static std::vector<Balloon> balloons;
		static sf::Clock clock;
};

#endif
