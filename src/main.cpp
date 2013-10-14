#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "defines.hpp"
#include "random.hpp"
#include "Balloon.hpp"

using namespace std;
using namespace sf;

vector<Balloon> balloons;

void checkCollisions()
{
    const unsigned int _size = balloons.size();

    for (unsigned int i = 0; i < _size; ++i)
    {
        Balloon& balloonSource = balloons[i];

        for (unsigned int j = 0; j < _size; ++j)
        {
            Balloon& balloonDest = balloons[j];

            if (i == j) continue;

            if (balloonDest.isCollided(balloonSource))
            {
//                Vector2f firstDir = balloonSource.getDirection();
//                Vector2f secondDir = balloonDest.getDirection();
//
//                int newVelX = (firstDir.x * (balloonSource.getRadius() - balloonDest.getRadius()) + (2 * balloonDest.getRadius() * secondDir.x)) / (balloonSource.getRadius() + balloonDest.getRadius());
//                int newVelY = (firstDir.y * (balloonSource.getRadius() - balloonDest.getRadius()) + (2 * balloonDest.getRadius() * secondDir.y)) / (balloonSource.getRadius() + balloonDest.getRadius());
//                int newVelX2 = (secondDir.x * (balloonDest.getRadius() - balloonSource.getRadius()) + (2 * balloonSource.getRadius() * firstDir.x)) / (balloonDest.getRadius() + balloonSource.getRadius());
//                int newVelY2 = (secondDir.y * (balloonDest.getRadius() - balloonSource.getRadius()) + (2 * balloonSource.getRadius() * firstDir.y)) / (balloonDest.getRadius() + balloonSource.getRadius());
//
//                balloonSource.setDirection(Vector2f(newVelX, newVelY));
//                balloonSource.move(balloonSource.getDirectionX()*2, balloonSource.getDirectionY()*2);
//                balloonDest.setDirection(Vector2f(newVelX2, newVelY2));
//                balloonDest.move(balloonDest.getDirectionX()*2, balloonDest.getDirectionY()*2);

                balloonSource.setDirection(Vector2f(-balloonSource.getDirection().x, -balloonSource.getDirection().y));
                balloonDest.setDirection(Vector2f(-balloonDest.getDirection().x, -balloonDest.getDirection().y));
                balloonSource.move(balloonSource.getDirection());
                balloonDest.move(balloonDest.getDirection());
            }
        }
    }
}

int main()
{
    RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Balloons");
    window.setFramerateLimit(60);
    rand_init();

    // Background GUI
    Texture texture;
    if (!texture.loadFromFile("img/back.png"))
    {
        cout << "Error loading img/back.png" << endl;
    }
    texture.setSmooth(true);
    texture.setRepeated(true);
    Sprite bg;
    bg.setTexture(texture);
    bg.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));
    cout << "test" << endl;

    // Initialisation des ballons
    for (int i=1; i<=NB_BALLOONS; i++)
    {
        float size,posX,posY;
        bool found;

        // On regénère une position aléatoire tant qu'on tombe sur un ballon déjà à cet endroit
        do
        {
            found = false;
            size = random(30.f, MAX_SIZE);
            posX = random(1.f, WIDTH-size*2);
            posY = random(1.f, HEIGHT-size*2);

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

    sf::Clock clock;
    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des évènements
        float elapsedTime = clock.getElapsedTime().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == Event::Closed) or (event.type == Event::KeyPressed and event.key.code == Keyboard::Escape))
                window.close();

            if (event.type == Event::MouseButtonPressed and event.mouseButton.button == Mouse::Left)
            {
                // On regarde si un ballon à été cliqué
                auto it = balloons.begin();
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

        window.clear();

        // GUI
        window.draw(bg);

        // Déplacements
        for (auto& balloon: balloons)
            balloon.run();

        // Collisions
        checkCollisions();

        // Affichage
        window.clear();
        for (auto& balloon: balloons)
            window.draw(balloon);


        window.display();
    }

    return 0;
}
