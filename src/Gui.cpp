#include "Gui.hpp"

using namespace std;
using namespace sf;

Gui::window = RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Balloons");

/**
 * Initialisation de la GUI
 */
bool Gui::init()
{
	// Background GUI
    if (!bg.loadFromFile("img/back.png"))
    {
        cout << "Error loading img/back.png" << endl;
        return false;
    }
    bg.setSmooth(true);
    bg.setRepeated(true);
    bgSpr.setTexture(bg);
    bgSpr.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));
    
    // Side gui
    if (!sideGui.loadFromFile("img/gui.png"))
    {
        cout << "Error loading img/gui.png" << endl;
        return false;
    }
    sideGui.setSmooth(true);
    sideGui.setRepeated(true);
    sideGuiSpr.setTexture(sideGui);
    sideGuiSpr.setTextureRect(IntRect(0, 0, sideGui.getSize().x, HEIGHT));
    sideGuiSpr.setPosition(WIDTH-sideGui.getSize().x, 0);

    // GUI font
    if (!guiFont.loadFromFile("fonts/gui.ttf"))
    {
        cout << "Error loading fonts/gui.ttf" << endl;
        return false;
    }
    guiCountdown.setFont(guiFont);
    guiCountdown.setString("30");
    guiCountdown.setCharacterSize(50);
    guiCountdown.setColor(Color::Black);
    guiCountdown.setPosition(WIDTH - sideGui.getSize().x/2 - 20, 50);

    return true;
}

/**
 * Affichage de la GUI
 */
bool Gui::draw()
{
	window.clear();

    window.draw(bgSpr);
    window.draw(sideGuiSpr);
    window.draw(guiCountdown);

    window.display();

    return true;
}

/**
 * Mise à jour de la GUI
 */
bool Gui::update(const int secs)
{
	if (secs <= COUNTDOWN)
    {
        ostringstream oss;
        oss << COUNTDOWN - secs;
        guiCountdown.setString(oss.str());
    }

    return true;
}