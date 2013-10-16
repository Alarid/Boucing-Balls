#include "Balloon.hpp"
//#include <math.h>
#include "random.hpp"

#include "Gui.hpp"

#include <iostream>


Balloon::Balloon (float posx,float posy,float radius) : PhysObject((random(0,1)*2-1)*SPEED,(random(0,1)*2-1)*SPEED)
{
    shape = new sf::CircleShape(radius);

	shape->setFillColor(sf::Color::Green);
	shape->setOutlineColor(sf::Color::White);
	shape->setOutlineThickness(3);

    shape->setOrigin(radius,radius);
	shape->setPosition(posx, posy);
}

Balloon::~Balloon()
{
    delete reinterpret_cast<sf::CircleShape*>(shape);
}

bool Balloon::isCollided(const PhysObject& other) const
{
    return other.isCollided(*this);
}

bool Balloon::isCollided(const Balloon& other) const
{
    const sf::Vector2f& other_pos = other.shape->getPosition();
    return isCollided(other_pos.x,other_pos.y,reinterpret_cast<sf::CircleShape*>(other.shape)->getRadius());
}

bool Balloon::isCollided(float posx, float posy)const
{
    return isCollided(posx,posy,0);
}

bool Balloon::isCollided(float posx, float posy, float radius)const
{
	const sf::Vector2f& pos = shape->getPosition();
	float xd = pos.x - posx;
	float yd = pos.y - posy;

    return sqrt(xd*xd + yd*yd) <= reinterpret_cast<sf::CircleShape*>(shape)->getRadius() + radius;
}

void Balloon::move(const float time)
{

    sf::Vector2f future_pos(shape->getPosition() + direction*(time*METTER_PER_SECOND));
    float myradius = reinterpret_cast<sf::CircleShape*>(shape)->getRadius();
    auto sideGuiSize = Gui::sideGui.getSize().x;

	// Si on est en contact ou qu'on a dépassé un des bords de l'écran, on inverse le déplacement
	if ((future_pos.x + myradius) >= (WIDTH-sideGuiSize))
    {
        direction.x = -direction.x;
        future_pos.x = WIDTH-sideGuiSize - myradius;
    }
    else if (future_pos.x - myradius < 0)
    {
        direction.x = -direction.x;
        future_pos.x = myradius;
    }
	
    if (future_pos.y - myradius < 0)
    {
        direction.y = -direction.y;
        future_pos.y = myradius;
    }
    else if ((future_pos.y + myradius) >= HEIGHT)
    {
        direction.y = -direction.y;
        future_pos.y = HEIGHT - myradius;
    }

    shape->setPosition(future_pos);
}
