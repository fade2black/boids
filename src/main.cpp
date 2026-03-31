#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "swarm.hpp"
#include "SFML/Graphics.hpp"

#define CIRCLE_RADIUS 7.f
#define SWARM_SIZE 10

#include <vector>

const int WIDTH = 1000;
const int HEIGHT = 800;

int main() {
    Swarm swarm(SWARM_SIZE, WIDTH, HEIGHT);
    std::vector<sf::CircleShape> shapes;
    
    // Initialize shapes for each agent
    for (int i = 0; i < swarm.getSize(); ++i) {
        Agent agent = swarm.getAgent(i);
        sf::CircleShape shape(CIRCLE_RADIUS, 3);

        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(sf::Vector2f(agent.getX(), agent.getY()));
        shapes.push_back(shape);
    }

    // Create the window
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids!");
    // Start simulation loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        swarm.update();        
    
        for(int i = 0; i < swarm.getSize(); ++i)  {
            Agent agent = swarm.getAgent(i);

            sf::Angle angle = sf::radians(std::atan2(agent.getVy(), agent.getVx()));
            shapes[i].setRotation(angle + sf::radians(M_PI_2)); // Rotate the shape to point in the direction of velocity
            shapes[i].setPosition(sf::Vector2f(agent.getX(), agent.getY()));
        }

        window.clear();
        for (const auto &shape : shapes) {
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}