#include "particle_system.hpp"

#include <cmath>
#include <utility>

ParticleSystem::ParticleSystem(std::vector<Particle> initialParticles,
                               const Vec2 dim, bool toroidal) :
                               particles(std::move(initialParticles)), 
                               worldDim(dim), toroidal(toroidal)
                                                 
{
    // default matrix :  each type of particle atracts itself, no iteration with other types.
    for (std::size_t i = 0; i < NUM_TYPES; ++i)
    {
        matrix[i][i] = 1.0;
    }
}

const std::vector<Particle> &ParticleSystem::getParticles() const
{
    return particles;
}

void ParticleSystem::addParticle(Particle particle)
{
    particles.push_back(std::move(particle));
}

void ParticleSystem::setParticles(std::vector<Particle> newParticles)
{
    particles = std::move(newParticles);
}

const ParticleSystem::Matrix &ParticleSystem::getMatrix() const
{
    return matrix;
}

bool ParticleSystem::isToroidal() const 
{
    return toroidal;
}

std::uint32_t ParticleSystem::randomizeMatrix(std::uint32_t seed)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (auto &row : matrix)
        for (auto &v : row)
            v = dist(rng);

    return seed;
}

double ParticleSystem::rule(ParticleType type1, ParticleType type2) const
{
    return matrix[static_cast<std::size_t>(type1)][static_cast<std::size_t>(type2)];
}

double ParticleSystem::forceMagnitude(double x, double a) const
{
    const double beta = params.beta;

    // when (r / R) < beta, there matrix values does not have an impact on the force
    if (x < beta)
    {
        return x / beta - 1.0;
    }

    // when (r / R) < 1, the force is a triangle, with max at (beta + 1) / 2
    if (x < 1.0)
    {
        return a * (1.0 - std::abs(2.0 * x - 1.0 - beta) / (1.0 - beta));
    }
    return 0.0;
}

// in a toroidal world, we wrap the distance
Vec2 ParticleSystem::wrapDelta(Vec2 d) const
{
    if (!isToroidal()) {
        return d;
    }

    const double halfW = worldDim.x * 0.5;
    const double halfH = worldDim.y * 0.5;

    if (d.x > halfW) {
        d.x -= worldDim.x;
    }
    else if (d.x < -halfW)
    {
        d.x += worldDim.x;
    }

    if (d.y > halfH) {
        d.y -= worldDim.y;
    }
    else if (d.y < -halfH) {
        d.y += worldDim.y;
    }

    return d;
}

void ParticleSystem::update(float dt)
{
    const std::size_t N = particles.size();
    // interaction radius
    const double interRadius = params.interRadius;
    const double squaredInterRadius = interRadius * interRadius;
    // a force forceScale, proportional to the interaction radius
    const double forceScale = interRadius * params.forceFactor;

    // Forces : each particle is visited once
    // for a particle couple (pi, pj), we compute fpipj and fpjpi
    // rule (pi, pj), gives the atraction / repulsion of pj sur pi

    for (std::size_t i = 0; i < N; ++i)
    {

        Particle &particle = particles[i];
        const Vec2 posI = particle.getPosition();
        const ParticleType typeI = particle.getType();

        for (std::size_t j = i + 1; j < N; ++j)
        {

            Particle &other = particles[j];
            const Vec2 d = wrapDelta(other.getPosition() - posI);
            const double squaredDistance = d.squaredNorm();

            // No need to compute the forces when particles are too close
            // or too far apart.
            if (squaredDistance == 0.0 || squaredDistance >= squaredInterRadius)
            {
                continue;
            }

            const double distance = std::sqrt(squaredDistance);
            // unit vector giving the interaction direction
            const Vec2 dir = d / distance;
            // the force magnitude use distance / radius as input
            const double x = distance / interRadius;

            // Force exerted by j on i.
            const double fij = forceMagnitude(distance / interRadius,
                                              rule(typeI, other.getType()));
            // Force exerted by i on j.
            const double fji = forceMagnitude(distance / interRadius,
                                              rule(other.getType(), typeI));

            // apply the forces on the particles
            particle.ApplyForce(dir * (fij * forceScale));
            other.ApplyForce(dir * (-fji * forceScale));
        }
    }

    // Update each particle's position
    // Here we integrate : update function
    //  v(k) = v(k - 1) + F(k) * dt
    //  x(k) = x(k - 1) + v(k) * dt
    //  Then we apply the friction on the particle
    //      v(k) = v(k) * 2 ^ (-dt / frictionHalfLife), it is just a way of reducing the 
    //      particle velocity over the time.

    const double frictionFactor = std::pow(0.5, dt / params.frictionHalfLife);
    const double halfWidth = worldDim.x * 0.5;
    const double halfHeight = worldDim.y * 0.5;

    for (auto &particle : particles)
    {
        
        particle.update(dt);

        Vec2 position = particle.getPosition();
        Vec2 velocity = particle.getVelocity() * frictionFactor;

        // In a toroidal world, wrap the particles around the boundaries
        if (isToroidal())
        {
            if (position.x < -halfWidth)
                position.x += worldDim.x;
            else if (position.x > halfWidth)
                position.x -= worldDim.x;

            if (position.y < -halfHeight)
                position.y += worldDim.y;
            else if (position.y > halfHeight)
                position.y -= worldDim.y;
        }
        else
        {   // When a particle hits a wall, reverse its velocity component
            // perpendicular to the wall to simulate a bounce.

            if (position.x < -halfWidth)
            {
                position.x = -halfWidth;
                velocity.x = -velocity.x;
            }
            else if (position.x > halfWidth)
            {
                position.x = halfWidth;
                velocity.x = -velocity.x;
            }

            if (position.y < -halfHeight)
            {
                position.y = -halfHeight;
                velocity.y = -velocity.y;
            }
            else if (position.y > halfHeight)
            {
                position.y = halfHeight;
                velocity.y = -velocity.y;
            }
        }

        // set the new postion and velocity.
        particle.setPosition(position);
        particle.setVelocity(velocity);
    }
}