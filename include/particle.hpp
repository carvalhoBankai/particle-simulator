#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "vec2.hpp"

enum class ParticleType {
    Red,
    Green,
    Yellow
};

class Particle {
    private:
        Vec2 position;
        Vec2 velocity;
        Vec2 acceleration;
        Vec2 force;
        ParticleType type;
        float mass;
    
    public:
        Particle();
        Particle(Vec2 position, ParticleType type);
        void ApplyForce(Vec2 force);  
        void update(float dt);
        Vec2 getPosition() const;
        Vec2 getVelocity() const;
        void setVelocity(Vec2 velocity);
        void setPosition(const Vec2 position);
        ParticleType getType() const;
};

#endif