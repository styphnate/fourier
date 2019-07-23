#include "define.h"
#include <SFML/Graphics.hpp>
#include <math.h>

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public sf::CircleShape {
public:
  Circle(const float &radius, const double &x, const double &y);
  Circle(const Circle &other, const sf::RectangleShape &rotatingLine);
  Circle(const Circle &other) = default;

  void setAttributes();

  void updatePosition(const sf::RectangleShape &rotatingLine);

  void setPrevRadius(double &prevRad);

private:
  double prevRadius;
};

#endif // CIRCLE_H