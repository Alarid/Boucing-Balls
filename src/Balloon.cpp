#include "Balloon.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Balloon::Balloon (float posx,float posy,float radius,int id)
{
	setRadius(radius);
	setFillColor(sf::Color::Green);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(3);
	setPosition(posx, posy);

	int dirx = rand() & 1;
	int diry = rand() & 1;
	direction.x = dirx ? SPEED : -SPEED;
	direction.y = diry ? SPEED : -SPEED;
}

bool Balloon::isClicked(int posX, int posY) const
{
	Vector2f mypos = getPosition();
	float myradius = getRadius();
	return ((posX > mypos.x) //TODO , iici la hit box est carée
            && (posX < mypos.x+myradius*2)
            && (posY > mypos.y)
            && (posY < mypos.y+myradius*2));
}

bool Balloon::isCollided(const Balloon& other) const
{
	const Vector2f& other_pos = other.getPosition();
	return isCollided(other_pos.x, other_pos.y, other.getRadius());
}

bool Balloon::isCollided(float posx,float posy,float radius) const
{
	const Vector2f& mypos = getPosition();
	float myradius = getRadius();
	if  ((posx >= mypos.x && posx <= (mypos.x + myradius*2)) ||
		((posx + radius*2) >= mypos.x && (posx + radius*2) <= (mypos.x + myradius*2)) ||
		(posy > mypos.y && posy <= (mypos.y + myradius*2)) ||
		((posy + radius*2) >= mypos.y && (posy + radius*2) <= (mypos.y + myradius*2)))
    {
        Vector2f myCenter = Vector2f(mypos.x+myradius, mypos.y+myradius);
        Vector2f otherCenter = Vector2f(posx+radius, posy+radius);
        float distance = sqrt(
            ((myCenter.x - otherCenter.x) * (myCenter.x - otherCenter.x)) +
            ((myCenter.y - otherCenter.y) * (myCenter.y - otherCenter.y))
        );
        if (distance <= myradius + radius) return true;
    }

    return false;
}

void Balloon::run()
{
	Vector2f mypos = getPosition();
	float myradius = getRadius() * 2;

	// Si on est en contact ou qu'on a dépassé un des bords de l'écran, on inverse le déplacement
	if ((mypos.x + myradius) >= WIDTH)
    {
        direction.x = -direction.x;
        setPosition(Vector2f(WIDTH-myradius, getPosition().y));
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

    direction.x = direction.x;
    direction.y = direction.y;
	move(direction);
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
