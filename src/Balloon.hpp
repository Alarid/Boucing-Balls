#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>
#include <math.h>
#include "defines.hpp"

class Balloon: public sf::CircleShape
{
    public:
        Balloon(float posx,float posy,float radius,int id);

        bool isClicked(int posx, int posy)const;
        bool isCollided(const Balloon& other)const;
        bool isCollided(float posx, float posy, float radius)const;

        void invertDirection();
        void run();

        /*int getDirectionX() {return direction.x; };
        int getDirectionY() {return direction.y; };*/

        const sf::Vector2f& getDirection() const;
        void setDirection(sf::Vector2f dir) { direction = dir; };

    private:
        sf::Vector2f direction;
};

#endif
