#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>

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
    Clock clock;
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
    
    // Side gui
    Texture sideGui;
    if (!sideGui.loadFromFile("img/gui.png"))
    {
        cout << "Error loading img/gui.png" << endl;
    }
    sideGui.setSmooth(true);
    sideGui.setRepeated(true);
    Sprite sideGuiSpr;
    sideGuiSpr.setTexture(sideGui);
    sideGuiSpr.setTextureRect(IntRect(0, 0, sideGui.getSize().x, HEIGHT));
    sideGuiSpr.setPosition(WIDTH-sideGui.getSize().x, 0);

    // GUI font
    Font font;
    if (!font.loadFromFile("fonts/gui.ttf"))
    {
        cout << "Error loading fonts/gui.ttf" << endl;
    }
    Text guiCountdown;
    guiCountdown.setFont(font);
    guiCountdown.setString("30");
    guiCountdown.setCharacterSize(50);
    guiCountdown.setColor(Color::Black);
    guiCountdown.setPosition(WIDTH - sideGui.getSize().x/2 - 20, 50);

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
        balloons.push_back(Balloon(posX, posY, size, sideGui.getSize().x));
    }

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

        // Mise à jour du countdown
        int secs = (int)clock.getElapsedTime().asSeconds();
        if (secs <= COUNTDOWN)
        {
            ostringstream oss;
            oss << COUNTDOWN - secs;
            guiCountdown.setString(oss.str());
        }

        // GUI
        window.draw(bg);
        window.draw(sideGuiSpr);
        window.draw(guiCountdown);

        // Déplacements
        for (auto& balloon: balloons)
            balloon.run();

        // Collisions
        checkCollisions();

        // Affichage
        for (auto& balloon: balloons)
            window.draw(balloon);


        window.display();
    }

    return 0;
}
