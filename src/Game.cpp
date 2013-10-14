#include "Game.hpp"

using namespace std;
using namespace sf;

/**
 * Méthode principale du jeu
 */
bool Game::run()
{
	rand_init();

    Gui::init();
    Gui::window.setFramerateLimit(60);

    // Boucle principale
    while (Gui::window.isOpen())
    {
    	// Gestion des évènements
        float elapsedTime = clock.getElapsedTime().asSeconds();
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

            draw();
        }
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
        balloons.push_back(Balloon(posX, posY, size, Gui::sideGui.getSize().x));
    }

    return true;
}

/**
 * Mise à jour des ballons
 */
bool Game::updateBalloons()
{
	// Déplacements
    for (auto& balloon: balloons)
        balloon.run();

    // Collisions
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

/**
 * Affichage du jeu
 */
bool Game::draw()
{
	// Mise à jour et affichage de la GUI
	int secs = (int)clock.getElapsedTime().asSeconds();
    Gui::update(secs);
    Gui::draw();

    // Mise à jour des ballons
    updateBalloons();

    // Affichage des ballons
    for (auto& balloon: balloons)
        Gui::window.draw(balloon);

    return true;
}