#include "circle.h"
#include "define.h"
#include "rotating_line.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

void render(sf::RenderWindow &window, std::vector<std::unique_ptr<sf::Shape>> &renderObjects) {
  for (auto &obj : renderObjects) {
    window.draw(*obj);
  }
}

void updateOutput(std::vector<std::unique_ptr<sf::Shape>> &output) {
  for (auto &point : output) {
    point->setPosition(point->getPosition().x + 1, point->getPosition().y);
  }
  output.erase(std::remove_if(std::begin(output), std::end(output),
                              [](const std::unique_ptr<sf::Shape> &point) { return point->getPosition().x > WIDTH; }),
               std::end(output));
}

void updatePositionAndRotation(std::vector<Circle> &circles, std::vector<RotatingLine> &rotatingLines, double &theta) {
  for (size_t i = 0; i < rotatingLines.size(); ++i) {
    uint32_t n = i * 2 + 1;
    rotatingLines.at(i).updateRotation(n, theta);
  }

  for (size_t i = 1; i < circles.size(); ++i) {
    circles.at(i).updatePosition(rotatingLines.at(i - 1));
  }

  for (size_t i = 1; i < rotatingLines.size(); ++i) {
    rotatingLines.at(i).updatePosition(rotatingLines.at(i - 1), circles.at(i - 1));
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fourier");
  window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - WIDTH / 2,
                                  sf::VideoMode::getDesktopMode().height / 2 - HEIGHT / 2));
  window.setFramerateLimit(60);

  double theta = 1.0;

  std::vector<Circle> circles;
  std::vector<RotatingLine> rotatingLines;
  std::vector<std::unique_ptr<sf::Shape>> output;

  // Create main circle
  circles.push_back(Circle(RADIUS_MAIN, WIDTH / 2 - WIDTH / 3 - RADIUS_MAIN, HEIGHT / 2 - RADIUS_MAIN));
  // Create main rotating line
  rotatingLines.push_back(RotatingLine(circles.at(0)));

  // Create as many circles as you want
  for (size_t i = 1; i < 4; ++i) {
    circles.push_back(Circle(circles.at(i - 1), rotatingLines.at(i - 1)));
    rotatingLines.push_back(RotatingLine(circles.at(i), circles.at(i - 1).getRadius()));
  }

  // Create connecting line
  std::unique_ptr<sf::RectangleShape> connectingLine =
      std::make_unique<sf::RectangleShape>(sf::Vector2f(RADIUS_MAIN, 1));
  connectingLine->setPosition(sf::Vector2f(
      circles.at(circles.size() - 1).getPosition().x + circles.at(circles.size() - 1).getRadius(), HEIGHT / 2));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        // Can add and remove circles dynamically
        if (event.key.code == sf::Keyboard::Left) {
          if (circles.size() > 1) {
            circles.pop_back();
            rotatingLines.pop_back();
          }
        }
        if (event.key.code == sf::Keyboard::Right) {
          circles.push_back(Circle(circles.at(circles.size() - 1), rotatingLines.at(rotatingLines.size() - 1)));
          rotatingLines.push_back(
              RotatingLine(circles.at(circles.size() - 1), circles.at(circles.size() - 2).getRadius()));
        }
      }
    }
    window.clear();

    updatePositionAndRotation(circles, rotatingLines, theta);

    connectingLine->setPosition(
        sf::Vector2f(rotatingLines.at(rotatingLines.size() - 1).getPosition().x +
                         circles.at(circles.size() - 1).getRadius() *
                             cos(rotatingLines.at(rotatingLines.size() - 1).getRotation() * PI / 180),
                     rotatingLines.at(rotatingLines.size() - 1).getPosition().y +
                         circles.at(circles.size() - 1).getRadius() *
                             sin(rotatingLines.at(rotatingLines.size() - 1).getRotation() * PI / 180)));
    // Sets length of connecting according to length between center and circle
    connectingLine->setSize(sf::Vector2f(WIDTH / 2 - connectingLine->getPosition().x, 1));

    // Handles drawing of graph
    std::unique_ptr<sf::Shape> tmpOutput = std::make_unique<sf::RectangleShape>(sf::Vector2f(1, 1));
    tmpOutput->setPosition(sf::Vector2f(WIDTH / 2, connectingLine->getPosition().y));
    output.push_back(std::move(tmpOutput));
    updateOutput(output);

    // Render objects
    for (const auto &circletmp : circles) {
      window.draw(circletmp);
    }
    for (const auto &rotatingLinetmp : rotatingLines) {
      window.draw(rotatingLinetmp);
    }
    window.draw(*connectingLine.get());

    // Render graph
    render(window, output);
    window.display();
  }

  return 0;
}