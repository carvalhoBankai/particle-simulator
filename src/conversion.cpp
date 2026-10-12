#include "conversion.hpp"

std::vector<Point> toPoints(const std::vector<Particle>& particles) {
    std::vector<Point> points;

    for(const auto& particle : particles) {
        
        sf::Color color = sf::Color::Green;
        if (particle.getType() == ParticleType::Red) {
            color = sf::Color::Red;
        } else if (particle.getType() == ParticleType::Yellow) {
            color = sf::Color::Yellow;
        } 
        points.push_back({particle.getPosition(), color});
    }

    return points;
}