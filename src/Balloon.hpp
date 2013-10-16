#ifndef BALLOON_HPP
#define BALLOON_HPP

#include "defines.hpp"
#include "PhysObject.hpp"

class Balloon: public PhysObject 
{
    public:
        Balloon(float posx,float posy,float radius);
        virtual ~Balloon();

        //const sf::Vector2f& getDirection() const;
        //void setDirection(sf::Vector2f dir) { direction = dir; };

        virtual void move(const float time_sec);
        virtual bool isCollided(const PhysObject& other) const;

    protected:

        virtual bool isCollided(const Balloon& other) const;
        virtual bool isCollided(float posx, float posy) const;
        bool isCollided(float posx, float posy,float radius) const;

    private:
};

#endif
