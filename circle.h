#include <SFML/Graphics.hpp>
#include "define.h"
#include <iostream>

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public sf::CircleShape
{
public:
  Circle(const float &radius, const double &x, const double &y) : sf::CircleShape(radius), prevRadius{radius}
  {
    this->setPosition(sf::Vector2f(x, y));
    setAttributes();
  }
  Circle(const Circle &other, int i /* To make this not be a copy constructor */) : sf::CircleShape(other.getRadius() / 4), prevRadius{other.getRadius()}
  {
    (void)i;
    std::cout << "HERE" << std::endl;
    this->setPosition(sf::Vector2f(other.getPosition().x + other.getRadius(), other.getPosition().y));
    setAttributes();
  }

  void setAttributes()
  {
    this->setFillColor(sf::Color(255, 255, 255, 0));
    this->setOutlineThickness(1);
    this->setOutlineColor(sf::Color(255, 255, 255));
  }
  
  void updatePosition(const sf::RectangleShape &rotatingLine)
  {
    this->setPosition(sf::Vector2f(rotatingLine.getPosition().x + prevRadius * cos(rotatingLine.getRotation() * PI / 180.0) - this->getRadius(), rotatingLine.getPosition().y + prevRadius * sin(rotatingLine.getRotation() * PI / 180.0) - this->getRadius()));
  }

  void setPrevRadius(double &prevRad) { prevRadius = prevRad; }

private:
  double prevRadius;
};

#endif // CIRCLE_H