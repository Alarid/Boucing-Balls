#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>
#include "math.h"
#include "const.hpp"

class Balloon: public sf::CircleShape
{
    public:
        Balloon(float posx,float posy,float radius,int sideGuiSize);
        bool isClicked(int posx, int posy);
        bool isCollided(Balloon b);
        bool isCollided(float posx, float posy, float radius);
        void invertDirection();
        void run();

        int getDirectionX() { return direction.x; };
        int getDirectionY() { return direction.y; };
        sf::Vector2f getDirection() { return sf::Vector2f(direction.x, direction.y); };
        void setDirection(sf::Vector2f dir) { direction = dir; };

    private:
        sf::Vector2f direction;
        int sideGuiSize;
};

#endif
