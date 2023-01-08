/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SfmlRenderer
*/

#ifndef SFMLRENDERER_HPP_
#define SFMLRENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <queue>

#include "IRenderer.hpp"
#include "Text.hpp"
#include "EventHandler.hpp"
namespace renderer
{
    class SfmlRenderer final : public IRenderer
    {
    public:
        SfmlRenderer(std::shared_ptr<EventHandler> eventHandler);

        ~SfmlRenderer() = default;

        void clear() final;

        void display() final;

        void drawSprite(const Component::Sprite &sprite, const Component::Transform &transform) final;

        void drawText(const Component::ui::Text &text, const Component::Transform &transform) final;

        void drawShape(const Component::Vector2Df &position, const Component::Vector2Df &size) final;

        void handleInputs(float deltatime, Registry &r) final;

        float getPointerX() const final;

        float getPointerY() const final;

        bool isMouseButtonPressed(Input::Mouse m) const final;

        bool pollCharTyped(char &c) final;

    private:
        sf::RenderWindow _window;
        std::unordered_map<std::string, sf::Texture> _sprites;
        std::unordered_map<std::string, sf::Font> _fonts;
        std::shared_ptr<EventHandler> _eventHandler;
        std::queue<char> _textEntered;
    };
}
#endif /* !SFMLRENDERER_HPP_ */
