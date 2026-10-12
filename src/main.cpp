#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <iostream>
#include <optional>

#include "render.hpp"
#include "particle.hpp"
#include "vec2.hpp"
#include "point.hpp"
#include "particle_system.hpp"
#include "conversion.hpp"

constexpr unsigned WINDOW_SIZE = 800;
constexpr float WORLD_SIZE = static_cast<float>(WINDOW_SIZE);

const float POINT_RADIUS = 2.0f;
const float FIXED_DT = 1.f / 60.f;
const float MAX_FRAME_TIME = 0.1f;

const int nRed = 500;
const int nGreen = 500;
const int nYellow = 400;
const int nPart = nRed + nGreen + nYellow;

float accumulator = 0.f;

// Create nPart particles with random positions throughout the world.
std::vector<Particle> makeParticles(std::mt19937& gen)
{
    std::uniform_real_distribution<float> posDist(-WORLD_SIZE / 2.f, WORLD_SIZE / 2.f);

    std::vector<ParticleType> types;
    types.reserve(nPart);
    types.insert(types.end(), nRed, ParticleType::Red);
    types.insert(types.end(), nGreen, ParticleType::Green);
    types.insert(types.end(), nYellow, ParticleType::Yellow);

    // shuffle the particles
    std::shuffle(types.begin(), types.end(), gen);

    std::vector<Particle> particles;
    particles.reserve(nPart);

    for (ParticleType type : types)
    {
        Vec2 position{posDist(gen), posDist(gen)};
        particles.emplace_back(position, type);
    }

    return particles;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    ParticleSystem particleSystem(makeParticles(gen),
                   Vec2{WORLD_SIZE,
                   WORLD_SIZE},
                   true);

    // randomize the interaction matrix.
    particleSystem.randomizeMatrix();

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
        "Particle Simulation"
    );

    Render render(window, POINT_RADIUS);

    sf::Clock simulationClock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float elapsed = simulationClock.restart().asSeconds();
        elapsed = std::min(elapsed, MAX_FRAME_TIME);
        accumulator += elapsed;

        while (accumulator >= FIXED_DT)
        {
            particleSystem.update(FIXED_DT);
            accumulator -= FIXED_DT;
        }

        auto points = toPoints(particleSystem.getParticles());

        window.clear();

        render.draw(points);

        window.display();
    }
}