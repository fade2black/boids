#include <iostream>
#include <vector>
#include "swarm.hpp"
#include "SFML/Graphics.hpp"

#define WIDTH 800
#define HEIGHT 600
#define CIRCLE_RADIUS 3.f
#define SWARM_SIZE 10

int main() {
    Swarm swarm(SWARM_SIZE, WIDTH, HEIGHT);
    std::vector<sf::CircleShape> shapes;
    
    for (int i = 0; i < swarm.getSize(); ++i) {
        Agent agent = swarm.getAgent(i);
        std::cout << "Agent " << i << ": Location(" << agent.getLocation().getX() << ", " << agent.getLocation().getY() 
                  << ") Velocity(" << agent.getVelocity().getX() << ", " << agent.getVelocity().getY()   << ")\n";

        sf::CircleShape shape(CIRCLE_RADIUS);
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(sf::Vector2f(agent.getLocation().getX(), agent.getLocation().getY()));
        shapes.push_back(shape);
    }


    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids!");
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        swarm.update();
    
        for(int i = 0; i < swarm.getSize(); ++i) {
            Agent agent = swarm.getAgent(i);
            shapes[i].setPosition(sf::Vector2f(agent.getLocation().getX(), agent.getLocation().getY()));
        }

        window.clear();
        for (const auto &shape : shapes) {
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}