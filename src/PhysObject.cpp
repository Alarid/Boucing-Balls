#include "PhysObject.hpp"

PhysObject::PhysObject(float x,float y) : direction(x,y)
{
}

PhysObject::~PhysObject()
{
}

void PhysObject::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    sf::VertexArray lines(sf::LinesStrip, 4);
    lines[0].position = shape->getPosition();
    lines[1].position = shape->getPosition() + 8.f*direction;
    lines[2].position = shape->getPosition();
    lines[3].position = shape->getPosition() + 8.f*direction;

    target.draw(*shape,states);
    target.draw(lines,states);
}

