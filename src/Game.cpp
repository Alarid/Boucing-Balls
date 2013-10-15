#include "Game.hpp"

using namespace std;
using namespace sf;

std::vector<Balloon> Game::balloons;
Clock Game::clock;

/**
 * Méthode principale du jeu
 */
bool Game::run()
{
	rand_init();

//    Gui::init();
    Gui::window.setFramerateLimit(60);

    initBalloons();

    // Boucle principale
    while (Gui::window.isOpen())
    {
    	// Gestion des évènements
        Event event;
        while (Gui::window.pollEvent(event))
        {
            if ((event.type == Event::Closed) or (event.type == Event::KeyPressed and event.key.code == Keyboard::Escape))
                Gui::window.close();

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

        draw();
    }

    return true;
}

/**
 * Initialisation des ballons
 */
bool Game::initBalloons()
{
	for (int i=1; i<=NB_BALLOONS; i++)
    {
        float size,posX,posY;
        bool found;

        // On regénère une position aléatoire tant qu'on tombe sur un ballon déjà à cet endroit
        do
        {
            found = false;
            size = random(30.f, MAX_SIZE);
            posX = random(1.f, WIDTH-size);
            posY = random(1.f, HEIGHT-size);

            auto it = balloons.begin();
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
        balloons.emplace_back(posX, posY, size, Gui::sideGui.getSize().x);
    }

    return true;
}

/**
 * Mise à jour des ballons
 */
bool Game::updateBalloons(const float time)
{
    // Collisions

	// Déplacements
    for (auto& balloon: balloons)
    {
        balloon.run(time);
    }

    checkCollisions();

    return true;
}

/**
 * Vérification des collisions entres les ballons
 */
bool Game::checkCollisions()
{
	const unsigned int _size = balloons.size();

    for (unsigned int i = 0; i < _size; ++i)
    {
        Balloon& balloonSource = balloons[i];

        for (unsigned int j = i+1; j < _size; ++j)
        {
            Balloon& balloonDest = balloons[j];

            if (balloonDest.isCollided(balloonSource))
            {
                const Vector2f centerBalloonSource(balloonSource.getPosition());
                const Vector2f centerBalloonDest(balloonDest.getPosition());

                /*const Vector2f collisionPoint(
                    ((centerBalloonSource.x * balloonDest.getRadius()) + (centerBalloonDest.x * balloonSource.getRadius())) / (balloonSource.getRadius() + balloonDest.getRadius()),
                    ((centerBalloonSource.y * balloonDest.getRadius()) + (centerBalloonDest.y * balloonSource.getRadius())) / (balloonSource.getRadius() + balloonDest.getRadius())
                );*/

                const Vector2f collisionPoint(((centerBalloonSource * balloonDest.getRadius()) + (centerBalloonDest * balloonSource.getRadius())) / (balloonSource.getRadius() + balloonDest.getRadius()));
                cout << Angle(centerBalloonSource, collisionPoint) << endl;


                balloonSource.setDirection(-balloonSource.getDirection());
                balloonDest.setDirection(-balloonDest.getDirection());
            }
        }
        Gui::window.draw(balloonSource);
    }
}

/**
 * Affichage du jeu
 */
bool Game::draw()
{
    Gui::window.clear();
    float time = clock.restart().asSeconds();

    // Mise à jour et affichage de la GUI
//    Gui::update((int)time);
//    Gui::draw();

    // Mise à jour des ballons
    updateBalloons(time);

    Gui::window.display();

    return true;
}
