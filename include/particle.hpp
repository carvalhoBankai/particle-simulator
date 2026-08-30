#include "vec2.hpp"

class Particle {
    private:
        Vec2 position;
        Vec2 velocity;
        Vec2 acceleration;
        float mass;
    
    public:
        Particle();
        void ApllyForce(Vec2 force, float dt);  
};