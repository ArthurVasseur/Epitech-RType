/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** RigidBody2D
*/

#ifndef RIGIDBODY2D_HPP_
#define RIGIDBODY2D_HPP_

namespace Component
{
    struct RigidBody2D
    {
    public:
        RigidBody2D() : _mass(100.f), _invMass((_mass != 0.f ? 1.f / _mass : 0.f)),
                        _forces(Vector2Df(0.f, 0.f)), _velocity(Vector2Df(0.f, 0.f)) {}

        explicit RigidBody2D(float mass) : _mass(mass), _invMass((mass != 0.f ? 1.f / mass : 0.f)),
                                           _forces(Vector2Df(0.f, 0.f)), _velocity(Vector2Df(0.f, 0.f)) {}

        ~RigidBody2D() = default;

        float getMass() const { return (_mass); }

        float getInvMass() const { return (_invMass); }

        const Vector2Df &getForces() const { return (_forces); }

        const Vector2Df &getVelocity() const { return (_velocity); }

        void setVelocity(const Vector2Df &velocity) { _velocity = velocity; }

        void addForce(const Vector2Df &gravity) { _forces = _mass * gravity; };

    private:
        float _mass;
        float _invMass;
        Vector2Df _forces;
        Vector2Df _velocity;
    };
}

#endif /* !RIGIDBODY2D_HPP_ */
