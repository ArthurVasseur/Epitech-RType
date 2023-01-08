/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include "ISystem.hpp"

namespace System
{
    class Background : public ISystem {
        public:
            Background(Registry &r);
            ~Background() = default;

        void update(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);
        static void loadBackground(Registry &r);
    };
} // namespace System


#endif /* !BACKGROUND_HPP_ */
