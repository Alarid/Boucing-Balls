#ifndef PHYSENGINE_HPP
#define PHYSENGINE_HPP

#include <vector>

class PhysObject;

class PhysEngine
{
    public:
        PhysEngine() = delete; //not possible to create it

        static void nextStep(float time_sec);
        static int findAndRemove(float posx,float posy);
        static void add(PhysObject* obj);
        static bool isCollided(PhysObject* obj);
    private:
        static std::vector<PhysObject*> objects;

};


#endif
