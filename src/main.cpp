#include <iostream>
#include <vector>
#include "swarm.hpp"
#include "SFML/Graphics.hpp"

#define WIDTH 800
#define HEIGHT 600
#define CIRCLE_RADIUS 5.f

int main() {
    Swarm swarm(10, WIDTH, HEIGHT);
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

        // for (auto &agent : swarm.getAgents()) {
        //     agent.update(swarm.getAgents());
        // }

        window.clear();
        for (const auto &shape : shapes) {
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}