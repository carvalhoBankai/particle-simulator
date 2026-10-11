#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "particle.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>


/**
 * The model as the following paramèters
 * interRadius : radius of interaction between the particles.
 * beta : parameter controlling the repulsion area.
 * forceFactor : force intensity factor applied on all particles.
 * frictionHalfLife : fractional velocity life, in seconds.
 * toroidal : true, the model is toroidal, otherwise, not toroidal.
 */


class ParticleSystem {

    public:
        // Number of particle types
        static constexpr std::size_t NUM_TYPES = 3;
        using Matrix = std::array<std::array<double, NUM_TYPES>, NUM_TYPES>;

        struct Params {
            double interRadius      = 100.0;  // radius of interaction between the particles.
            double beta             = 0.3;    // parameter controlling the repulsion area.
            double forceFactor      = 10.0;   // intensité globale des forces
            double frictionHalfLife = 0.04;   // half life of the vitesse taut, en secondes
            bool   toroidal         = false;  // toroidal worl or a wordl with walls
        };

        ParticleSystem(std::vector<Particle> particles, const Vec2 worldDim, bool toroidal);

        const std::vector<Particle>& getParticles() const;
        void addParticle(Particle particle);
        void setParticles(std::vector<Particle> newParticles);
        void update(float dt);

        // get a random iteration matrix, log the seed, so the config can be reutilized
        std::uint32_t randomizeMatrix(std::uint32_t seed = std::random_device{}());
        const Matrix& getMatrix() const;

    private:
        std::vector<Particle> particles;
        const Vec2 worldDim;
        bool toroidal;

        Matrix matrix{};
        // parameters of the system
        Params params;

        // force function, x = dist(p1, p2) / interRadius, a matrix iteration value between p1 and p2
        // a value is the interval [-1; 1]
        double forceMagnitude(double x, double a) const;
        // get the particles iteration rules
        double rule(ParticleType type1, ParticleType type2) const;
        // get the shortest path between two particiles in a toroidal world
        Vec2 wrapDelta(Vec2 d) const;

        bool isToroidal() const;
};

#endif