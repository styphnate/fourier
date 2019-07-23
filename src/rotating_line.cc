#include "../inc/rotating_line.h"

RotatingLine::RotatingLine(const sf::CircleShape &circle, const double &prevRadius = 0)
    : sf::RectangleShape(sf::Vector2f(circle.getRadius(), 1)), prevRadius{prevRadius} {
  this->setPosition(sf::Vector2f(circle.getPosition().x + circle.getRadius() + prevRadius,
                                 circle.getPosition().y + circle.getRadius()));
}

void RotatingLine::updatePosition(const RotatingLine &prevRotatingLine, const sf::CircleShape &prevCircle) {
  this->setPosition(
      prevCircle.getPosition().x + prevRadius + prevRadius * cos(prevRotatingLine.getRotation() * PI / 180),
      prevCircle.getPosition().y + prevRadius + prevRadius * sin(prevRotatingLine.getRotation() * PI / 180.0));
}

void RotatingLine::updateRotation(const uint32_t &n, const double &theta) {
  this->rotate(n * theta);
  // this->setRotation(((4 * cos(n * theta)) / n * PI) + ((4 * sin(n * theta)) / n * PI));
}