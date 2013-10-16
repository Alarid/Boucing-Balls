#include "PhysEngine.hpp"
#include "PhysObject.hpp"
#include "Gui.hpp"

std::vector<PhysObject*> PhysEngine::objects;

void PhysEngine::nextStep(float time)
{
    const unsigned int _size = objects.size();

    for(int i=0;i<_size;++i)
        objects[i]->move(time);

    for (unsigned int i=0; i<_size; ++i)
    {
        PhysObject& _1 = *objects[i];

        for (unsigned int j=i+1; j<_size; ++j)
        {
            PhysObject& _2 = *objects[j];

            if (_1.isCollided(_2))
            {
                /*
                const Vector2f centerBalloonSource(balloonSource.getPosition());
                const Vector2f centerBalloonDest(balloonDest.getPosition());

                const Vector2f collisionPoint(((centerBalloonSource * balloonDest.getRadius()) + (centerBalloonDest * balloonSource.getRadius())) / (balloonSource.getRadius() + balloonDest.getRadius()));
                cout << Angle(centerBalloonSource, collisionPoint) << endl;
                */

                _1.direction = -_1.direction;
                _2.direction = -_2.direction;
            }
        }
        _1.draw(Gui::window);
    }
}

void PhysEngine::clear()
{
    for(PhysObject* obj : objects)
        delete obj;
}

int PhysEngine::findAndRemove(float x,float y)
{
    int find = 0;
    auto it = objects.begin();
    while (it != objects.end())
    {
        // Si c'est le cas, on l'enlève
        if ((*it)->isCollided(x,y))
        {
            delete *it;
            it = objects.erase(it);
            --find;
        }
        else
            ++it;
    }
    return find;
}

void PhysEngine::add(PhysObject* obj)
{
    objects.emplace_back(obj);
}

bool PhysEngine::isCollided(PhysObject* obj)
{
    bool find = false;
    const unsigned int _size = objects.size();
    for(unsigned int i=0;i<_size;++i)
    {
        if (objects[i]->isCollided(*obj))
        {
            find = true;
            break;
        }
    }
    return find;
}

