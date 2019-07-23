#include "define.h"
#include <SFML/Graphics.hpp>
#include <math.h>

#ifndef ROTATING_LINE_H
#define ROTATING_LINE_H

class RotatingLine : public sf::RectangleShape {
public:
  RotatingLine(const sf::CircleShape &circle, const double &prevRadius);
  void updatePosition(const RotatingLine &prevRotatingLine, const sf::CircleShape &prevCircle);
  RotatingLine(const RotatingLine &other) = default;

  void updateRotation(const uint32_t &n, const double &theta);

private:
  const double prevRadius;
};

#endif // ROTATING_LINE_H