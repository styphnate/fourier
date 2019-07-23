#include "../inc/circle.h"

Circle::Circle(const float &radius, const double &x, const double &y) : sf::CircleShape(radius), prevRadius{radius} {
  this->setPosition(sf::Vector2f(x, y));
  setAttributes();
}

Circle::Circle(const Circle &other, const sf::RectangleShape &rotatingLine)
    : sf::CircleShape(other.getRadius() / 4), prevRadius{other.getRadius()} {
  updatePosition(rotatingLine);
  setAttributes();
}

void Circle::setAttributes() {
  this->setFillColor(sf::Color(255, 255, 255, 0));
  this->setOutlineThickness(1);
  this->setOutlineColor(sf::Color(255, 255, 255));
}

void Circle::updatePosition(const sf::RectangleShape &rotatingLine) {
  this->setPosition(sf::Vector2f(
      rotatingLine.getPosition().x + prevRadius * cos(rotatingLine.getRotation() * PI / 180.0) - this->getRadius(),
      rotatingLine.getPosition().y + prevRadius * sin(rotatingLine.getRotation() * PI / 180.0) - this->getRadius()));
}

void Circle::setPrevRadius(double &prevRad) { prevRadius = prevRad; }