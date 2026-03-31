#include "swarm.hpp"
#include <random>
#include <vector> 


const float PROTECTED_RANGE = 15.0f;
const float VISUAL_RANGE = 250.0f;

Swarm::Swarm(int nboids, int width, int height) : m_width(width), m_height(height) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis_pos_x(1, width);
    std::uniform_real_distribution<> dis_pos_y(1, height);
    std::uniform_real_distribution<> dis_vel(-5.0f, 5.0f);

    for (int i = 0; i < nboids; ++i) {
        float x = dis_pos_x(gen);
        float y = dis_pos_y(gen);
        float vx = dis_vel(gen);
        float vy = dis_vel(gen);
      
      m_agents.emplace_back(x, y, vx, vy);
    }
}

int Swarm::getSize() const {
    return m_agents.size();
}

Agent Swarm::getAgent(int index) {
    return m_agents[index];
}

void Swarm::addAgent(const Agent& agent) {
    m_agents.push_back(agent);
}

void Swarm::update() {
    std::vector<Agent> neighbours;

    for (auto& agent : m_agents) {
        for (auto& other : m_agents) {
            if (&agent == &other) continue;

            float vx = agent.getVx() - other.getVx();
            float vy = agent.getVy() - other.getVy();
            float dist = std::sqrt(vx*vx + vy*vy);
            
            if (dist < VISUAL_RANGE) {
                neighbours.push_back(other);
            }
        }
        
        agent.update(neighbours, m_width, m_height);
        neighbours.clear();
    }
}