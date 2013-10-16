#include "PhysObject.hpp"

PhysObject::PhysObject(float x,float y) : direction(x,y)
{
}

PhysObject::~PhysObject()
{
}

void PhysObject::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(*shape,states);
}

