#include "Geometry.hpp"

/**
\brief Angle (en degrés) de l'axe formé par 2 points
\param x1 : Abcisse du premier point
\param y1 : Ordonnée du premier point
\param x2 : Abcisse du second point
\param y2 : Ordonnée du second point
\return Angle de l'axe formé par 2 points
*/
inline float Geometry::Angle(const float x1, const float y1, const float x2, const float y2)
{
    float x = x1 - x2;
    float y = y1 - y2;

    if (y == 0.f)
    {
        if (x >= 0.f)
            return 0.f;
        else
            return 180.f;
    }

    if (y >= 0.f)
    {
        return ( ToDeg( std::atan(y/x) ) + 270.f );
    }
    else
    {
        return ( ToDeg( std::atan(y/x) ) + 90.f );
    }
}

/**
\brief Angle (en degrés) de l'axe formé par 2 points
\param p1 Premier point
\param p2 Second point
\return Angle de l'axe formé par 2 points
*/
inline float Geometry::Angle(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return Angle(p1.x, p1.y, p2.x, p2.y);
}

