#include "PhysObject.hpp"

PhysObject::PhysObject(float x,float y) : direction(x,y)
{
}

PhysObject::~PhysObject()
{
}

void PhysObject::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    sf::VertexArray lines(sf::Lines, 2);
    lines[0].position = shape->getPosition();
    lines[0].color = sf::Color::Red;

    lines[1].position = shape->getPosition() + 8.f*direction;
    lines[1].color = sf::Color::Blue;

    target.draw(*shape,states);
    target.draw(lines,states);
}

