/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Collider
*/

#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_

#include <algorithm>
#include "Vector2D.hpp"
#include "Rectangle.hpp"

namespace Component
{
    struct Collider
    {
    public:
        Collider() = delete;

        explicit Collider(const Rectangle &rectangle) : _rectangle(rectangle) {}

        explicit Collider(const Vector2Df &size) : _rectangle(Rectangle(size)) {}

        Collider(float w, float h) : _rectangle(Rectangle(w, h)) {}

        ~Collider() = default;

        Vector2Df getHalfSize() const
        {
            return Vector2Df(_rectangle._size.x / 2, _rectangle._size.y / 2);
        }

        const Rectangle &getRectangle() const { return (_rectangle); }

        bool checkCollision(const Vector2Df &position, const Collider &other, const Vector2Df &otherPosition)
        {
            return (checkCollision(position, _rectangle, otherPosition, other.getRectangle()));
        }

        static bool checkCollision(const Vector2Df &position, const Rectangle &rect, const Vector2Df &otherPosition,
                                   const Rectangle &otherRect)
        {
            float leftEdge = position.x;
            float rightEdge = leftEdge + rect._size.x;
            float topEdge = position.y;
            float bottomEdge = topEdge + rect._size.y;
            if (rect._size.x < 0) {
                std::swap(leftEdge, rightEdge);
            }
            if (rect._size.y < 0) {
                std::swap(topEdge, bottomEdge);
            }

            float enemyLeftEdge = otherPosition.x;
            float enemyRightEdge = enemyLeftEdge + otherRect._size.x;
            float enemyTopEdge = otherPosition.y;
            float enemyBottomEdge = enemyTopEdge + otherRect._size.y;
            if (otherRect._size.x < 0) {
                std::swap(enemyLeftEdge, enemyRightEdge);
            }
            if (otherRect._size.y < 0) {
                std::swap(enemyTopEdge, enemyBottomEdge);
            }

            return (rightEdge > enemyLeftEdge && leftEdge < enemyRightEdge &&
                    topEdge < enemyBottomEdge && bottomEdge > enemyTopEdge);
        }

    protected:
    private:
        Rectangle _rectangle;
    };
}

#endif /* !COLLIDER_HPP_ */
