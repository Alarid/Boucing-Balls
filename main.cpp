#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "const.hpp"
#include "Balloon.hpp"

using namespace std;
using namespace sf;

vector<Balloon> balloons;

float rand_FloatRange(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

void checkCollisions()
{
    vector<Balloon>::iterator it = balloons.begin();
    while (it != balloons.end())
    {
        vector<Balloon>::iterator it2 = balloons.begin();
        while (it2 != balloons.end())
        {
            if ((it->getId() != it2->getId()) && it2->isCollided(*it))
            {
                Vector2f firstDir = it->getDirection();
                Vector2f secondDir = it2->getDirection();

                int newVelX = (firstDir.x * (it->getRadius() - it2->getRadius()) + (2 * it2->getRadius() * secondDir.x)) / (it->getRadius() + it2->getRadius());
                int newVelY = (firstDir.y * (it->getRadius() - it2->getRadius()) + (2 * it2->getRadius() * secondDir.y)) / (it->getRadius() + it2->getRadius());
                int newVelX2 = (secondDir.x * (it2->getRadius() - it->getRadius()) + (2 * it->getRadius() * firstDir.x)) / (it2->getRadius() + it->getRadius());
                int newVelY2 = (secondDir.y * (it2->getRadius() - it->getRadius()) + (2 * it->getRadius() * firstDir.y)) / (it2->getRadius() + it->getRadius());

                it->setDirection(Vector2f(newVelX, newVelY));
                it->move(it->getDirection());
                it2->setDirection(Vector2f(newVelX2, newVelY2));
                it2->move(it2->getDirection());
            }

            it2++;
        }
        it++;
    }
}

int main()
{
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Balloons");
    srand(time(0));

    // Initialisation des ballons
    for (int i=1; i<=NB_BALLOONS; i++)
    {
        float size = 0, posX = 0, posY = 0;
        bool found;

        // On regénère une position aléatoire tant qu'on tombe sur un ballon déjà à cet endroit
        do
        {
            found = false;
            size = rand_FloatRange(30, MAX_SIZE);
            posX = rand_FloatRange(1, WIDTH-size*2);
            posY = rand_FloatRange(1, HEIGHT-size*2);

            vector<Balloon>::iterator it = balloons.begin();
            while (it != balloons.end())
            {
                if (it->isCollided(posX, posY, size))
                {
                    found = true;
                    break;
                }
                else
                    it++;
            }
        } while (found && balloons.size() > 0);

        // On créé le ballon
        balloons.push_back(Balloon(posX, posY, size, i));
    }


    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des évènements
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                // Clic gauche de la souris
                if (event.mouseButton.button == Mouse::Left)
                {
                    // On regarde si un ballon à été cliqué
                    vector<Balloon>::iterator it = balloons.begin();
                    while (it != balloons.end())
                    {
                        // Si c'est le cas, on l'enlève
                        if (it->isClicked(event.mouseButton.x, event.mouseButton.y))
                            it = balloons.erase(it);
                        else
                            ++it;
                    }
                }
            }
        }

        // Déplacements
        for (vector<Balloon>::iterator it = balloons.begin(); it != balloons.end(); ++it)
            it->run();

        // Collisions
        checkCollisions();

        // Affichage
        window.clear();
        for (vector<Balloon>::iterator it = balloons.begin(); it != balloons.end(); ++it)
            window.draw(*it);

        window.display();
    }

    return 0;
}
