/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** IRenderer
*/

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <string>
#include "Sprite.hpp"
#include "Text.hpp"
#include "Transform.hpp"
#include "Registry.hpp"
#include "Input.hpp"
namespace renderer
{
    class IRenderer
    {
    public:
        virtual void clear() = 0;

        virtual void display() = 0;

        virtual void drawSprite(const Component::Sprite &sprite, const Component::Transform &transform) = 0;

        virtual void drawText(const Component::ui::Text &text, const Component::Transform &transform) = 0;

        virtual void drawShape(const Component::Vector2Df &position, const Component::Vector2Df &size) = 0;

        virtual void handleInputs(float deltatime, Registry &r) = 0;
        virtual float getPointerX() const = 0;
        virtual float getPointerY() const = 0;
        virtual bool isMouseButtonPressed(Input::Mouse m) const = 0;
        virtual bool pollCharTyped(char &) = 0;

        ~IRenderer() = default;
    };
}

#endif /* !IRENDERER_HPP_ */
