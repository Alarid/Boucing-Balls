#include "Balloon.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Balloon::Balloon (float posx,float posy,float radius,int sideGuiSize)
{
	setRadius(radius);
	setFillColor(sf::Color::Green);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(3);
	setPosition(posx, posy);

	this->sideGuiSize = sideGuiSize;

	int dirx = rand() & 1;
	int diry = rand() & 1;

	direction.x = dirx ? SPEED : -SPEED;
	direction.y = diry ? SPEED : -SPEED;
}

bool Balloon::isClicked(int posX, int posY) const
{
	Vector2f mypos = getPosition();
	float myradius = getRadius();
	return ((posX > mypos.x) //TODO , ici la hit box est carée
            && (posX < mypos.x+myradius*2)
            && (posY > mypos.y)
            && (posY < mypos.y+myradius*2));
}

bool Balloon::isCollided(const Balloon& other) const
{
    const Vector2f& other_pos = other.getPosition();
    return isCollided(other_pos.x,other_pos.y,other.getRadius());
}

bool Balloon::isCollided(float posx, float posy, float radius)const
{
	const Vector2f& pos = getPosition();
	float xd = pos.x - posx;
	float yd = pos.y - posy;

    return sqrt(xd*xd + yd*yd) <= getRadius() + radius;
}

void Balloon::run(const float time)
{
	Vector2f mypos = getPosition();
	float myradius = getRadius() * 2;

	// Si on est en contact ou qu'on a dépassé un des bords de l'écran, on inverse le déplacement
	if ((mypos.x + myradius) >= (WIDTH-sideGuiSize))
    {
        direction.x = -direction.x;
        setPosition(Vector2f(WIDTH-myradius-sideGuiSize, getPosition().y));
    }
    else if (mypos.x <= 0)
    {
        direction.x = -direction.x;
        setPosition(Vector2f(0, getPosition().y));
    }
	else if (mypos.y <= 0)
    {
        direction.y = -direction.y;
        setPosition(Vector2f(getPosition().x, 0));
    }
    else if ((mypos.y + myradius) >= HEIGHT)
    {
        direction.y = -direction.y;
        setPosition(Vector2f(getPosition().x, HEIGHT-myradius));
    }

    move(direction.x*time*METTER_PER_SECOND, direction.y*time*METTER_PER_SECOND);
}

void Balloon::invertDirection()
{
	direction.x = -direction.x;
	direction.y = -direction.y;
}

const sf::Vector2f& Balloon::getDirection() const
{
    return this->direction;
};
