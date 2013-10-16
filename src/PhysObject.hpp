#ifndef PHYSOBJECT_HPP
#define PHYSOBJECT_HPP

#include <SFML/Graphics.hpp>

class PhysEngine;
class Game;
class Balloon;

class PhysObject
{

    public:
        PhysObject(float dirx,float diry);
        PhysObject(const PhysObject&) = delete; //delete copy
        PhysObject& operator=(const PhysObject&) = delete; //delete copy

        virtual ~PhysObject();

        void draw(sf::RenderTarget &target,sf::RenderStates states=sf::RenderStates::Default)const;

        virtual void move(const float time_sec) = 0;

        virtual bool isCollided(const PhysObject& other) const =0;

    protected:
        friend class PhysEngine;
        friend class Game;
        friend class Balloon;

        virtual bool isCollided(const Balloon& _1)const = 0;

        virtual bool isCollided(float posx, float posy) const = 0;

        sf::Shape* shape;
        sf::Vector2f direction;
};

#endif
